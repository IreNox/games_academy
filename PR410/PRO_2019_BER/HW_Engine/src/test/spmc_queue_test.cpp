#include "hw/threading/spmc_queue.h"
#include "hw/threading/thread.h"

#include <iostream>
#include <vector>

namespace hw
{
	struct TestSpmcQueueData;

	static constexpr size_t ThreadCount = 4u;

	struct TestSpmcQueueThreadData
	{
		TestSpmcQueueData*		pTestData;

		size_t					index;
		std::vector< int >		values;
	};

	struct TestSpmcQueueData
	{
		Thread					threads[ ThreadCount ];
		TestSpmcQueueThreadData	threadData[ ThreadCount ];
		SPMCQueue< int >		queue;
	};

	uint32 testSpmcQueueThread( const Thread& thread )
	{
		TestSpmcQueueThreadData* pThreadData	= (TestSpmcQueueThreadData*)thread.getArgument();
		TestSpmcQueueData* pTestData			= pThreadData->pTestData;

		while( !thread.isQuitRequested() )
		{
			int data;
			if( pTestData->queue.pop( data ) )
			{
				char buffer[ 128u ];
				sprintf_s( buffer, "Thread(%lli): %i\n", pThreadData->index, data );

				OutputDebugStringA( buffer );
				pThreadData->values.push_back( data );
			}
		}

		return 0u;
	}

	void testSpmcQueue()
	{
		TestSpmcQueueData data;
		data.queue.create( 1024 * 1024 );

		for( size_t i = 0u; i < ThreadCount; ++i )
		{
			TestSpmcQueueThreadData& threadData = data.threadData[ i ];
			threadData.pTestData	= &data;
			threadData.index		= i;

			data.threads[ i ].create( testSpmcQueueThread, &threadData );
		}

		for( int i = 0u; i < 10000; ++i )
		{
			data.queue.push( i );
		}

		while( !data.queue.isEmpty() )
		{
			Sleep( 50u );
		}

		for( size_t i = 0u; i < ThreadCount; ++i )
		{
			data.threads[ i ].destroy();
		}

		for( size_t a = 0u; a < ThreadCount; ++a )
		{
			const std::vector< int > threadValuesA = data.threadData[ a ].values;

			for( size_t b = 0u; b < ThreadCount; ++b )
			{
				if( a == b )
				{
					continue;
				}

				const std::vector< int > threadValuesB = data.threadData[ b ].values;

				for( int dataA : threadValuesA )
				{
					for( int dataB : threadValuesB )
					{
						assert( dataA != dataB );
					}
				}
			}
		}
	}
}
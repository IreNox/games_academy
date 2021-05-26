#include "hw/sound/sound_system.h"

#include "hw/core/vector.h"

namespace hw
{
	struct SoundListener
	{
		SoundListenerHandle		handle		= SoundListenerHandle::invalid();

		Vector					position;
	};

	SoundSystem::SoundSystem()
	{
	}

	SoundSystem::~SoundSystem()
	{
	}

	bool SoundSystem::create()
	{
		m_pListeners = new SoundListener[ MaxListenerCount ];

		return true;
	}

	void SoundSystem::destroy()
	{
	}

	void SoundSystem::update()
	{
	}

	SoundListenerHandle SoundSystem::addListener( const Vector& position )
	{
		SoundListener* pListener = nullptr;
		for( size_t i = 0u; i < MaxListenerCount; ++i )
		{
			SoundListener& currentListener = m_pListeners[ i ];
			if( currentListener.handle.isValid() )
			{
				continue;
			}

			pListener = &currentListener;
			pListener->handle.set( uint64( i ), m_nextListenerCounter );

			return pListener->handle;
		}

		return SoundListenerHandle::invalid();
	}

	void SoundSystem::removeListener( SoundListenerHandle listener )
	{
	}

	void SoundSystem::setListenerPosition( SoundListenerHandle listenerHandle, const Vector& position )
	{
		SoundListener* pListener = getListener( listenerHandle );
		if( pListener == nullptr )
		{
			return;
		}

		pListener->position = position;
	}

	SoundInstanceHandle SoundSystem::playSound( const SoundResource* pResource, bool hasPosition, const Vector& position )
	{
		return SoundInstanceHandle::invalid();
	}

	void SoundSystem::stopSound( SoundInstanceHandle instanceHandle )
	{
	}

	void SoundSystem::setInstanceVolume( SoundInstanceHandle instanceHandle, float volume )
	{
	}

	void SoundSystem::setInstancePosition( SoundInstanceHandle instanceHandle, const Vector& position )
	{
	}

	SoundListener* SoundSystem::getListener( SoundListenerHandle handle )
	{
		if( handle.isInvalid() )
		{
			return nullptr;
		}

		SoundListener& listener = m_pListeners[ handle.getIndex() ];
		if( listener.handle != handle )
		{
			return nullptr;
		}

		return &listener;
	}

}

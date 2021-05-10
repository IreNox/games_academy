#include "Map.h"

namespace GA
{
	template< class TKey, class TValue >
	HashMap<TKey, TValue>::HashMap()
	{
		m_pData		= nullptr;
		m_capacity	= 0u;
		m_size		= 0u;
	}

	template< class TKey, class TValue >
	HashMap<TKey, TValue>::~HashMap()
	{
		delete[] m_pData;
	}

	template< class TKey, class TValue >
	bool HashMap<TKey, TValue>::isEmpty() const
	{
		return m_size == 0u;
	}

	template< class TKey, class TValue >
	bool HashMap<TKey, TValue>::hasElements() const
	{
		return m_size > 0u;
	}

	template< class TKey, class TValue >
	size_t HashMap<TKey, TValue>::getSize() const
	{
		return m_size;
	}

	template< class TKey, class TValue >
	HashMap<TKey, TValue>::IteratorType HashMap<TKey, TValue>::getBegin()
	{
		return IteratorType( this, findFirstIndex() );
	}

	template< class TKey, class TValue >
	HashMap<TKey, TValue>::IteratorType HashMap<TKey, TValue>::getEnd()
	{
		return IteratorType( this, m_capacity );
	}

	template< class TKey, class TValue >
	void HashMap<TKey, TValue>::insert( TKey key, TValue value )
	{
		const InsertResult insertResult = insertKey( key );
		*insertResult.pValue = value;
	}

	template< class TKey, class TValue >
	HashMap<TKey, TValue>::InsertResult HashMap<TKey, TValue>::insertKey( TKey key )
	{
		const size_t index = insertIndex( key );

		Element& element = m_pData[ index ];
		if( element.isInUse )
		{
			InsertResult result;
			result.pValue	= &element.value;
			result.isNew	= false;
			return result;
		}

		element.isInUse	= true;
		element.key		= key;

		InsertResult result;
		result.pValue	= &element.value;
		result.isNew	= true;
		return result;
	}

	template< class TKey, class TValue >
	TValue* HashMap<TKey, TValue>::find( const TKey& key )
	{
		const size_t index = findIndex( key );
		if( index >= m_capacity )
		{
			return nullptr;
		}

		return &m_pData[ index ].value;
	}

	template< class TKey, class TValue >
	const TValue* HashMap<TKey, TValue>::find( const TKey& key ) const
	{
		return const_cast< HashMap< TKey, TValue > >( this )->find( key );
	}

	template< class TKey, class TValue >
	bool HashMap<TKey, TValue>::remove( const TKey& key )
	{
		const size_t index = findIndex( key );
		if( index >= m_capacity )
		{
			return false;
		}

		size_t nextIndex = index;
		size_t lastIndex = index;
		while( true )
		{
			nextIndex = (nextIndex + 1u) & (m_capacity - 1u);
			if( !m_pData[ nextIndex ].isInUse )
			{
				break;
			}

			const size_t nextKeyIndex = findIndex( m_pData[ nextIndex ].key );
			if( nextKeyIndex != index )
			{
				break;
			}

			m_pData[ nextIndex - 1u ] = m_pData[ nextIndex ];
			lastIndex = nextIndex;
		}

		m_pData[ lastIndex ].isInUse = false;
		m_size--;

		return true;
	}

	template< class TKey, class TValue >
	void HashMap<TKey, TValue>::grow( size_t nextCapacity )
	{
		Element* pOldElements = m_pData;
		size_t oldCapacity = m_capacity;

		m_pData		= new Element[ nextCapacity ];
		m_capacity	= nextCapacity;

		for( size_t i = 0u; i < m_capacity; ++i )
		{
			Element& oldElement = pOldElements[ i ];
			if( !oldElement.isInUse )
			{
				continue;
			}

			const size_t index = insertIndex( oldElement.key );
			Element& newElement = m_pData[ index ];
			newElement.isInUse	= true;
			newElement.key		= key;
			newElement.value	= value;
		}

		delete[] pOldElements;
	}

	template< class TKey, class TValue >
	size_t HashMap<TKey, TValue>::findIndex( const TKey& key ) const
	{
		if( isEmpty() )
		{
			return m_capacity;
		}

		size_t index = getValueHash( key ) & (m_capacity - 1u);
		while( true )
		{
			Element& element = m_pData[ index ];
			if( !element.isInUse )
			{
				return index;
			}
			else if( element.key == key )
			{
				return index;
			}

			index++;

			if( index >= m_capacity )
			{
				index = 0u;
			}
		}

		return index;
	}

	template< class TKey, class TValue >
	size_t HashMap<TKey, TValue>::insertIndex( const TKey& key ) const
	{
		if( m_size * 2u >= m_capacity )
		{
			grow( m_capacity * 2u );
		}

		return findIndex( key );
	}
}

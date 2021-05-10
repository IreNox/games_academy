#pragma once

namespace GA
{
	template< class TKey, class TValue >
	class HashMapIterator
	{
	public:

		using MapType = HashMap< TKey, TValue >;

						HashMapIterator();
						HashMapIterator( MapType* pMap, size_t index );

		TKey&			getKey();
		const TKey&		getKey() const;
		TValue&			getValue();
		const TValue&	getValue() const;

		void			++operator();

	private:

		MapType*		m_pMap;
		size_t			m_index;
	};

	template< class TKey, class TValue >
	class HashMap
	{
	public:

		using IteratorType = HashMapIterator< TKey, TValue >;

		struct InsertResult
		{
			TValue*		pValue;
			bool		isNew;
		};

						HashMap();
						~HashMap();

		bool			isEmpty() const;
		bool			hasElements() const;

		size_t			getSize() const;

		IteratorType	getBegin();
		IteratorType	getEnd();

		void			insert( TKey key, TValue value );
		InsertResult	insertKey( TKey key );

		TValue*			find( const TKey& key );
		const TValue*	find( const TKey& key ) const;

		bool			remove( const TKey& key );

	private:

		struct Element
		{
			bool		isInUse;
			TKey		key;
			TValue		value;
		};

		Element*		m_pData;
		size_t			m_capacity;
		size_t			m_size;

		void			grow( size_t nextCapacity );

		size_t			findFirstIndex() const;
		size_t			findIndex( const TKey& key ) const;
		size_t			insertIndex( const TKey& key ) const;
	};
}


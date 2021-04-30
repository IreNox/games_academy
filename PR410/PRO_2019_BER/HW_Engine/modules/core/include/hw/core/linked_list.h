#pragma once

namespace hw
{
	template<class T>
	struct LinkedListNode
	{
		T*		pPrev	= nullptr;
		T*		pNext	= nullptr;
	};

	template<class T>
	class LinkedList
	{
	public:

					LinkedList();

		bool		isEmpty() const;
		bool		hasElements() const;

		size_t		getLength() const;

		void		reset();

		void		pushFront( T* pElement );
		T*			popFront();

		void		pushBack( T* pElement);
		T*			popBack();

		void		remove( T* pElement );

	private:

		T*			m_pFirst	= nullptr;
		T*			m_pLast		= nullptr;
		size_t		m_length	= 0u;
	};
}

#include "../../../src/linked_list.inl"

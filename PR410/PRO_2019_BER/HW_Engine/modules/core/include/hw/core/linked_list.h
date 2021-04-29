#pragma once

namespace hw
{
	template<class T>
	struct LinkedListNode
	{
		T*		pPrev;
		T*		pNext;
	};

	template<class T>
	class LinkedList
	{
					LinkedList();

		bool		isEmpty() const;
		bool		hasElements() const;

		size_t		getLength() const;

		void		reset();

		void		pushFront( const T* pElement );
		T*			popFront();

		void		pushBack( const T* pElement);
		T*			popBack();

		void		remove( T* pElement );

	private:

		T*			m_pFirst;
		T*			m_pLast;
		size_t		m_length;
	};
}
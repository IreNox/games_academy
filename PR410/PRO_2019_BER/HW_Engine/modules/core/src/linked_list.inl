#pragma once

namespace hw
{
	template<class T>
	LinkedList<T>::LinkedList()
	{
	}

	template<class T>
	bool LinkedList<T>::isEmpty() const
	{
		return m_length == 0u;
	}

	template<class T>
	bool LinkedList<T>::hasElements() const
	{
		return m_length > 0u;
	}

	template<class T>
	size_t LinkedList<T>::getLength() const
	{
		return m_length;
	}

	template<class T>
	void LinkedList<T>::reset()
	{
		T* pNextElement = nullptr;
		for( T* pElement = m_pFirst; pElement != nullptr; pElement = pNextElement )
		{
			pNextElement = pElement->pNext;

			pElement->pPrev = nullptr;
			pElement->pNext = nullptr;
		}

		m_pFirst	= nullptr;
		m_pLast		= nullptr;
		m_length	= 0u;
	}

	template<class T>
	void LinkedList<T>::pushFront( T* pElement )
	{
		if( m_pFirst != nullptr )
		{
			m_pFirst->pPrev = pElement;
		}

		if( m_pLast == nullptr )
		{
			m_pLast = pElement;
		}

		m_pFirst = pElement;
		m_length++;
	}

	template<class T>
	T* LinkedList<T>::popFront()
	{
		if( m_pFirst == nullptr )
		{
			return nullptr;
		}

		T* pNextElement = m_pFirst->pNext;
		if( pNextElement != nullptr )
		{
			pNextElement->pPrev = nullptr;
		}

		if( pElement == m_pLast )
		{
			m_pLast = nullptr;
		}

		T* pElement = m_pFirst;
		m_pFirst = pNextElement;
		m_length--;

		return pElement;
	}

	template<class T>
	void LinkedList<T>::pushBack( T* pElement )
	{
		if( m_pLast != nullptr )
		{
			m_pLast->pNext = pElement;
		}

		if( m_pFirst == nullptr )
		{
			m_pFirst = pElement;
		}

		m_pLast = pElement;
		m_length++;
	}

	template<class T>
	T* LinkedList<T>::popBack()
	{
		if( m_pLast == nullptr )
		{
			return nullptr;
		}

		T* pPrevElement = m_pLast->pPrev;
		if( pPrevElement != nullptr )
		{
			pPrevElement->pNext = nullptr;
		}

		if( pElement == m_pFirst )
		{
			m_pFirst = nullptr;
		}

		T* pElement = m_pLast;
		m_pLast = pPrevElement;
		m_length--;

		return pElement;
	}

	template<class T>
	void LinkedList<T>::remove( T* pElement )
	{
		T* pPrevElement = m_pLast->pPrev;
		if( pPrevElement != nullptr )
		{
			pPrevElement->pNext = pElement->pNext;
		}

		T* pNextElement = m_pFirst->pNext;
		if( pNextElement != nullptr )
		{
			pNextElement->pPrev = pElement->pPrev;
		}

		if( pElement == m_pFirst )
		{
			m_pFirst = pElement->pNext;
		}

		if( pElement == m_pLast )
		{
			m_pLast = pElement->pPrev;
		}

		pElement->pPrev = nullptr;
		pElement->pNext = nullptr;
		m_length--;
	}

	template<class T>
	T* LinkedList<T>::getFirst()
	{
		return m_pFirst;
	}

	template<class T>
	T* LinkedList<T>::getLast()
	{
		return m_pLast;
	}

	template<class T>
	T* LinkedList<T>::getPrev( T* pElement )
	{
		return pElement->pPrev;
	}

	template<class T>
	T* LinkedList<T>::getNext( T* pElement )
	{
		return pElement->pNext;
	}
}
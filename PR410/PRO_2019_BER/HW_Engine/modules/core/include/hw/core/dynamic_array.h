#pragma once
 
namespace hw
{
	template<class T>
	class DynamicArray
	{
	public:

					DynamicArray();
					DynamicArray( const DynamicArray& rhs );
					~DynamicArray();

		bool		isEmpty() const;
		bool		hasElements() const;

		size_t		getLength() const;
		size_t		getCapacity() const;

		void		clear();
		void		reserve( size_t length );

		T&			pushBack();
		void		pushBack( const T& element );

		T			popBack();

		T&			operator[]( size_t index );
		const T&	operator[]( size_t index ) const;

		T&			operator=( const DynamicArray& rhs );

	private:

		T*			m_pData;
		size_t		m_length;
		size_t		m_capacity;
	};
}
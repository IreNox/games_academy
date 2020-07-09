#include "timer.hpp"

#include <iostream>

#define ARRAY_COUNT( arr ) (sizeof(arr)/sizeof(*arr))
struct Node
{
	struct Node* next;
	int val;
};

struct LinkedList
{
	Node* head;
};

void reverseAfter( struct Node* head, int val )
{
	LinkedList list ={head};

	Node* pNode = head;
	Node* pLastNode = nullptr;
	while( pNode != nullptr )
	{
		if( pNode->next != nullptr &&
			pNode->val == val )
		{
			Node* pEndNode = pNode;
			Node* pLastEndNode = pLastNode;
			while( pEndNode->next != nullptr )
			{
				pLastEndNode = pEndNode;
				pEndNode = pEndNode->next;
			}

			pLastNode->next = pEndNode;
			pEndNode->next = pNode;
			pLastEndNode->next = nullptr;
			pNode = pEndNode;
		}

		pLastNode = pNode;
		pNode = pNode->next;
	}
}

void linkedListTest()
{
	Node nodes[ 9 ];
	for( int i = 0u; i < ARRAY_COUNT(nodes); ++i )
	{
		nodes[ i ].next = &nodes[ i + 1 ];
		nodes[ i ].val = i;
	}
	nodes[ ARRAY_COUNT(nodes)-1 ].next = nullptr;

	reverseAfter( nodes, 3 );

	int i = 0;
	Node* pNode = nodes;
	while( pNode != nullptr )
	{
		std::cout << "Node " << i << " = " << pNode->val << " = " << (char)('A' + pNode->val) << std::endl;
		pNode = pNode->next;
		i++;
	}
}

int factorialNonRecursive( int n )
{
	int r = 1;
	for( int i = 1; i <= n; ++i )
	{
		r *= i;
	}
	return r;
}

int factorialRecursive( int n )
{
	if( n < 1 )
	{
		return 1;
	}

	return n * factorialRecursive( n - 1 );
}

void factorialTest()
{
	std::cout << "N F(0): " << factorialNonRecursive( 0 ) << std::endl;
	std::cout << "N F(2): " << factorialNonRecursive( 2 ) << std::endl;
	std::cout << "N F(3): " << factorialNonRecursive( 3 ) << std::endl;
	std::cout << "R F(0): " << factorialRecursive( 0 ) << std::endl;
	std::cout << "R F(2): " << factorialRecursive( 2 ) << std::endl;
	std::cout << "R F(3): " << factorialRecursive( 3 ) << std::endl;

	GamesAcademy::Timer timer;
	timer.create();

	int r = 0;
	double startTime = timer.get();
	for( int i = 0u; i < 1000000; ++i )
	{
		for( int j = 0u; j < 10; ++j )
		{
			r += factorialNonRecursive( j );
		}
	}
	double endTime = timer.get();
    std::cout << "Non recursive took " << (endTime - startTime) << " sec. Result: " << r << std::endl;

	r = 0;
	startTime = timer.get();
	for( int i = 0u; i < 1000000; ++i )
	{
		for( int j = 0u; j < 10; ++j )
		{
			r += factorialRecursive( j );
		}
	}
	endTime = timer.get();
	std::cout << "Recursive took " << (endTime - startTime) << " sec. Result: " << r << std::endl;
}

int main()
{
	//factorialTest();
	linkedListTest();
}
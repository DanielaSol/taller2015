#ifndef SRC_ASTAR_FSA_H_
#define SRC_ASTAR_FSA_H_

#include <string.h>
#include <stdio.h>

template <class USER_TYPE> class FixedSizeAllocator
{

public:
	// Constants
	enum
	{
		FSA_DEFAULT_SIZE = 100
	};

	// list class
	struct FSA_ELEMENT
	{
		USER_TYPE UserType;

		FSA_ELEMENT *pPrev;
		FSA_ELEMENT *pNext;
	};

public:
	FixedSizeAllocator( unsigned int MaxElements = FSA_DEFAULT_SIZE ) :
	m_pFirstUsed( NULL ),
	m_MaxElements( MaxElements )
	{
		// Aloca memoria suficiente para la cantidad maxima de elementos

		char *pMem = new char[ m_MaxElements * sizeof(FSA_ELEMENT) ];

		m_pMemory = (FSA_ELEMENT *) pMem;

		m_pFirstFree = m_pMemory;

		memset( m_pMemory, 0, sizeof( FSA_ELEMENT ) * m_MaxElements );

		// Apunta al primer elemento
		FSA_ELEMENT *pElement = m_pFirstFree;

		// configura los punteros
		for( unsigned int i=0; i<m_MaxElements; i++ )
		{
			pElement->pPrev = pElement-1;
			pElement->pNext = pElement+1;

			pElement++;
		}

		m_pFirstFree->pPrev = NULL;
		(pElement-1)->pNext = NULL;

	}


	~FixedSizeAllocator()
	{
		delete [] (char *) m_pMemory;
	}

	// Allocate a new USER_TYPE and return a pointer to it
	USER_TYPE *alloc()
	{

		FSA_ELEMENT *pNewNode = NULL;

		if( !m_pFirstFree )
		{
			return NULL;
		}
		else
		{
			pNewNode = m_pFirstFree;
			m_pFirstFree = pNewNode->pNext;

			// if the new node points to another free node then
			// change that nodes prev free pointer...
			if( pNewNode->pNext )
			{
				pNewNode->pNext->pPrev = NULL;
			}

			// node is now on the used list

			pNewNode->pPrev = NULL; // the allocated node is always first in the list

			if( m_pFirstUsed == NULL )
			{
				pNewNode->pNext = NULL; // no other nodes
			}
			else
			{
				m_pFirstUsed->pPrev = pNewNode; // insert this at the head of the used list
				pNewNode->pNext = m_pFirstUsed;
			}

			m_pFirstUsed = pNewNode;
		}

		return reinterpret_cast<USER_TYPE*>(pNewNode);
	}

	void free( USER_TYPE *user_data )
	{
		FSA_ELEMENT *pNode = reinterpret_cast<FSA_ELEMENT*>(user_data);

		if( pNode->pPrev )
		{
			pNode->pPrev->pNext = pNode->pNext;
		}
		else
		{
			m_pFirstUsed = pNode->pNext;
		}

		if( pNode->pNext )
		{
			pNode->pNext->pPrev = pNode->pPrev;
		}

		if( m_pFirstFree == NULL )
		{
			m_pFirstFree = pNode;
			pNode->pPrev = NULL;
			pNode->pNext = NULL;
		}
		else
		{
			m_pFirstFree->pPrev = pNode;
			pNode->pNext = m_pFirstFree;
			m_pFirstFree = pNode;
		}

	}

	USER_TYPE *GetFirst()
	{
		return reinterpret_cast<USER_TYPE *>(m_pFirstUsed);
	}

	USER_TYPE *GetNext( USER_TYPE *node )
	{
		return reinterpret_cast<USER_TYPE *>
			(
				(reinterpret_cast<FSA_ELEMENT *>(node))->pNext
			);
	}

public:

private:

private:
	FSA_ELEMENT *m_pFirstFree;
	FSA_ELEMENT *m_pFirstUsed;
	unsigned int m_MaxElements;
	FSA_ELEMENT *m_pMemory;
};

#endif /* SRC_ASTAR_FSA_H_ */

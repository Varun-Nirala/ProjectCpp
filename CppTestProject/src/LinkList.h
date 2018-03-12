#ifndef __LINKLIST__
#define __LINKLIST__

#include <iostream>

typedef struct Node
{
	int m_iData;
	Node *m_pNext;

	Node() = delete;
	Node(int data)
		:m_iData(data)
		, m_pNext(NULL)
	{}
}Node;

class LinkList
{
	public:
		LinkList(const LinkList &) = delete;
		LinkList& operator=(const LinkList &) = delete;

		LinkList();
		~LinkList();
		LinkList(initializer_list<int> iL);

		void AddNode(int data);
		Node* FindNode(int data);

		Node* DetectLoop();
		void BreakLoop();

		void Display();
		void clear();

	private:
		Node	*m_pHead;
		int		m_Size;
};

LinkList::LinkList()
	:m_pHead(NULL)
	,m_Size(0)
{}

LinkList::LinkList(initializer_list<int> iL)
	: LinkList()
{
	for (int i : iL)
	{
		AddNode(i);
	}
}

LinkList::~LinkList()
{
	clear();
}

void LinkList::clear()
{
	Node *p = m_pHead;
	while (p)
	{
		Node *temp = p;
		p = p->m_pNext;
		delete temp;
		m_Size--;
	}
	m_pHead = NULL;
	m_Size = 0;
}

void LinkList::AddNode(int data)
{
	if (!m_Size)
	{
		m_pHead = new Node(data);
		m_Size++;
	}
	else
	{
		Node *p = m_pHead;

		while (p->m_pNext)
		{
			p = p->m_pNext;
		}
		p->m_pNext = new Node(data);
		m_Size++;
	}
}

Node* LinkList::FindNode(int data)
{
	if (!m_Size)
	{
		return NULL;
	}
	else
	{
		Node *p = m_pHead;

		while (p->m_pNext)
		{
			if (p->m_iData == data)
			{
				return p;
			}
			p = p->m_pNext;
		}
	}
}

Node* LinkList::DetectLoop()
{
	Node *pSlow = m_pHead;
	Node *pFast = m_pHead;

	while (pSlow && pFast && pFast->m_pNext)
	{
		pSlow = pSlow->m_pNext;
		pFast = pFast->m_pNext->m_pNext;

		if (pSlow == pFast)
		{
			return pSlow;
		}
	}
	return NULL;
}

void LinkList::BreakLoop()
{
	Node *pSlow = DetectLoop();
	Node *pFast = pSlow;

	if (pSlow)
	{
		// Loop detected remove it

		// Step 1. Count number of elements in the Loop
		int k = 1;

		while (pSlow->m_pNext != pFast)
		{
			pSlow = pSlow->m_pNext;
			k++;
		}

		// Step 2. Now make pSlow point to head and pFast point to k step forward to head
		pFast = pSlow = m_pHead;

		for (int i = 0; i < k; ++i)
		{
			pFast = pFast->m_pNext;
		}

		// Step 3. Now move one next a time and they will meet at the loop start
		Node *lastNode = NULL;
		while (pSlow != pFast)
		{
			pSlow = pSlow->m_pNext;
			lastNode = pFast;
			pFast = pFast->m_pNext;
		}

		lastNode->m_pNext = NULL;
	}
}

void LinkList::Display()
{
	Node *p = m_pHead;
	
	while (p)
	{
		cout << p->m_iData << "->";
		p = p->m_pNext;
	}
	cout << "NULL" << endl;
}
#endif
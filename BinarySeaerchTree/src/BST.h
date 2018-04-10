#ifndef __BST_H__
#define __BST_H__

#include <iostream>
#include <queue>

using namespace std;

typedef struct Node
{
	using _dataType = int;

	Node()
	:m_pLeft(nullptr)
	, m_pRight(nullptr)
	, m_data(0)
	{}

	Node(_dataType data)
		:Node()
	{
		m_data = data;
	}

	struct Node		*m_pLeft;
	struct Node		*m_pRight;
	_dataType		m_data;
}Node;

class BST
{
	using _dataType = int;

	public:
		BST();
		~BST();

		BST(const BST &) = delete;
		BST(const BST &&) = delete;
		BST& operator=(const BST &) = delete;

		void clear();
		int size();
		void push(_dataType &data);
		bool find(_dataType &data);
		bool pop(_dataType &data);

		void inOrderDisplay();
		void preOrderDisplay();
		void postOrderDisplay();

	private:
		void insert(Node **node, _dataType &data);
		void inorder(Node *node);
		void preorder(Node *node);
		void postorder(Node *node);

	private:
		Node		*m_pRoot;
		int			m_iSize;
};

BST::BST()
	:m_pRoot(nullptr)
	, m_iSize(0)
{}

BST::~BST()
{
	clear();
}

void BST::clear()
{
	// Using BFS for deletion
	std::queue<Node *> qNodePtr;
	qNodePtr.push(m_pRoot);

	while (!qNodePtr.empty())
	{
		Node *node = qNodePtr.front();
		qNodePtr.pop();

		if (node->m_pLeft)
		{
			qNodePtr.push(node->m_pLeft);
		}

		if (node->m_pRight)
		{
			qNodePtr.push(node->m_pRight);
		}

		delete node;
		node = nullptr;
		m_iSize--;
	}
}

int BST::size()
{
	return m_iSize;
}

void BST::push(_dataType &data)
{
	insert(&m_pRoot, data);
}

bool BST::find(_dataType &data)
{
	Node *p = m_pRoot;
	while (p)
	{
		if (data == p->m_data)
		{
			return true;
		}
		else if (data < p->m_data)
		{
			p = p->m_pLeft;
		}
		else
		{
			p = p->m_pRight;
		}
	}
	return false;
}

bool BST::pop(_dataType &data)
{
	return false;
}

void BST::inOrderDisplay()
{
	cout << "Inorder   :: ";
	inorder(m_pRoot);
	cout << endl;
}

void BST::preOrderDisplay()
{
	cout << "Preorder  :: ";
	preorder(m_pRoot);
	cout << endl;
}

void BST::postOrderDisplay()
{
	cout << "Postorder :: ";
	postorder(m_pRoot);
	cout << endl;
}

//Private members
void BST::insert(Node **node, _dataType &data)
{
	if (!*node)
	{
		*node = new Node(data);
		m_iSize++;
	}
	else if (data == (*node)->m_data)
	{
		(*node)->m_data = data;	// Simple replacement
	}
	else if (data < (*node)->m_data)
	{
		insert(&(*node)->m_pLeft, data);
	}
	else
	{
		insert(&(*node)->m_pRight, data);
	}
	
	return;
}

void BST::inorder(Node *node)
{
	if (!node)
	{
		return;
	}
	inorder(node->m_pLeft);
	cout << node->m_data << ", ";
	inorder(node->m_pRight);
}

void BST::preorder(Node *node)
{
	if (!node)
	{
		return;
	}
	cout << node->m_data << ", ";
	preorder(node->m_pLeft);
	preorder(node->m_pRight);
}

void BST::postorder(Node *node)
{
	if (!node)
	{
		return;
	}
	postorder(node->m_pLeft);
	postorder(node->m_pRight);
	cout << node->m_data << ", ";
}
#endif // __BST_H__
#include "RedBlackTree.h"
#include <assert.h>

const char COLOR_BLACK = 'B';
const char COLOR_RED = 'R';

RedBlacktree::RedBlacktree()
	: m_pRoot(NULL)
	, m_pcLEAF{createNewNode(COLOR_BLACK)}
{}

bool RedBlacktree::add(dataType &data)
{

}

bool RedBlacktree::remove(dataType &data)
{
}

//Private Members
void RedBlacktree::rotateRight(Node *node)
{
	Node *newRoot = node->m_pLeft;

	if (isLeaf(newRoot))
	{
		assert(!"Can't Rotate right, something wrong with tree");
		return;
	}

	node->m_pLeft = newRoot->m_pRight;
	newRoot->m_pRight = node;

	newRoot->m_pParent = node->m_pParent;
	node->m_pParent = newRoot;

	node->m_pLeft->m_pParent = node;
}

void RedBlacktree::rotateLeft(Node *node)
{
	Node *newRoot = node->m_pRight;
	if (isLeaf(newRoot))
	{
		assert(!"Can't Rotate left, something wrong with tree");
		return;
	}

	node->m_pRight = newRoot->m_pLeft;
	newRoot->m_pLeft = node;

	newRoot->m_pParent = node->m_pParent;
	node->m_pParent = newRoot;

	node->m_pRight->m_pParent = node;
}

Node* RedBlacktree::getParent(const Node *node)
{
	if (!node)
		return NULL;

	Node *n = node->m_pParent;
	return n;
}

Node* RedBlacktree::getGrandParent(const Node *node)
{
	if (!node)
		return NULL;

	Node *p = getParent(node);
	if (!p)
	{
		// LOG
		return NULL;
	}
	return getParent(p);
}

Node* RedBlacktree::getSibling(const Node *node)
{
	Node *p = getParent(node);
	if (!p)
	{
		//LOG
		return NULL;
	}

	if (p->m_pLeft == node)
	{
		return p->m_pRight;
	}
	else
	{
		return p->m_pLeft;
	}
}

Node* RedBlacktree::getUncle(const Node *node)
{
	if (!getGrandParent(node))
	{
		//LOG
		return NULL;
	}
	else
	{
		return getSibling(getParent(node));
	}
}

bool RedBlacktree::isBlack(const Node *node)
{
	return node->m_cColor == COLOR_BLACK;
}

bool RedBlacktree::isRed(const Node *node)
{
	return !(isBlack(node));
}

bool RedBlacktree::isLeaf(const Node *node)
{
	return node == m_pcLEAF;
}

Node* RedBlacktree::createNewNode(const dataType &data, const char &color)
{
	Node *newNode = new Node(data, color);
	if (!newNode)
	{
		assert(!"Node Creation error");
		//LOG_ERROR
	}
	return newNode;
}
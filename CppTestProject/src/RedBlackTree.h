#ifndef __REDBLACK_TREE_H__
#define __REDBLACK_TREE_H__

#include <iostream>

extern const char COLOR_BLACK;
extern const char COLOR_RED;

typedef struct Node
{
	using dataType = int;

	struct Node		*m_pParent;
	struct Node		*m_pLeft;
	struct Node		*m_pRight;
	char			m_cColor;
	dataType		m_iData;

	Node(const dataType &d,const char &ch)
	{
		m_pParent	= NULL;
		m_pLeft		= NULL;
		m_pRight	= NULL;
		m_cColor	= ch;
		m_iData		= d;
	}
}Node;

class RedBlacktree
{
	using dataType = int;
	public:
		RedBlacktree();
		~RedBlacktree();

		bool add(dataType &data);
		bool remove(dataType &data);

	private:
		//Rotation
		void	rotateRight(Node *node);
		void	rotateLeft(Node *node);

		//Functionality used by other methods
		Node*	getParent(const Node *node);
		Node*	getGrandParent(const Node *node);
		Node*	getSibling(const Node *node);
		Node*	getUncle(const Node *node);
		bool	isBlack(const Node *node);
		bool	isRed(const Node *node);
		bool	isLeaf(const Node *node);

		Node*	createNewNode(const dataType &data = 0, const char &color = COLOR_RED);

	private:
		Node		*m_pRoot;
		const Node	*m_pcLEAF;
};
#endif //#ifndef __REDBLACK_TREE_H__
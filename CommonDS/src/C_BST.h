#ifndef __C_BST_H__
#define __C_BST_H__

/*
	Desc : Binary search tree handling keys with same value
*/

namespace nsC_BST
{
	template<typename T>
	struct Node
	{
		T m_data;

		int m_count;
		//Node *m_pP;	// Parent Node
		Node *m_pL;	// Left Child Node
		Node *m_pR;	// Right Child Node

		Node(T value = 0) :
			m_data(value)
			//, m_pP(NULL)
			, m_pL(NULL)
			, m_pR(NULL)
			, m_count(1)
		{}
	};

	template<typename T>
	bool InsertRecursive(Node<T> *&root, T data)	// Recursive version
	{
		if (!root)
		{
			root = new Node<T>(data);
			return true;
		}
		else if (data < root->m_data)
		{
			InsertRecursive(root->m_pL, data);
		}
		else if (data > root->m_data)
		{
			InsertRecursive(root->m_pR, data);
		}
		else
		{
			// i.e same key
			root->m_count++;
			return true;
		}
	}

	template<typename T>
	bool InsertIterative(Node<T> *&root, T data)	// Iterative version
	{
		if (!root)
		{
			root = new Node<T>(data);
			return true;
		}
		else
		{
			Node<T> *curr = root;
			Node<T> *prev = NULL;

			while (curr)
			{
				prev = curr;
				if (data < curr->m_data)
				{
					curr = curr->m_pL;
				}
				else
				{
					curr = curr->m_pR;
				}
			}

			if (curr)	// that means it should have the same key
			{
				if (curr->m_data == data)
				{
					curr->m_count++;
				}
				else
				{
					assert(false);
					printf("ERROR::%s::%d:: Data corrupt.", __FUNCTIONW__, __LINE__);
					return false;
				}
			}
			else if (data < prev->m_data)
			{
				prev->m_pL = new Node<T>(data);
			}
			else
			{
				prev->m_pR = new Node<T>(data);
			}
		}

		return true;
	}

	template<typename T>
	bool search(Node<T> *root, T value)
	{
		if (root)
		{
			if (value < root->m_data)
			{
				search(root->m_pL, value);
			}
			else if (value > root->m_data)
			{
				search(root->m_pR, value);
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	template<typename T>
	Node<T>* remove(Node<T> *root, T value)
	{
		if (!root)
		{
			return NULL;
		}
		else if (value < root->m_data)
		{
			root->m_pL = remove(root->m_pL, value);
		}
		else if (value > root->m_data)
		{
			root->m_pR = remove(root->m_pR, value);
		}
		else
		{// We found the Node
			
			// Case 1. If it have count > 1 (Special case as our tree can store multiple same key)
			if (root->m_count > 1)
			{
				root->m_count--;
			}
			// Case 2. If it have no child 
			else if (root->m_pL == NULL && root->m_pR == NULL)
			{
				delete root;
				root = NULL;
			}
			// Case 3. If it have Only one child
				// a : Have right Child
			else if (root->m_pL == NULL)
			{
				Node<T> *temp = root;
				root = root->m_pR;
				delete temp;
			}
			// Case 3. If it have Only one child
				// b : Have left Child
			else if (root->m_pR == NULL)
			{
				Node<T> *temp = root;
				root = root->m_pL;
				delete temp;
			}
			// Case 3. If it have both child
			else
			{
				Node<T> *rightMin = FindMin(root->m_pR);	// Find the minimum in right sub tree
				root->m_data = rightMin->m_data;
				root->m_count = rightMin->m_count;

				rightMin->m_count = 1;
				root->m_pR = remove(root->m_pR, rightMin->m_data);
			}
		}
		return root;
	}

	template<typename T>
	Node<T>* FindMin(Node<T> *root)
	{
		Node<T> *curr = root;

		/* loop down to find the leftmost leaf */
		while (curr->m_pL != NULL)
		{
			curr = curr->m_pL;
		}

		return curr;
	}

	template<typename T>
	void preorder(Node<T> *root)
	{
		if (!root)
		{
			return;
		}

		preorder(root->m_pL);
		cout << "Data = " << root->m_data << " (" << root->m_count << ")" << endl;
		preorder(root->m_pR);
	}

	template<typename T>
	void inorder(Node<T> *root)
	{
		if (!root)
		{
			return;
		}

		inorder(root->m_pL);
		inorder(root->m_pR);
		cout << "Data = " << root->m_data << " (" << root->m_count << ")" << endl;
	}

	template<typename T>
	void postorder(Node<T> *root)
	{
		if (!root)
		{
			return;
		}

		cout << "Data = " << root->m_data << " (" << root->m_count << ")" << endl;
		postorder(root->m_pL);
		postorder(root->m_pR);
	}
}
#endif //__BST_H__
#ifndef __C_LIST_H__
#define __C_LIST_H__

#include <iostream>

namespace nsC_List
{
	template<typename T>
	struct Node
	{
		T		m_data;
		Node	*m_pNext;
		Node	*m_pPrev;

		Node(T value) :
			m_data(value)
			, m_pNext(NULL)
			, m_pPrev(NULL)
		{}
	};

	template<typename T>
	struct List
	{
		int			m_size;
		Node<T>		*m_pHead;
		Node<T>		*m_pTail;

		List() :
			m_size(0)
			, m_pHead(NULL)
			, m_pTail(NULL)
		{}
	};

	template<typename T>
	List<T>* CreateList()
	{
		return new List<T>();
	}

	template<typename T>
	void DeleteList(List<T> *&list)
	{
		if (list)
		{
			int size = list->m_size;
			for (int i = 0; i < size; ++i)
			{
				PopBack(list);
			}

			delete list;
			list = NULL;

			std::cout << "List is destroyed..." << std::endl;
		}
	}

	template<typename T>
	bool PushFront(List<T> *list, T value)
	{
		if (list)
		{
			Node<T> *node = new Node<T>(value);

			if (list->m_size == 0)
			{
				list->m_pHead = list->m_pTail = node;
			}
			else
			{
				list->m_pHead->m_pPrev = node;
				node->m_pNext = list->m_pHead;

				list->m_pHead = node;
			}
			list->m_size++;

			return list->m_size > 0;
		}
		else
		{
			std::cout << "List is a NULL pointer." << std::endl;
			return false;
		}
	}

	template<typename T>
	bool PushBack(List<T> *list, T value)
	{
		if (list)
		{
			Node<T> *node = new Node<T>(value);

			if (list->m_size == 0)
			{
				list->m_pHead = list->m_pTail = node;
			}
			else
			{
				list->m_pTail->m_pNext = node;
				node->m_pPrev = list->m_pTail;

				list->m_pTail = node;
			}

			list->m_size++;

			return list->m_size > 0;
		}
		else
		{
			std::cout << "List is a NULL pointer." << std::endl;
			return false;
		}
	}

	template<typename T>
	bool PopBack(List<T> *list)
	{
		if (list && list->m_size > 0)
		{
			Node<T> *node = list->m_pTail;
			list->m_pTail = node->m_pPrev;
			if (list->m_pTail)
			{
				list->m_pTail->m_pNext = NULL;
			}

			list->m_size--;

			delete node;

			return true;
		}
		else
		{
			std::cout << "List is a NULL pointer." << std::endl;
			return false;
		}
	}

	template<typename T>
	bool PopFront(List<T> *list)
	{
		if (list && list->m_size > 1)
		{
			Node<T> *node = list->m_pHead;
			list->m_pHead = node->m_pNext;
			if (list->m_pHead)
			{
				list->m_pHead->m_pPrev = NULL;
			}

			list->m_size--;

			delete node;

			return true;
		}
		else
		{
			std::cout << "List is a NULL pointer." << std::endl;
			return false;
		}
	}

	template<typename T>
	bool Front(List<T> *list, T &value)
	{
		if (!list)
		{
			std::cout << "List is a NULL pointer." << std::endl;
		}
		else if (list->m_size > 0)
		{
			value = list->m_pHead->m_data;
			return true;
		}
		return false;
	}

	template<typename T>
	bool Back(List<T> *list, T &value)
	{
		if (!list)
		{
			std::cout << "List is a NULL pointer." << std::endl;
		}
		else if (list->m_size > 0)
		{
			value = list->m_pTail->m_data;
			return true;
		}
		return false;
	}

	template<typename T>
	void Traverse(List<T> *list)
	{
		if (!list)
		{
			std::cout << "List is a NULL pointer." << std::endl;
		}
		else if (list && list->m_size == 0)
		{
			std::cout << "List is empty." << std::endl;
		}
		else
		{
			int size = list->m_size;
			Node<T> *node = list->m_pHead;
			std::cout << "List data is ..." << std::endl;
			for (int i = 0; i < size; i++)
			{
				std::cout << "[" << i << "]" << " :: " << node->m_data << std::endl;
				node = node->m_pNext;
			}
		}
	}
}
#endif// __C_LIST_H__
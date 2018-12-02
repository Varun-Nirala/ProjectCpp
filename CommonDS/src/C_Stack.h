#ifndef __C_STACK_H__
#define __C_STACK_H__

namespace nsC_Stack
{
	template<typename T>
	struct Stack
	{
		T		*m_arr;
		int		m_top;
		int		m_capacity;

		Stack(int size)
			: m_arr(NULL)
		{
			m_top = -1;
			m_capacity = size;
			m_arr = new T[m_capacity];
		}
	};

	template<typename T>
	int Size(Stack<T> &stack)
	{
		return stack.m_top + 1;
	}

	template<typename T>
	bool Push(Stack<T> &stack, T value)
	{
		if (stack.m_top < stack.m_capacity - 1)
		{
			int index = ++stack.m_top;
			stack.m_arr[index] = value;
			return true;
		}
		else
		{
			std::cout << "Stack is FULL." << std::endl;
			return false;
		}
	}

	template<typename T>
	bool Top(Stack<T> &stack, T &value)
	{
		if (stack.m_top >= 0)
		{
			value = stack.m_arr[stack.m_top];
			return true;
		}
		else
		{
			std::cout << "Stack is EMPTY." << std::endl;
			return false;
		}
	}

	template<typename T>
	void Pop(Stack<T> &stack)
	{
		if (stack.m_top >= 0)
		{
			stack.m_top--;
		}
		else
		{
			std::cout << "Stack is EMPTY." << std::endl;
		}
	}
}
#endif // __C_STACK_H__
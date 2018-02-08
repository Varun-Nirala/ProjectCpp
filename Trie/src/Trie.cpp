#include <Trie.h>
#include <stack>

using std::string;
using std::cin;
using std::cout;
using std::endl;

Trie::Trie()
	:m_pRoot(NULL)
	, m_nWordCount(0)
{
	m_pRoot = new Node(ROOT_CHAR);
}

Trie::Trie(const string &word)
	:Trie()
{
	if (!AddWord(word))
	{
		LOG_ERROR(__FUNCTION__, __LINE__, "Failed to add word");
	}
}

Trie::~Trie()
{
	clearAll();
}

// DFS display
void Trie::Display()
{
	if (!getWordCount())
	{
		LOG_DEBUG(__FUNCTION__, __LINE__, "Disctionary is empty.");
		return;
	}
	std::stack<Node*> myStack;
	string sPrefix;
	Node *node = m_pRoot;

	myStack.push(node);
	if (node->m_pChild)
	{
		node = node->m_pChild;
		myStack.push(node);
	}

	while (myStack.size() > 1)
	{
		node = myStack.top();
		sPrefix.push_back(node->m_cData);

		while (node->m_pChild)
		{
			node = node->m_pChild;
			sPrefix.push_back(node->m_cData);
			
			myStack.push(node);
		}

		cout << sPrefix << endl;
		
		node = myStack.top();
		while (node->m_pNext == NULL && myStack.size() > 1)
		{
			myStack.pop();
			node = myStack.top();
			sPrefix.pop_back();
		}

		if (sPrefix.size())
		{
			sPrefix.pop_back();
			myStack.pop();
			myStack.push(node->m_pNext);
		}
	}
}

bool Trie::AddWord(const string &word)
{
	bool rc = true;
	Node *node = m_pRoot;
	int startIndex = 0;

	if (getWordCount() == 0)
	{
		for (char ch : word)
		{
			node->m_pChild = new Node(ch);
			node = node->m_pChild;
		}
		node->m_pChild = new Node('\n');
		incrementWordCount();
		LOG_DEBUG(__FUNCTION__, __LINE__, "Word Added Successfuly.");
	}
	else
	{
		node = node->m_pChild;	// Descend to the first child of root
		int prefixMatchIndex = 0, size = word.size();

		node = findInsertionPoint(node, word, 0, prefixMatchIndex);

		if (node->m_pNext == NULL)	// should be NULL
		{
			node->m_pNext = new Node(word[prefixMatchIndex]);
			node = node->m_pNext;

			for (int i = prefixMatchIndex + 1; i < size; i++)
			{
				node->m_pChild = new Node(word[i]);
				node = node->m_pChild;
			}
		}
		else
		{
			LOG_ERROR(__FUNCTION__, __LINE__, "Logical Error.Should not be here.");
		}

		node->m_pChild = new Node('\n');
		incrementWordCount();
		LOG_DEBUG(__FUNCTION__, __LINE__, "Word Added Successfuly.");
	}
	return rc;
}

/*
Prequisite	:: Root node shouldn't be passed as first argument.
Return		:: Returns the node which matched the char of the string with its index as prefixMatchIndex
*/
Node* Trie::findInsertionPoint(Node *node, const std::string &word, int startIndex, int &prefixMatchIndex)
{
	if (!node)
	{
		LOG_ERROR(__FUNCTION__, __LINE__, "NULL passed as argument");
		return NULL;
	}

	prefixMatchIndex = 0;
	bool found = false;

	int size = word.size();
	for (startIndex; startIndex < size; ++startIndex)
	{
		char ch = word[startIndex];

		while (!found)
		{
			if (node->m_cData == ch)
			{
				found = true;
			}
			else
			{
				if (node->m_pNext)
				{
					node = node->m_pNext;
				}
				else
				{
					break;
				}
			}
		}

		if (found)
		{
			if (node->m_pChild)
			{
				node = node->m_pChild;
			}
			prefixMatchIndex++;
			found = false;
		}
		else
		{
			break;
		}
	}
	return node;
}

bool Trie::incrementWordCount()
{
	if (m_nWordCount < INT_MAX)
	{
		m_nWordCount++;
		return true;
	}
	else
	{
		LOG_ERROR(__FUNCTION__, __LINE__, "No Word present.");
		return false;
	}
}

bool Trie::decrementWordCount()
{
	if (m_nWordCount > 0)
	{
		m_nWordCount--;
		return true;
	}
	else
	{
		LOG_ERROR(__FUNCTION__, __LINE__, "Reached max int limit.");
		return false;
	}
}

int Trie::getWordCount() const
{
	return m_nWordCount;
}

void Trie::clearAll()
{
}
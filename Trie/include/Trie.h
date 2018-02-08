#ifndef _TRIE_H_
#define _TRIE_H_

#include <iostream>
#include <string>

void inline LOG_DEBUG(const std::string &func, int line, const std::string &msg)
{
	std::cout << "DEBUG :: " << func << "::" << line << "  :  " << msg << std::endl;
}

void inline LOG_ERROR(const std::string &func, int line, const std::string &msg)
{
	std::cout << "ERROR :: " << func << "::" << line << "  :  " << msg << std::endl;
}

#define ROOT_CHAR '\r'

typedef struct Node
{
	char	m_cData;
	Node	*m_pNext;
	Node	*m_pChild;

	Node(char ch)
		:m_cData(ch)
		, m_pNext(NULL)
		, m_pChild(NULL)
	{}
}Node;

class Trie
{
	public:
		Trie();
		Trie(const std::string &word);

		~Trie();

		void Display();
		bool AddWord(const std::string &word);
		Node* findInsertionPoint(Node *node, const std::string &word, int startIndex, int &prefixMatchIndex);

		void clearAll();

		bool incrementWordCount();
		bool decrementWordCount();

		int getWordCount() const;

	private:
		Node	*m_pRoot;
		int		m_nWordCount;
};
#endif 
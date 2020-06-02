#include "trieTree.h"
#include <cassert>

namespace DS
{
	Node::Node(char alpha /*= '\0'*/, bool end /*= false*/)
		:mChar(alpha)
		, mIsEnd(end)
	{}

	Node::Node(const Node &src)
	{
		mChar = src.mChar;
		mIsEnd = src.mIsEnd;
		copyFrom(src);
	}

	Node::Node(Node &&src)
	{
		mChar = std::move(src.mChar);
		mIsEnd = std::move(src.mIsEnd);
		mNodes = std::move(src.mNodes);
	}

	Node& Node::operator=(const Node &src)
	{
		if (this != &src)
		{
			copyFrom(src);
		}
		return *this;
	}

	Node& Node::operator=(Node &&src)
	{
		mChar = std::move(src.mChar);
		mIsEnd = std::move(src.mIsEnd);
		mNodes = std::move(src.mNodes);
		return *this;
	}

	Node::~Node()
	{
		for (auto it : mNodes)
		{
			delete it;
		}
		mNodes.clear();
	}

	bool Node::isLeaf() const
	{
		return mNodes.empty();
	}

	bool Node::matchChar(const char &ch) const
	{
		return ch == mChar;
	}

	const std::vector<Node*>& Node::getNodes() const
	{
		return mNodes;
	}

	std::vector<Node*>& Node::getNodes()
	{
		return mNodes;
	}

	bool Node::erase(const char &ch)
	{
		return std::begin(mNodes) == mNodes.erase(std::find_if(std::begin(mNodes), std::end(mNodes), 
			[&ch](Node *node) -> bool { return node->matchChar(ch); })
		);
	}

	void Node::copyFrom(const Node &src)
	{
		mNodes.resize(src.mNodes.size());

		for (size_t i = 0; i < src.mNodes.size(); ++i)
		{
			mNodes[i] = new Node(*src.mNodes[i]);
		}
	}

	std::ostream& operator<<(std::ostream &out, Node &node)	// Node Friend Function
	{
		out << node.mChar;

		if (node.mIsEnd)
		{
			out << std::endl;
		}
		return out;
	}

	std::ostream& operator<<(std::ostream &out, Node *node)	// Node Friend Function
	{
		out << *node;
		return out;
	}





	Trie::Trie()
		: mSize(0)
	{}

	Trie::Trie(std::initializer_list<std::string> il)
	{
		std::for_each(il.begin(), il.end(), [&](auto word) {
			insert(word);
		});
	}

	bool Trie::insert(std::string word)
	{
		convertToLower(word);
		return addWord(word);
	}

	size_t Trie::erase(std::string word, bool delAllWithPref/* = false*/)
	{
		convertToLower(word);
		// Count of word's deleted
		size_t retCount = 0;	

		// If we have to delete the exact word
		if (!delAllWithPref)
		{
			if (removeExact(word))
			{
				retCount++;
			}
		}
		// Delete all with prefix
		else
		{
			std::vector<std::string> allWords = getAllWordWithPrefix(word);

			for (auto str : allWords)
			{
				if (removeExact(word + str))
				{
					retCount++;
				}
				else
				{
					assert(!"Error removing exact found word");
				}
			}
		}
		mSize -= retCount;
		mRoot;
		return retCount;
	}

	size_t Trie::count(std::string prefix) const
	{
		convertToLower(prefix);
		size_t pos = 0;
		const Node *node = findWord(prefix, pos).back();
		return traverse(node).size();
	}

	size_t Trie::size() const
	{
		return mSize;
	}

	std::vector<std::string> Trie::getAllWordWithPrefix(std::string prefix) const
	{
		convertToLower(prefix);

		size_t pos = 0;
		const Node *node = findWord(prefix, pos).back();
		std::vector<std::string> allWords = traverse(node);

		return allWords;
	}

	bool Trie::addWord(const std::string &word)
	{
		size_t pos = 0;

		Node *node = const_cast<Node *>(findWord(word, pos).back());

		// No need to check for (node == NULL), findWord should always return a valid node
		if (pos == word.size())
		{
			// This means word is already there
			if (!node->mIsEnd)
			{
				// if it is not the end word node, mark it as it now
				mSize++;
				node->mIsEnd = true;
				return true;
			}
			// As we have done nothing return false
			return false;
		}

		for (pos = pos; pos < word.size(); ++pos)
		{
			node->mNodes.push_back(new Node(word[pos]));
			node = node->mNodes.back();
		}
		node->mIsEnd = true;
		mSize++;

		return true;
	}

	std::vector<std::string> Trie::traverse(const Node *node) const
	{
		std::vector<std::string> allWords;
		allWords.resize(size());

		size_t actualSize = 0;
		recurse(node, "", allWords, actualSize);

		allWords.erase(std::begin(allWords) + actualSize, std::end(allWords));

		return allWords;
	}

	void Trie::recurse(const Node *inNode, std::string pref, std::vector<std::string> &vec, size_t &actualSize) const
	{
		for (size_t i = 0; i < inNode->getNodes().size(); ++i)
		{
			Node *node = inNode->getNodes()[i];
			pref.push_back(node->mChar);

			if (node->mIsEnd)
			{
				vec[actualSize++] = pref;
			}
			recurse(node, pref, vec, actualSize);
			pref.pop_back();
		}
	}

	std::vector<const Node*> Trie::findWord(const std::string &prefix, size_t &pos) const
	{
		std::vector<const Node*> vecNode;
		if (mSize == 0)
		{
			vecNode.push_back(&mRoot);
			return vecNode;
		}

		size_t max = prefix.size();
		const Node *p = &mRoot;

		vecNode.push_back(p);

		std::vector<Node*>::const_iterator it;
		for (size_t i = 0; i < max; ++i)
		{
			it = std::find_if(p->mNodes.begin(), p->mNodes.end(),
				[&i, &prefix](const Node *node)
				{	return node->matchChar(prefix[i]);	}
			);

			if (it != p->mNodes.end())
			{
				p = *it;
				pos++;
				vecNode.push_back(p);
			}
			else
			{
				break;
			}
		}
		return vecNode;
	}

	bool Trie::removeExact(std::vector<const Node*> &vec)
	{
		size_t i = vec.size() - 1;
		Node *child = const_cast<Node *>(vec[i--]);
		for (; i >= 0; --i)
		{
			Node *curr = const_cast<Node *>(vec[i]);

			if (child->isLeaf())
			{
				curr->erase(child->mChar);
				if (curr->getNodes().empty() && !curr->mIsEnd)
				{
					curr->mIsEnd = true;
				}
				else
				{
					return true;
				}
			}
			else if (child->mIsEnd)
			{
				child->mIsEnd = false;
				return true;
			}
			child = curr;
		}

		return false;
	}

	bool Trie::removeExact(std::string word)
	{
		convertToLower(word);

		size_t pos = 0;
		std::vector<const Node*> vec = findWord(word, pos);

		// vector will always have atleast one element, mRoot node.
		if (vec.size() == 1)
		{
			return false;
		}

		if (pos == word.size())
		{
			if (removeExact(vec))
			{
				return true;
			}
			else
			{
				assert(!"Error removing exact found word");
			}
		}
		return false;
	}

	void Trie::convertToLower(std::string &word) const
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}

	void Trie::convertToUpper(std::string &word) const
	{
		std::transform(word.begin(), word.end(), word.begin(),
			[](unsigned char c) { return std::toupper(c); });
	}

	std::ostream& operator<<(std::ostream &out, Trie &trie)	// Trie Friend Function
	{
		auto allWords = trie.traverse(&trie.mRoot);

		if (allWords.empty())
		{
			out << "Trie is Empty\n";
		}
		else
		{
			out << "*************************************" << "\n";
			out << "Total Number of words are :: " << allWords.size() << "\n\n";
			for_each(std::begin(allWords), std::end(allWords), [&out](auto &word) { out << word << "\n"; });
			out << "*************************************" << "\n";
		}
		return out;
	}
}
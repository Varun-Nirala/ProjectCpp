#include <iostream>
#include <string>
#include <vector>

#include "trieTree.h"

using namespace std;

int main()
{
	DS::Trie trie;

	trie.insert("to");
	//trie.insert("tea");
	trie.insert("team");
	trie.insert("ted");
	trie.insert("teaming");
	trie.insert("teamiz");
	trie.insert("ten");
	trie.insert("in");
	trie.insert("inn");
	trie.insert("india");

	cout << trie << endl;

	//auto allWords = trie.getAllWordWithPrefix("i");
	//for_each(std::begin(allWords), std::end(allWords), [](auto &word) { cout << word << "\n"; });

	//DS::Trie tr = std::move(trie);
	//cout << tr << endl;
	//cout << trie << endl;

	//trie.erase("teaming");
	//cout << trie << endl;

	trie.erase("t", true);
	cout << trie << endl;
	return 0;
}

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "trieTree.h"

using namespace std;

void FillFromFile(const string &fileName, DS::Trie &trie)
{
	ifstream inf{fileName};

	// If we couldn't open the input file stream for reading
	if (!inf)
	{
		// Print an error and exit
		std::cerr << "File open error!\n";
		return;
	}

	size_t totalReadWord = 0;
	size_t successFullInsertion = 0;

	// While there's still stuff left to read
	std::string strInput;
	while (inf)
	{
		// read stuff from the file into a string and print it
		std::getline(inf, strInput);
		totalReadWord++;
		successFullInsertion++;
		if (!trie.insert(strInput))
		{
			successFullInsertion--;
			std::cerr << "Already exists! :: " << strInput << endl;
		}
	}

	cout << "Total Word Read From file are : " << totalReadWord << endl;
	cout << "Total Successfull insertions : " << successFullInsertion << endl;
}

void searchWordsInFile(const string &fileName, const DS::Trie &trie)
{
	ifstream inf{ fileName };

	// If we couldn't open the input file stream for reading
	if (!inf)
	{
		// Print an error and exit
		std::cerr << "File open error!\n";
		return;
	}

	size_t totalReadWord = 0;
	size_t successfullyFound = 0;

	// While there's still stuff left to read
	std::string strInput;
	while (inf)
	{
		// read stuff from the file into a string and print it
		std::getline(inf, strInput);
		totalReadWord++;
		successfullyFound++;
		if (!trie.find(strInput))
		{
			successfullyFound--;
			std::cerr << "Not Found :: " << strInput << endl;
		}
	}

	cout << "Total Word Read From file are : " << totalReadWord << endl;
	cout << "Successfully found words : " << successfullyFound << endl;
}

int main()
{
	DS::Trie trie;
	std::string fileName{ "C:\\Varun_Work\\GitHub\\Trie\\words.txt" };

	FillFromFile(fileName, trie);

	cout << "Number of words in trie are : " << trie.size() << endl;

	searchWordsInFile(fileName, trie);
	//cout << trie << endl;

	//DS::Trie trie{ "to", "tea", "team", "ted", "teaming", "teamiz", "ten", "in", "inn", "india" };
	//cout << trie << endl;

	//auto allWords = trie.getAllWordWithPrefix("i");
	//for_each(std::begin(allWords), std::end(allWords), [](auto &word) { cout << word << "\n"; });

	//DS::Trie tr = std::move(trie);
	//cout << tr << endl;
	//cout << trie << endl;

	//trie.erase("teaming");
	//cout << trie << endl;

	//trie.erase("t", true);
	//cout << trie << endl;
	return 0;
}

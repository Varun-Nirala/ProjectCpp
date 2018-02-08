#include <iostream>
#include <Trie.h>

using namespace std;

int main(int argc, char *argv[])
{
	bool endIt = false;
	int input;
	Trie trieRoot;
	while (!endIt)
	{
		cout << "Menu :: Press key\n";
		cout << "1. To Insert a Word.\n";
		cout << "2. To Display all Word.\n";
		cout << "3. To Exit.\n";
		string word;

		getline(cin, word);

		input = word[0] - '0';

		switch (input)
		{
			case 1:
				cout << "Enter the word :: ";
				getline(cin, word);
				trieRoot.AddWord(word);
				break;
			case 2:
				trieRoot.Display();
				break;
			case 3:
				endIt = true;
				break;
		}
	}

	return 0;
}
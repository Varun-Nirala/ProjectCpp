#include "BST.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec{ 8, 3, 10, 1, 6, 14, 4, 7, 13};
	// Inorder		-> 1, 3, 4, 6, 7, 8, 10, 13, 14
	// PreOrder		-> 8, 3, 1, 6, 4, 7, 10, 14, 13
	// PostOrder	-> 1, 4, 7, 6, 3, 13, 14, 10, 8

	BST bst;

	for (int &val : vec)
	{
		bst.push(val);
	}

	cout << "Size = " << bst.size() << endl;

	bst.inOrderDisplay();
	bst.preOrderDisplay();
	bst.postOrderDisplay();

	system("PAUSE");
	return 0;
}
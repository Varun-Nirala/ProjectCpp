#include <iostream>
#include <limits>
#include "..\includes\RedBlackTree.h"

int main()
{
	ns_RBT::RBTree<int> rbTree;

	rbTree.insert(7);
	rbTree.insert(6);
	rbTree.insert(5);
	rbTree.insert(4);
	rbTree.insert(3);
	rbTree.insert(2);
	rbTree.insert(1);

	rbTree.inorder();
	rbTree.levelorder();

	rbTree.remove(6);

	rbTree.inorder();
	rbTree.levelorder();

	rbTree.remove(2);

	rbTree.inorder();
	rbTree.levelorder();

	std::cin.clear(); // reset any error flags
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find an enter character
	std::cin.get();

	return 0;
}
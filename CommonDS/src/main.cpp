#include <iostream>
#include <assert.h>
#include <string.h>
#include <string>
#include "C_BST.h"
#include "C_List.h"
#include "C_Stack.h"

using namespace std;

/******************************************************************************************** Stack
int main()
{
	using namespace nsC_Stack;

	Stack<int> stack(9);

	int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		Push(stack, arr[i]);
	}

	int value;
	while (Top(stack, value))
	{
		cout << "Data :: " << value << endl;
		Pop(stack);
	}
	getchar();
	getchar();
	return 0;
}
Stack*/

/******************************************************************************************** List
int main()
{
	using namespace nsC_List;
	List<int> *list = NULL;

	list = CreateList<int>();

	int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30, 15, 10, 20, 8, 12, 18, 25, 19, 30 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		PushFront(list, arr[i]);
	}
	
	Traverse(list);

	DeleteList(list);

	Traverse(list);

	getchar();
	getchar();
	return 0;
}
List*/

/******************************************************************************************** Integer to English
string gs_num_to_text[] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
string gs_tens_to_text[] = { "", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety" };
string gs_power_to_text[] = { "", "thousand", "million", "billion" };

string padIfNeeded(string ans)
{
	if (ans == "")
	{
		return "";
	}
	return " " + ans;
}

string translateHundred(int hundred_chunk)
{
	// handle special cases in the teens
	if (hundred_chunk < 20) {
		return gs_num_to_text[hundred_chunk];
	}
	int tens = hundred_chunk / 10;
	int ones = hundred_chunk % 10;
	return gs_tens_to_text[tens] + padIfNeeded(gs_num_to_text[ones]);
}


string translateThousand(int thousand_chunk)
{
	if (thousand_chunk < 100)
	{
		return translateHundred(thousand_chunk);
	}
	else
	{
		int hundreds = thousand_chunk / 100;
		int hundred_chunk = thousand_chunk % 100;
		return gs_num_to_text[hundreds] + " hundred" + padIfNeeded(translateHundred(hundred_chunk));
	}
}

int main()
{
	int number;
	bool bIsNegative = false;

	cout << "Enter number : ";
	cin >> number;

	if (number < 0)
	{
		bIsNegative = true;
		number *= -1;
	}

	string num;
	int chunk_count = 0;
	while (number > 0)
	{
		if (number % 1000 != 0)
		{
			num = translateThousand(number % 1000) + padIfNeeded(gs_power_to_text[chunk_count] + padIfNeeded(num));
		}
		number /= 1000;
		chunk_count++;
	}

	cout << num;

	getchar();
	getchar();
	return 0;
}
Integer to English*/

/******************************************************************************************** C Style String Permutation
char* SwitchChar(char *pStr, int x, int y)
{
	char c = pStr[x];
	pStr[x] = pStr[y];
	pStr[y] = c;
	return pStr;
}

void Permute(char *pStr, int start)
{
	if (start == strlen(pStr) - 1)
	{
		printf("%s\n", pStr);
	}

	for (int next = start; next < strlen(pStr); ++next)
	{
		Permute(SwitchChar(pStr, start, next), start + 1);
	}
}

int main()
{
	char buffer[BUFSIZ];

	printf("Enter any string : ");
	scanf("%s", buffer);

	char *pStr = NULL;

	int len = strlen(buffer);

	pStr = (char *)malloc(len + 1);
	memset(pStr, '\0', len + 1);
	//pStr = (char *)calloc(len + 1, sizeof(char));

	for (int i = 0; i < len; ++i)
	{
		pStr[i] = buffer[i];
	}
	printf("Entered string is : %s.\n", pStr);

	Permute(pStr, 0);

	getchar();
	getchar();
	return 0;
}
C Style String Permutation*/

/******************************************************************************************** BinarySearchTree.h*/
int main()
{
	using namespace nsC_BST;
	int choice = 1;
	Node<int> *pRoot = NULL;
	//int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30, 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	//int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	int arr[] = { 15};

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		InsertRecursive(pRoot, arr[i]);
	}

	inorder(pRoot);

	int value;

	cout << "Enter value to delete : ";
	cin >> value;

	if (search(pRoot, value))
	{
		pRoot = remove(pRoot, value);
	}

	inorder(pRoot);

	getchar();
	getchar();

	/*while (choice)
	{
		int data;
		printf("0. To Exit.\n");
		printf("1. To insert data.\n");
		printf("2. To inorder display.\n");

		printf("Enter your choice : \n");
		scanf("%d", &choice);

		switch (choice)
		{
			case 0:
				break;

			case 1:
				printf("Enter the data : ");
				scanf("%d", &data);
				Insert(pRoot, data);
				break;

			case 2:
				inorder(pRoot);
				break;
		}
	}
	*/
	return 0;
}
/*BinarySearchTree.h */
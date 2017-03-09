#include <iostream>
#include <string>

#include "BigInt.h"

using namespace std;
using namespace PersonalInt;

int main(int argc, char *argv[])
{
	string s_number;

	cout << "Enter a number : ";
	cin >> s_number;

	BigInt bigInt;

	bigInt = s_number;
	cout << bigInt;

	bigInt = 123456789;
	cout << bigInt;

	BigInt _bigInt(BigInt("123321"));
	cout << _bigInt;

	system("PAUSE");
	return 0;
}
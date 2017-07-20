#include <iostream>
#include <string>
#include "FileReader.h"

using namespace std;

int main(int argc, char const *argv[])
{
	FileData fileData("test.cpp");

	cout << "Filename 		= " << fileData.GetFileName() << endl;
	cout << "Number of Line = " << fileData.GetSize() << endl;

	cout << "Hello"<< endl;

	return 0;
}
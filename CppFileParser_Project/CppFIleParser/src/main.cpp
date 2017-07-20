#include <iostream>
#include <string>
#include "FileHandler.h"

using namespace std;

int main(int argc, char const *argv[])
{
	FileHandler FileHandler(R"(..\test.cpp)");

	cout << "FileName       = " << FileHandler.GetFileName() << endl;
	cout << "Number of Line = " << FileHandler.GetSize() << endl;

	cout << "Press any key to exit.\n";
	cin.get();
	return 0;
}
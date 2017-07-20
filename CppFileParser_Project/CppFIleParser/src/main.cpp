#include <iostream>
#include <string>
#include "FileHandler.h"

using namespace std;

int main(int argc, char const *argv[])
{
	FileHandler fileHandler(R"(..\test.cpp)");

	cout << fileHandler << endl;

	cout << "Press Enter key to exit.\n";
	cin.get();
	return 0;
}
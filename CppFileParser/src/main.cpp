#include <iostream>
#include <string>
#include "FilesManager.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/*
	FileHandler fileHandler(R"(C:\Varun\GitHubRepo\ProjectCpp\trunk\CppFileParser_Project\test.cpp)");

	cout << fileHandler << endl;

	fileHandler.Rename("test_renamed.cpp");*/

	FilesManager filesManager(R"(C:\Varun\GitHubRepo\ProjectCpp\trunk\CppFileParser_Project\Test\)");

	cout << filesManager.GetSize();

	cout << filesManager << endl;

	cout << "Press Enter key to exit.\n";
	cin.get();
	return 0;
}
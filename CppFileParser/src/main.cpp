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

	// Path home D:\Varun\Varun_Work\GitHubRepos\NiralaVarun\ProjectCpp\CppSolution\C_Threads\src
	// Path Office C:\Varun\GitHubRepo\ProjectCpp\CppSolution\C_Threads\src
	FilesManager filesManager(R"()");

	cout << filesManager.GetSize();

	cout << filesManager << endl;

	cout << "Press Enter key to exit.\n";
	cin.get();
	return 0;
}
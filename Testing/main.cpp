#include <iostream>
#include <vector>
#include <string>

#include "TGA_File.h"

using namespace std;

int main()
{
	string fileName{ "version_1.tga" };

	string path = R"(D:\Varun\Aristocrat_LapTop_BackUp_Jan_2021\Interviews_2021\StarStable\StarStableRounds\ScalingAlgorithm\src\)";

	TGA::TGAFile file(path + fileName);

	file.decode();

	file.displayHeader();
	file.displayFooter();

	string newFileName{ "copy.tga" };
	file.encode(newFileName);

	TGA::TGAFile file1(path + newFileName);
	file1.decode();

	file1.displayHeader();
	file1.displayFooter();

	return 0;
}
#include <iostream>
#include <vector>
#include <string>

#include "TGA_File.h"

using namespace std;

int main()
{
	string fileName{ "sample_640�426.tga" };
	string path = R"(D:\Varun\Aristocrat_LapTop_BackUp_Jan_2021\Interviews_2021\StarStable\StarStableRounds\ScalingAlgorithm\src\)";

	TGAFile file(path + fileName);

	cout << file;

	return 0;
}
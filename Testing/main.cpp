#include <iostream>
#include <vector>
#include <string>

#include "TGA_File.h"

using namespace std;

int main()
{
	string path = R"(D:\Varun\Aristocrat_LapTop_BackUp_Jan_2021\Interviews_2021\StarStable\StarStableRounds\ScalingAlgorithm\src\)";

	//vector<string> vfileNames{ "version_1.tga" , "version_2_TopLeft.tga", "version_2_BottomLeft.tga", "version_2_RLE_TopLeft.tga", "version_2_RLE_BottomLeft.tga" };
	
	vector<string> vfileNames{ "version_2_RLE_TopLeft.tga" };

	for (int i = 0; i < vfileNames.size(); ++i)
	{
		string fileName = vfileNames[i];
		TGA::TGAFile file(path + fileName);

		if (!file.decode())
		{
			cout << "Break";
		}

		file.displayHeader();
		file.displayFooter();

		string newFileName = "copy_" + fileName;

		if (!file.encode(newFileName))
		{
			cout << "Break";
		}

		cout << "Done " << i << endl;
	}
	return 0;
}
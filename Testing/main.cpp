#include <iostream>
#include <vector>
#include <string>

#include "ScaleImage.h"

using namespace std;

void MakeCopyOf(const string &path, const vector<string> &fileNames);
void SampleFile(const string& path, const vector<string> &fileNames, TGA::ScaleImage::ALGO_TYPE type);

int main()
{
	string path = R"(D:\Varun\Aristocrat_LapTop_BackUp_Jan_2021\Interviews_2021\StarStable\StarStableRounds\ScalingAlgorithm\src\)";
	vector<string> vfileNames{ "version_1_BottomLeft.tga" , "version_1_TopLeft.tga", "version_2_TopLeft.tga", "version_2_BottomLeft.tga", "version_2_RLE_TopLeft.tga", "version_2_RLE_BottomLeft.tga" };
	
	//vector<string> vfileNames{ "version_1_BottomLeft.tga", "version_1_TopLeft.tga" };
	//vector<string> vfileNames{ "version_2_RLE_TopLeft.tga" };

	MakeCopyOf(path, vfileNames);

	SampleFile(path, vfileNames, TGA::ScaleImage::ALGO_TYPE::NEAREST_NEIGHBOUR);
	SampleFile(path, vfileNames, TGA::ScaleImage::ALGO_TYPE::BILINEAR);
	
	return 0;
}

void SampleFile(const string& path, const vector<string> &vfileNames, TGA::ScaleImage::ALGO_TYPE type)
{
	int scalePercent = 50;
	std::cout << "Enter percentage to scale to : ";
	std::cin >> scalePercent;

	for (size_t i = 0; i < vfileNames.size(); ++i)
	{
		string fileName = path + vfileNames[i];

		TGA::ScaleImage scaleImage;

		scaleImage.scale(fileName, type, scalePercent);

		cout << "Done " << i << endl;
	}
}

void MakeCopyOf(const string& path, const vector<string> &vfileNames)
{
	for (size_t i = 0; i < vfileNames.size(); ++i)
	{
		string fileName = vfileNames[i];
		TGA::TGAFile file;

		if (!file.decode(path + fileName))
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
}
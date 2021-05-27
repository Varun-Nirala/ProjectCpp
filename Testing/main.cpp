#include <iostream>
#include <vector>
#include <string>

#include "ScaleImage.h"

using namespace std;

void MakeCopyOf(const string &path, const vector<string> &fileNames);
void SampleFile(const string& path, const vector<string> &fileNames, TGA::ScaleImage::ALGO_TYPE type);

void printUsage()
{
	string usage = R"(
Usage       : scaleImage.exe file percentage algorithm

Description : Read a targa file and save a scaled copy of the image at the same locaton with new name.
              By default image is scaled to 50 percent using the nearest neighbour algorithm.
              Excepted image extensions are tga, icb, vda and vst.

              file (required)
                 [string] this should be full path with filename and extension.
                 Example : D:\User\Files\image_name.tga

              percentage (optional)
                 [integer] this is the percentage by which we need to scale.
                 If none provided default 50 will be used.

             algorithm (optional)
                 [integer] this is the option to specify which algorithm we want to be used.
                 0 -> Nearest neighbour
                 1 -> Bilinear interpolation
                 3 -> Create two copy by using both algorithms

Options :
   -h
       Print this help.

Example :
     D:\User\Files\image_name.tga
     D:\User\Files\image_name.tga 150
     D:\User\Files\image_name.tga 200 0
     D:\User\Files\image_name.tga 50 1
)";

	puts(usage.c_str());
}

int main(int argc, char *argv[])
{
	if (argc < 2 || strcmp(argv[1], "-h") == 0)
	{
		printUsage();
		return 0;
	}

	string filepath(argv[1]);

	std::cout << "File : " << filepath << '\n';

	int percent = 50;
	int algo = 0;
	
	if (argc > 2 && argc <= 4)
	{
		try
		{
			percent = stoi(argv[3]);
			if (argc == 4)
				algo = stoi(argv[4]);
		}
		catch (std::exception &e)
		{
			puts(e.what());
			return 1;
		}
	}

	TGA::ScaleImage scaleImage;
	switch (algo)
	{
		case 0:
			scaleImage.scale(filepath, TGA::ScaleImage::ALGO_TYPE::NEAREST_NEIGHBOUR, percent);
			break;
		case 1:
			scaleImage.scale(filepath, TGA::ScaleImage::ALGO_TYPE::BILINEAR, percent);
			break;
		case 3:
			scaleImage.scale(filepath, TGA::ScaleImage::ALGO_TYPE::NEAREST_NEIGHBOUR, percent);
			scaleImage.scale(filepath, TGA::ScaleImage::ALGO_TYPE::BILINEAR, percent);
			break;
	default:
		break;
	}
	return 0;
}
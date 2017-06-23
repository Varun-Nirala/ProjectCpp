
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <dirent.h>

using namespace std;

/*	Dirent structure for refereence
struct dirent {
	ino_t d_ino;				//	inode number
	off_t d_off;				//	offset to the next dirent
	unsigned short d_reclen;	//	length of this record
	unsigned char d_type;		//	type of file
	char d_name[256];			//	filename
};	*/

int GetAllFilesInAdir(const string &path, vector<string> &vec_files);
string FormatPath(const string &path);
string ExtractFileNameAsString(struct dirent *ent);
bool AddIntroOutroLogToFile(const string &szfileName, const vector<string> &v_funcToExclude);

int main(int argc, char const *argv[])
{
	vector<string> vec_files;

	//string path = R"(D:\Varun\Varun_Work\GitHubRepos\NiralaVarun\ProjectCpp\trunk\CppFiles_Project)";
	string path(argv[1]);

	string covertedPath = FormatPath(path);

	if(EXIT_FAILURE == GetAllFilesInAdir(covertedPath, vec_files))
	{
		cout << "Error :: Openingdir.\n";
		return 1;
	}

	GetAllFilesInAdir(covertedPath, vec_files);

	vector<string> v_funcToExclude;
	vector<string>::iterator it;
	for(it = vec_files.begin(); it != vec_files.end(); ++it)
	{
		string fileName = *it;
		if(AddIntroOutroLogToFile(fileName, v_funcToExclude))
		{
			cout << "SUCCESS :: Successfully Added to File : " << fileName << endl;
		}
		else
		{
			cout << "ERROR   :: Successfully Added to File : " << fileName << endl;
		}
	}

	cin.get();
	return 0;
}

/*************************************************************************
*	@Function	:	bool AddIntroOutroLogToFile(const string &szfileName, 
*					const vector<string> &v_funcToExclude)
*	@breif		:	Add Intro and Exit Log to All Func, except those in @param2
*	@Param1		:	FileName to modify
*	@Param2		:	reference to a vector of string which hold the function to exclude
*
*	@return		:	SUCCESS or FAILURE
*************************************************************************/
bool AddIntroOutroLogToFile(const string &szfileName, const vector<string> &v_funcToExclude)
{
	
}

/*************************************************************************
*	@Function	:	int GetAllFilesInAdir(const string &path, vector<string> &vec_files)
*	@breif		:	Store all files present in the directory path provided in @Param1
*	@Param1		:	Absolute path of the directory
*	@Param2		:	reference to a vector of string to hold the file names
*
*	@return		:	SUCCESS or FAILURE
*************************************************************************/
int GetAllFilesInAdir(const string &path, vector<string> &vec_files)
{
	DIR *dir = NULL;
	struct dirent *ent = NULL;

	if ((dir = opendir(path.c_str())) != NULL)
	{
  		while ((ent = readdir(dir)) != NULL)
  		{
  			vec_files.push_back(ExtractFileNameAsString(ent));
		}
  		closedir(dir);
	}
	else
	{
  		/* could not open directory */
  		cout << "Error opening directory." << endl;
  		return EXIT_FAILURE;
	}
return EXIT_SUCCESS;
}

/*************************************************************************
*	@Function	:	string FormatPath(const string &path)
*	@breif		:	formats the path according to the windows, i.e replaces '\' with '\\'
*	@Param1		:	path to format
*
*	@return		:	formatted string path
*************************************************************************/
string FormatPath(const string &path)
{
	string convertedPath;

	for(char ch : path)
	{
		if(ch == '\\')
		{
			convertedPath.push_back('\\');
			convertedPath.push_back('\\');
		}
		else
		{
			convertedPath.push_back(ch);
		}
	}
return convertedPath;
}

/*************************************************************************
*	@Function	:	string ExtractFileNameAsString(struct dirent *ent)
*	@breif		:	extract the file name (fixed length char array) from
*					dirent struct and convert it to string
*	@Param1		:	dirent structure pointer
*
*	@return		:	string
*************************************************************************/
string ExtractFileNameAsString(struct dirent *ent)
{
	string fileName(ent->d_name);
return fileName;
}
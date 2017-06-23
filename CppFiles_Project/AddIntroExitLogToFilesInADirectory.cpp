
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

int GetAllFilesInAdir(const string &szPath, vector<string> &vec_files);

string FormatPath(const string &szPath);

string ExtractFileNameAsString(struct dirent *ent);

bool AddIntroOutroLogToFile(const string &szfileName, const string &szIntroLogPrefix,
			const string &szOutroLogPrefix, const vector<string> &v_funcToExclude);


int main(int argc, char const *argv[])
{
	vector<string> vec_files;

	//string szPath = R"(D:\Varun\Varun_Work\GitHubRepos\NiralaVarun\ProjectCpp\trunk\CppFiles_Project)";
	string szPath(argv[1]);
	string szIntroLogPrefix(argv[2]);
	string szOutroLogPrefix(argv[3]);

	string szConvertedPath = FormatPath(szPath);

	if(EXIT_FAILURE == GetAllFilesInAdir(szConvertedPath, vec_files))
	{
		cout << "Error :: Openingdir.\n";
		return 1;
	}

	GetAllFilesInAdir(szConvertedPath, vec_files);

	vector<string> v_funcToExclude;
	vector<string>::iterator it;
	for(it = vec_files.begin(); it != vec_files.end(); ++it)
	{
		string szFileName = *it;
		if(AddIntroOutroLogToFile(szFileName, szIntroLogPrefix, szOutroLogPrefix, v_funcToExclude))
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
*						const string &szIntroLogPrefix,	const string &szOutroLogPrefix,
*						const vector<string> &v_funcToExclude)
*	@breif		:	Add Intro and Exit Log to All Func, except those in @param4
*	@Param1		:	FileName to modify
*	@Param2		:	String to use as prefix in Log while entering a Function
*	@Param3		:	String to use as prefix in Log while exiting a Function
*	@Param4		:	reference to a vector of string which hold the function to exclude
*
*	@return		:	SUCCESS or FAILURE
*************************************************************************/
bool AddIntroOutroLogToFile(const string &szfileName, const string &szIntroLogPrefix,
				const string &szOutroLogPrefix, const vector<string> &v_funcToExclude)
{
	
}

/*************************************************************************
*	@Function	:	int GetAllFilesInAdir(const string &szPath, vector<string> &vec_files)
*	@breif		:	Store all files present in the directory path provided in @Param1
*	@Param1		:	Absolute path of the directory
*	@Param2		:	reference to a vector of string to hold the file names
*
*	@return		:	SUCCESS or FAILURE
*************************************************************************/
int GetAllFilesInAdir(const string &szPath, vector<string> &vec_files)
{
	DIR *dir = NULL;
	struct dirent *ent = NULL;

	if ((dir = opendir(szPath.c_str())) != NULL)
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
*	@Function	:	string FormatPath(const string &szPath)
*	@breif		:	formats the path according to the windows, i.e replaces '\' with '\\'
*	@Param1		:	path to format
*
*	@return		:	formatted string path
*************************************************************************/
string FormatPath(const string &szPath)
{
	string szConvertedPath;

	for(char ch : szPath)
	{
		if(ch == '\\')
		{
			szConvertedPath.push_back('\\');
			szConvertedPath.push_back('\\');
		}
		else
		{
			szConvertedPath.push_back(ch);
		}
	}
return szConvertedPath;
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
	string szFileName(ent->d_name);
return szFileName;
}
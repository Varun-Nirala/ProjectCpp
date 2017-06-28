
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <dirent.h>

using namespace std;

#define USE_ARGS_PARAMETERS

/*	Dirent structure for refereence
struct dirent {
	ino_t d_ino;				//	inode number
	off_t d_off;				//	offset to the next dirent
	unsigned short d_reclen;	//	length of this record
	unsigned char d_type;		//	type of file
	char d_name[256];			//	filename
};	*/

typedef enum
{
	E_CT_NO_COMMENT = 0,
	E_CT_SINGLE_LINE_START,
	E_CT_SINGLE_LINE_MID,
	E_CT_MULTI_LINE_START,
	E_CT_MULTI_LINE_START_MID,
	E_CT_MULTI_LINE_END_START,
	E_CT_MULTI_LINE_END_MID,
	E_CT_MULTI_LINE_ENDINALINE,				// Handle it carefully
	E_CT_SINGLE_MULTI_AND_CODE,				// Handle it carefully
}E_COMMENT_TYPE;

int GetAllFilesInAdir(const string &szPath, vector<string> &vec_files);

string FormatPath(const string &szPath);

string ExtractFileNameAsString(struct dirent *ent);

bool AddIntroOutroLogToFile(const string &szfileName, const string &szIntroLogPrefix,
			const string &szOutroLogPrefix, const vector<string> &v_funcToExclude);

bool GetAllLinesOfFiles(fstream &myFileStream, vector<string> &v_fileLines, int FromLine = 0);

E_COMMENT_TYPE HasCommentChars(string &szLine, int &position);


/*************************************************************************
*	@Function	:	int main(int argc, char const *argv[])
*	@breif		:	Enter point of Execution
*	@Param1		:	number of command line argument + 1(exe file name)
*	@Param2		:	Array or char*, size = @Param1, All command line arguments as character array
*
*	@return		:	SUCCESS or FAILURE
*************************************************************************/
int main(int argc, char const *argv[])
{
	vector<string> vec_files;

#ifndef USE_ARGS_PARAMETERS
	string szPath = R"(D:\Varun\Varun_Work\GitHubRepos\NiralaVarun\ProjectCpp\trunk\CppFiles_Project)";
	string szIntroLogPrefix("VARUN_LOGGING_ENTER");
	string szOutroLogPrefix("VARUN_LOGGING_EXIT");
#else
	string szPath(argv[1]);
	string szIntroLogPrefix(argv[2]);
	string szOutroLogPrefix(argv[3]);
#endif

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
			cout << "SUCCESS :: Successfully Added to File : " << szFileName << endl;
		}
		else
		{
			cout << "ERROR   :: Error Addeding to File : " << szFileName << endl;
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
	bool rc = true;
	fstream myFileStream;
	myFileStream.open(szfileName);

	if(myFileStream.is_open())
	{
		vector<string> v_fileLines;
		GetAllLinesOfFiles(myFileStream, v_fileLines);

		string szfileLine;
		int pos;
		bool bInAMultiComment = false;
		for(int i = 0; i < v_fileLines.size(); ++i)
		{
			szfileLine = v_fileLines[i];
			
			/* 	@TODO : Main processing Start here
			*	->	identify if this line is a comment or part of a comment or contain a comment
			*	->	Case 1 : If it's a part of multi-line comment
			*					then ->  Simply Skip this line and comming line until multi-line comment doesn't end
			*	->	Case 2 : If it's a single line comment, but whole line is comment
			*					then -> Skip whole line
			*	->	Case 3 : If it's a Single/multi line comment but it start or end in this line, i.e line contain uncommented data(compilable code)
			*					then -> Find if a function START/END in this line
			*	->  Case 4 : No comment start in it, whole line is a compilable line.
			*					then -> Find if a function START/END in this line
			*	If Function Starts : 
			*		then -> Add szIntroLogPrefix Line in vector before this index
			*	If Funcion Ends :
			*		then -> Add szOutroLogPrefix Line in vector before this index
			*/

			E_COMMENT_TYPE e_CommentType = HasCommentChars(szfileLine, pos);
			switch(e_CommentType)
			{
				case E_CT_NO_COMMENT :
					cout << "INFO 	:: No Comment." << endl;
					break;

				case E_CT_SINGLE_LINE_START :
					cout << "INFO 	:: Single Line Comment(Whole Line)." << endl;
					break;

				case E_CT_SINGLE_LINE_MID :
					cout << "INFO 	:: Single Line Comment(In Mid)." << endl;
					break;

				case E_CT_MULTI_LINE_START:
					if(!bInAMultiComment)
					{
						bInAMultiComment = true;
					}
					else
					{
						cout << "ERROR   :: MultiLine Comment Start Error : Line : " << szfileLine << endl;
					}
					cout << "INFO 	:: Multi Line Comment(Start)." << endl;
					break;

				case E_CT_MULTI_LINE_START_MID:
					if(!bInAMultiComment)
					{
						bInAMultiComment = true;
					}
					else
					{
						cout << "ERROR   :: MultiLine Comment Start Error : Line : " << szfileLine << endl;
					}
					cout << "INFO 	:: Multi Line Comment(Start In Mid)." << endl;
					break;

				case E_CT_MULTI_LINE_END_START :
					if(bInAMultiComment)
					{
						bInAMultiComment = false;
					}
					else
					{
						cout << "ERROR   :: MultiLine Comment End Error : Line : " << szfileLine << endl;
					}
					cout << "INFO 	:: Multi Line Comment End(Start)." << endl;
					break;

				case E_CT_MULTI_LINE_END_MID :
					if(bInAMultiComment)
					{
						bInAMultiComment = false;
					}
					else
					{
						cout << "ERROR   :: MultiLine Comment End Error : Line : " << szfileLine << endl;
					}
					cout << "INFO 	:: Multi Line Comment End(In Mid)." << endl;
					break;

				case E_CT_MULTI_LINE_ENDINALINE :
					cout << "INFO 	:: Multi Line Comment Start and End(In A Line)." << endl;
					break;

				case E_CT_SINGLE_MULTI_AND_CODE :
					cout << "INFO 	:: Multi/Single Line Comment Start and End(In A Line)." << endl;
					break;

				default :
					cout << "INFO 	:: Unhandled Situation." << endl;
					break;
			}
		}

		/*	@TODO : Create A new file With Same name as "szfileName" but with added Prefix "_Modified" ("szfileName_Modified.cpp/h") with
		*			all the lines in the vector "v_fileLines"
		*/
	}
	else
	{
		cout << "ERROR :: Error opening File  :: " << szfileName << endl;
		rc = false;
	}
	return rc;
}

E_COMMENT_TYPE HasCommentChars(string &szLine, int &position)
{
	static vector<string> v_commentStrings{ "/*", "*/", "//" };
	int pos_multiStart = -1, pos_multiEnd = -1, pos_singleStart = -1, pos = 0;

	for(int i = 0; i < v_commentStrings.size(); ++i)
	{
		pos = szLine.find(v_commentStrings[i]);
		if(string::npos != pos)
		{
			switch(i)
			{
				case 0 :
					pos_multiStart = pos;
					break;
				case 1 :
					pos_multiEnd = pos;
					break;
				case 2 :
					pos_singleStart = pos;
					break;
			}
		}
	}

	E_COMMENT_TYPE e_CommentType;

	if(pos_singleStart == -1 && pos_multiStart == -1 && pos_multiEnd == -1)
	{
		e_CommentType = E_CT_NO_COMMENT;
		position = -1;
	}
	else if(pos_multiStart == -1 && pos_multiEnd == -1)
	{
		if(pos_singleStart == 0)
		{
			e_CommentType = E_CT_SINGLE_LINE_START;
		}
		else
		{
			e_CommentType = E_CT_SINGLE_LINE_MID;		
		}
		position = pos_multiStart;
	}
	else if(pos_singleStart == -1 && pos_multiEnd == -1)
	{
		if(pos_multiStart == 0)
		{
			e_CommentType = E_CT_MULTI_LINE_START;
		}
		else
		{
			e_CommentType = E_CT_MULTI_LINE_START_MID;		
		}
		position = pos_multiStart;
	}
	else if(pos_singleStart == -1 && pos_multiStart == -1)
	{
		if(pos_multiEnd == 0)
		{
			e_CommentType = E_CT_MULTI_LINE_END_START;
		}
		else
		{
			e_CommentType = E_CT_MULTI_LINE_END_MID;
		}
		position = pos_multiEnd;
	}
	else if(pos_singleStart == -1)
	{
		e_CommentType = E_CT_MULTI_LINE_ENDINALINE;
		position = pos_multiEnd;
	}
	else
	{
		e_CommentType = E_CT_SINGLE_MULTI_AND_CODE;
		(pos_singleStart > pos_multiEnd) ? position = pos_singleStart : position = pos_multiEnd;
	}
	return e_CommentType;
}

bool GetAllLinesOfFiles(fstream &myFileStream, vector<string> &v_fileLines, int FromLine)
{
	// Add proper error checking
	string szFileLine;
	while(getline(myFileStream, szFileLine))
	{
		if(FromLine == 0)
		{
			v_fileLines.push_back(szFileLine);
		}
		else
		{
			FromLine--;
		}
	}
	return true;
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
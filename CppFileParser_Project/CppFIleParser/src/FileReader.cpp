#include <iostream>
#include <dirent.h>
#include <algorithm>
#include "FileReader.h"
#include "helper.h"

using namespace std;

// PUBLIC MEMBERS
FileData::FileData(const string &sFilepath)
{
	Initialize(sFilepath);
}

FileData::~FileData()
{
	Release();
}

string FileData::GetFileName()
{
	return m_sFileName;
}

bool FileData::Rename(const string &sNewName)
{
}

int FileData::GetSize()
{
	return m_vFileLines.size();
}

string FileData::GetLine(int lineNumber)
{
	if(ValidRange(lineNumber))
	{
		return m_vFileLines[lineNumber];
	}
	else
	{
		// TODO::LOG_ERROR
	}
	return "";
}

bool FileData::Replace(const string &sSrc, const string &sDst, bool bAllMatch, bool bCaseSensitiveSearch)
{
}

bool FileData::AddAfter(int lineNumber, const string &sStatement)
{
}

bool FileData::AddAfter(const string &sSearchLine, const string &sStatement)
{
}

bool FileData::AddBefore(int lineNumber, const string &sStatement)
{
}

bool FileData::AddBefore(const string &sSearchLine, const string &sStatement)
{
}

bool FileData::Remove(int lineNumber)
{
	if(ValidRange(lineNumber))
	{
		m_vFileLines.erase(m_vFileLines.begin() + lineNumber);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileData::Remove(const string &sSearchLine)
{
	int lineNumber = SearchLine(sSearchLine);

	if(lineNumber >= 0)
	{
		m_vFileLines.erase(m_vFileLines.begin() + lineNumber);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileData::SaveEditedData()
{
}


// PROTECTED MEMBERS
void FileData::Initialize(const string &sFilepath)
{
	m_sFileName = ExtractFileName(sFilepath);
	ReadFileData();
}

string FileData::ExtractFileName(const string &sFilePath)
{
	string sFileName;
	if(sFilePath.empty())
	{
		//TODO::Throw exception
		return "";
	}
	else
	{
		int matchIndex = sFilePath.find('\\');
		if(matchIndex != string::npos)
		{
			// USE ALGORITHM's COPY FUNCTIONALITY
		}
		else
		{
			sFileName = sFilePath;
		}
	}
	return sFileName;
}

void FileData::Release()
{
}

bool FileData::ReadFileData()
{
	// TODO:: Do Error Checking
	m_fstream.open(m_sFileName);

	string sFileLine;
	while(getline(m_fstream, sFileLine))
	{
		m_vFileLines.push_back(sFileLine);
	}
	return true;
}

int FileData::SearchLine(const string &sSrc)
{
}

bool FileData::SearchLine(const string &sSrc, vector<int> &v_SearchIndexes)
{
}


// PRIVATE MEMBERS
bool FileData::ValidRange(int lineNumber)
{
	return (lineNumber >=0 && lineNumber < GetSize());
}
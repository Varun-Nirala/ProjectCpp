#include <iostream>
#include <dirent.h>
#include <algorithm>
#include "FileHandler.h"
#include "helper.h"

using namespace std;

// PUBLIC MEMBERS
FileHandler::FileHandler(const string &sFilepath)
{
	Initialize(sFilepath);
}

FileHandler::~FileHandler()
{
	Release();
}

string FileHandler::GetFileName() const
{
	return m_sFileName;
}

bool FileHandler::Rename(const string &sNewName)
{
}

size_t FileHandler::GetSize() const
{
	return m_vFileLines.size();
}

string FileHandler::GetLine(int lineNumber) const
{
	if(ValidRange(lineNumber))
	{
		return m_vFileLines[lineNumber];
	}
	else
	{
		// TODO::LOG_ERROR
		LOG_ERROR("Provided linenumber is not in valid range.");
	}
	return "";
}

bool FileHandler::Replace(const string &sSrc, const string &sDst, bool bAllMatch, bool bCaseSensitiveSearch)
{
	bool bRc = true;
	if(bAllMatch)
	{
		vector<int> v_SearchIndexes;
		if(SearchLine(sSrc, v_SearchIndexes, bCaseSensitiveSearch))
		{
			// TODO
		}
		else
		{
			LOG_INFO("Match not found");
			bRc = false;
		}
	}
	else
	{
		int matchIndex = SearchLine(sSrc, bCaseSensitiveSearch);

		if(matchIndex != -1)
		{
			m_vFileLines[matchIndex] = sSrc;
		}
		else
		{
			LOG_INFO("Match not found");
			bRc = false;
		}
	}
	return bRc;
}

bool FileHandler::AddAfter(int lineNumber, const string &sStatement)
{
	if(ValidRange(lineNumber))
	{
		lineNumber++;
		// TODO::Test boundary condition specially end one
		m_vFileLines.insert(m_vFileLines.begin() + lineNumber, sStatement);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileHandler::AddAfter(const string &sSearchLine, const string &sStatement)
{
	int index = SearchLine(sSearchLine);

	if(index != -1)
	{
		AddAfter(index, sSearchLine);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileHandler::AddBefore(int lineNumber, const string &sStatement)
{
	if(ValidRange(lineNumber))
	{
		if(lineNumber > 0)	// TO handle when 0 is passed
		{
			lineNumber--;
		}
		// TODO::Test boundary condition specially end one
		m_vFileLines.insert(m_vFileLines.begin() + lineNumber, sStatement);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileHandler::AddBefore(const string &sSearchLine, const string &sStatement)
{
	int index = SearchLine(sSearchLine);

	if(index != -1)
	{
		AddBefore(index, sSearchLine);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileHandler::Remove(int lineNumber)
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

bool FileHandler::Remove(const string &sSearchLine)
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

bool FileHandler::SaveEditedData()
{
}


// PROTECTED MEMBERS
void FileHandler::Initialize(const string &sFilepath)
{
	if(ReadFileHandler(sFilepath))
	{
		m_sFileName = ExtractFileName(sFilepath);
	}
	else
	{
		m_vFileLines.clear();
	}
}

string FileHandler::ExtractFileName(const string &sFilePath)
{
	string sFileName;
	if(sFilePath.empty())
	{
		LOG_ERROR("Provided filepath is empty.");
		//TODO::Throw exception
		return "";
	}
	else
	{
		int matchIndex = sFilePath.rfind('\\') + 1;
		if(matchIndex != string::npos)
		{
			// USE ALGORITHM's COPY FUNCTIONALITY
			for(matchIndex; matchIndex < sFilePath.size(); matchIndex++)
			{
				sFileName.push_back(sFilePath[matchIndex]);
			}
		}
		else
		{
			sFileName = sFilePath;
		}
	}
	return sFileName;
}

void FileHandler::Release()
{
	SaveEditedData();
	m_fstream.close();
}

bool FileHandler::ReadFileHandler(const string &sFilepath)
{
	// TODO:: Do Error Checking
	m_fstream.open(sFilepath);

	if(m_fstream.is_open())
	{
		string sFileLine;
		while(getline(m_fstream, sFileLine))
		{
			m_vFileLines.push_back(sFileLine);
		}
		return true;
	}
	else
	{
		LOG_ERROR("Error in opening file." + sFilepath);
		return false;
	}
}

int FileHandler::SearchLine(const string &sSrc, bool bCaseSensitiveSearch)
{
	string sTarget;
	if(bCaseSensitiveSearch)
	{
		sTarget = sSrc;
	}
	else
	{
		// TODO:: to conversion
	}

	// MainCode for searching
	return 0;
}

bool FileHandler::SearchLine(const string &sSrc, vector<int> &v_SearchIndexes, bool bCaseSensitiveSearch)
{
}

void FileHandler::Display() const
{
	size_t size = GetSize();
	cout << "FileName       := " << m_sFileName;
	cout << "\nNumber of line := " << size;
	cout << "\n\nFile          :=\n\n******************* START ********************\n\n";


	for(size_t i = 0; i < size; i++)
	{
		cout << GetLine(i) << "\n";
	}

	cout << "\n\n******************** END *********************" << endl;
}

// PROTECTED FRIEND FUNCTION
ostream& operator<< (ostream &out, const FileHandler &fileHandler)
{
	fileHandler.Display();
	return out;
}

// PRIVATE MEMBERS
bool FileHandler::ValidRange(int lineNumber) const
{
	return (lineNumber >=0 && lineNumber < GetSize());
}
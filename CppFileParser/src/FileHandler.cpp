#include <iostream>
#include <dirent.h>
#include <algorithm>
#include <functional>
#include "FileHandler.h"
#include "helper.h"

namespace ALL_USING
{
	using std::string;
	using std::cout;
	using std::endl;
	using std::vector;
}

using namespace ALL_USING;

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

string FileHandler::GetFilePath() const
{
	return m_sFilePath;
}

bool FileHandler::Rename(const string &sNewName)
{
	bool bRc = true;
	if(SaveEditedData())
	{
		std::fstream m_fstream;
		if(m_fstream.is_open())
		{
			m_fstream.close();
			if(rename(GetFileNameFormRoot().c_str(), sNewName.c_str()))
			{
				LOG_INFO("File renamed");
				m_fstream.open(GetFileNameFormRoot());
				bRc = true;
			}
		}
		else
		{
			LOG_ERROR("No file is currently open.");
		}
	}
	else
	{
		LOG_ERROR("File can't be saved.");
		bRc = false;
	}
	return bRc;
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
			size_t i = 0;
			size_t max = v_SearchIndexes.size();

			for(i = 0; i < max; i++)
			{
				m_vFileLines[v_SearchIndexes[i]] = sDst;
			}
		}
		else
		{
			LOG_ERROR("Target string not found.");
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
			LOG_ERROR("Target string not found.");
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
		LOG_ERROR("Target string not found.");
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
		LOG_ERROR("Target string not found.");
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
		LOG_ERROR("Target string not found.");
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
		LOG_ERROR("Target string not found.");
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
		LOG_ERROR("Target string not found.");
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
		LOG_ERROR("Target string not found.");
		return false;
	}
}

bool FileHandler::SaveEditedData()
{
	// Empty files current content
	std::ofstream fileStream;
	fileStream.open(GetFileNameFormRoot(), std::ofstream::out | std::ofstream::trunc);
	if(fileStream.is_open())
	{
		for(const std::string &sFileLines : m_vFileLines)
		{
			fileStream << sFileLines;
		}
		fileStream.close();
	}
	return true;
}


// PROTECTED MEMBERS
void FileHandler::Initialize(const string &sFilepath)
{
	if(ReadFileData(sFilepath))
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
	}
	else
	{
		unsigned int matchIndex = sFilePath.rfind('\\') + 1;
		if(matchIndex != string::npos)
		{
			m_sFilePath = sFilePath.substr(0, matchIndex);
			sFileName = sFilePath.substr(matchIndex);
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
}

bool FileHandler::ReadFileData(const string &sFilepath)
{
	// TODO:: Do Error Checking
	std::fstream m_fstream;
	m_fstream.open(sFilepath);

	if(m_fstream.is_open())
	{
		string sFileLine;
		while(getline(m_fstream, sFileLine))
		{
			m_vFileLines.push_back(sFileLine + "\n");
		}
		m_fstream.close();
		return true;
	}
	else
	{
		LOG_ERROR("Error in opening file." + sFilepath);
		m_fstream.close();
		return false;
	}
}

int FileHandler::SearchLine(const string &sSrc, bool bCaseSensitiveSearch)
{
	if(bCaseSensitiveSearch)
	{
		vector<string>::iterator it = find(m_vFileLines.begin(), m_vFileLines.end(), sSrc);
		return (it - m_vFileLines.begin());
	}
	else
	{
		string sSource;
		transform(sSrc.begin(), sSrc.end(), sSource.begin(), ::tolower);

		struct CompareIt compareIt;

		std::function<bool (string)> compareFunc = std::bind(&CompareIt::CompareCaseInSensitive, &compareIt, sSource, std::placeholders::_1);

		vector<string>::iterator it;
		find_if(m_vFileLines.begin(), m_vFileLines.end(), compareFunc);
		return (it - m_vFileLines.begin());
	}
	return 0;
}

bool FileHandler::SearchLine(const string &sSrc, vector<int> &v_SearchIndexes, bool bCaseSensitiveSearch)
{
	string sSource;
	bool bRc = false;

	if(bCaseSensitiveSearch)
	{
		sSource = sSrc;
	}
	else
	{
		std::transform(sSrc.begin(), sSrc.end(), sSource.begin(), ::tolower);
	}

	CompareIt compareIt;
	vector<string>::iterator it;
	
	for(it = m_vFileLines.begin(); it != m_vFileLines.end(); ++it)
	{
		if(compareIt.CompareCaseInSensitive(sSource, *it))
		{
			v_SearchIndexes.push_back(it - m_vFileLines.begin());
			if(!bRc)
			{
				bRc = true;	// Return true if even one match is found
			}
		}
	}
	return bRc;
}

void FileHandler::Display() const
{
	size_t size = GetSize();
	cout << "FileName       := " << m_sFileName;
	cout << "\nFilPath        := " << m_sFilePath;
	cout << "\nNumber of line := " << size;
	cout << "\n\nFile           :=\n\n******************* START ********************\n";

	for(size_t i = 0; i < size; i++)
	{
		cout << GetLine(i);
	}

	cout << "******************** END *********************" << endl;
}

// PROTECTED FRIEND FUNCTION
std::ostream& operator<< (std::ostream &out, const FileHandler &fileHandler)
{
	fileHandler.Display();
	return out;
}

// PRIVATE MEMBERS
bool FileHandler::ValidRange(int lineNumber) const
{
	return (lineNumber >=0 && static_cast<unsigned int>(lineNumber) < GetSize());
}

string FileHandler::GetFileNameFormRoot()
{
	return m_sFilePath + "\\" + m_sFileName;
}

bool FileHandler::CompareIt::CompareCaseInSensitive(string sFirst, string sSecond)
{
	string sTarget;
	std::transform(sSecond.begin(), sSecond.end(), sTarget.begin(), ::tolower);
	return (sFirst == sSecond);
}
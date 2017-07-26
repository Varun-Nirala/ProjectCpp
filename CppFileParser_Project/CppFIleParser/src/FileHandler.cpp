#include <iostream>
#include <dirent.h>
#include <algorithm>
//#include <cstdio>
#include <functional>
#include "FileHandler.h"
#include "helper.h"

// PUBLIC MEMBERS
FileHandler::FileHandler(const std::string &sFilepath)
{
	Initialize(sFilepath);
}

FileHandler::~FileHandler()
{
	Release();
}

std::string FileHandler::GetFileName() const
{
	return m_sFileName;
}

std::string FileHandler::GetFilePath() const
{
	return m_sFilePath;
}

bool FileHandler::Rename(const std::string &sNewName)
{
	bool bRc = true;
	if(SaveEditedData())
	{
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

std::string FileHandler::GetLine(int lineNumber) const
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

bool FileHandler::Replace(const std::string &sSrc, const std::string &sDst, bool bAllMatch, bool bCaseSensitiveSearch)
{
	bool bRc = true;
	if(bAllMatch)
	{
		std::vector<int> v_SearchIndexes;
		if(SearchLine(sSrc, v_SearchIndexes, bCaseSensitiveSearch))
		{
			// TODO
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

bool FileHandler::AddAfter(int lineNumber, const std::string &sStatement)
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

bool FileHandler::AddAfter(const std::string &sSearchLine, const std::string &sStatement)
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

bool FileHandler::AddBefore(int lineNumber, const std::string &sStatement)
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

bool FileHandler::AddBefore(const std::string &sSearchLine, const std::string &sStatement)
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

bool FileHandler::Remove(const std::string &sSearchLine)
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
	if(m_fstream.is_open())
	{
		m_fstream.close();
		
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
		m_fstream.open(GetFileNameFormRoot());
		return true;
	}
	else
	{
		LOG_ERROR("No file is currently open.");
		return false;
	}
}


// PROTECTED MEMBERS
void FileHandler::Initialize(const std::string &sFilepath)
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

std::string FileHandler::ExtractFileName(const std::string &sFilePath)
{
	std::string sFileName;
	if(sFilePath.empty())
	{
		LOG_ERROR("Provided filepath is empty.");
		//TODO::Throw exception
	}
	else
	{
		unsigned int matchIndex = sFilePath.rfind('\\') + 1;
		if(matchIndex != std::string::npos)
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
	m_fstream.close();
}

bool FileHandler::ReadFileData(const std::string &sFilepath)
{
	// TODO:: Do Error Checking
	m_fstream.open(sFilepath);

	if(m_fstream.is_open())
	{
		std::string sFileLine;
		while(getline(m_fstream, sFileLine))
		{
			m_vFileLines.push_back(sFileLine + "\n");
		}
		return true;
	}
	else
	{
		LOG_ERROR("Error in opening file." + sFilepath);
		return false;
	}
}

int FileHandler::SearchLine(const std::string &sSrc, bool bCaseSensitiveSearch)
{
	if(bCaseSensitiveSearch)
	{
		std::vector<std::string>::iterator it = find(m_vFileLines.begin(), m_vFileLines.end(), sSrc);
		return (it - m_vFileLines.begin());
	}
	else
	{
		std::string sSource;
		transform(sSrc.begin(), sSrc.end(), sSource.begin(), ::tolower);

		struct CompareIt compareIt;

		std::function<bool (std::string)> compareFunc = std::bind(&CompareIt::CompareCaseInSensitive, &compareIt, sSource, std::placeholders::_1);

		std::vector<std::string>::iterator it;
		find_if(m_vFileLines.begin(), m_vFileLines.end(), compareFunc);
		return (it - m_vFileLines.begin());
	}
	return 0;
}

bool FileHandler::SearchLine(const std::string &sSrc, std::vector<int> &v_SearchIndexes, bool bCaseSensitiveSearch)
{
	std::string sSource;
	bool bRc = true;

	if(bCaseSensitiveSearch)
	{
		sSource = sSrc;
	}
	else
	{
		std::transform(sSrc.begin(), sSrc.end(), sSource.begin(), ::tolower);
	}

	// MainCode for searching
	struct CompareIt compareIt;
	std::function<bool (std::string)> compareFunc = std::bind(&CompareIt::CompareCaseInSensitive, &compareIt, sSource, std::placeholders::_1);

	// use generate or foreach
	return bRc;
}

void FileHandler::Display() const
{
	size_t size = GetSize();
	std::cout << "FileName       := " << m_sFileName;
	std::cout << "\nFilPath        := " << m_sFilePath;
	std::cout << "\nNumber of line := " << size;
	std::cout << "\n\nFile           :=\n\n******************* START ********************\n";


	for(size_t i = 0; i < size; i++)
	{
		std::cout << GetLine(i);
	}

	std::cout << "******************** END *********************" << std::endl;
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

std::string FileHandler::GetFileNameFormRoot()
{
	return m_sFilePath + "\\" + m_sFileName;
}

bool FileHandler::CompareIt::CompareCaseInSensitive(std::string sFirst, std::string sSecond)
{
	std::string sTarget;
	std::transform(sSecond.begin(), sSecond.end(), sTarget.begin(), ::tolower);
	return (sFirst == sSecond);
}
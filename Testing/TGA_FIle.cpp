#include <iostream>
#include <iterator>
#include <algorithm>
#include "TGA_File.h"
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
TGAFile::TGAFile(const string &sFilepath)
{
	initialize(sFilepath);
}

TGAFile::~TGAFile()
{
	release();
}

string TGAFile::getFileName() const
{
	return m_sFileName;
}

string TGAFile::getFilePath() const
{
	return m_sFilePath;
}

size_t TGAFile::getSize() const
{
	return m_size;
}

//string TGAFile::getLine(int lineNumber) const
//{
//	if(ValidRange(lineNumber))
//	{
//		return m_vFileLines[lineNumber];
//	}
//	else
//	{
//		// TODO::LOG_ERROR
//		LOG_ERROR("Provided linenumber is not in valid range.");
//	}
//	return "";
//}
//
//bool TGAFile::saveEditedData()
//{
//	// Empty files current content
//	std::ofstream fileStream;
//	fileStream.open(GetFileNameFormRoot(), std::ofstream::out | std::ofstream::trunc);
//	if(fileStream.is_open())
//	{
//		for(const std::string &sFileLines : m_vFileLines)
//		{
//			fileStream << sFileLines;
//		}
//		fileStream.close();
//	}
//	return true;
//}


// PROTECTED MEMBERS
void TGAFile::initialize(const string &sFilepath)
{
	if(parse(sFilepath))
	{
		m_sFileName = extractFileName(sFilepath);
	}
	else
	{
		m_pixels.clear();
	}
}

string TGAFile::extractFileName(const string &sFilePath)
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

void TGAFile::release()
{
	//saveEditedData();
}

bool TGAFile::parse(const string& sFilepath)
{
	std::ifstream file(sFilepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file)
	{
		LOG_ERROR("Error: Opening file :: " + sFilepath + "\n");
		file.close();
		return false;
	}

	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);

	char* buffer = new char[length];

	file.read(buffer, length);

	if (!file)
	{
		LOG_ERROR("Error: Only :: " + std::to_string(file.gcount()) + " could be read" + "\n");
	}
	file.close();

	TGAHeader header;
	header.parse(buffer);

	header.display();

	char singature[17]{};

	memcpy(singature, &buffer[length - 18], 16);

	if (strncmp("TRUEVISION-XFILE", singature, 16) == 0)
	{
		m_version = 2;
	}

	return true;
}

void TGAFile::display() const
{
	size_t size = getSize();
	cout << "FileName         := " << m_sFileName << '\n';
	cout << "FilPath          := " << m_sFilePath << '\n';
	cout << "Number of line   := " << size << "\n\n";
	cout << "File             :=\n\n******************* START ********************\n";

	for(size_t i = 0; i < size; i++)
	{
		cout << m_pixels[i];
	}

	cout << "******************** END *********************" << endl;
}

// PRIVATE MEMBERS
bool TGAFile::validRange(int lineNumber) const
{
	return (lineNumber >= 0 && static_cast<unsigned int>(lineNumber) < getSize());
}

string TGAFile::getFileNameFormRoot()
{
	return m_sFilePath + "\\" + m_sFileName;
}

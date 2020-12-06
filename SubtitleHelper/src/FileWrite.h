#ifndef _FILE_WRTIE_H_
#define _FILE_WRTIE_H_

#include <string>
#include <fstream>

class FileWrite
{
public:
	explicit FileWrite(const std::string &fileName)
		:m_szFileName(fileName)
	{
		m_fileToWrite.open(fileName, std::ios::out | std::ios::trunc);
	}

	const std::string& getFileName() const
	{
		return m_szFileName;
	}

	void Write(int number)
	{
		m_fileToWrite << number;
	}

	void Write(const char* context)
	{
		m_fileToWrite << context;
	}

	void Write(const std::string &context)
	{
		m_fileToWrite << context;
	}

	void Close()
	{
		m_fileToWrite.close();
	}

	~FileWrite()
	{
		Close();
	}

public:
	const std::string	m_szFileName;
	std::ofstream		m_fileToWrite;
};

#endif //_FILE_WRTIE_H_
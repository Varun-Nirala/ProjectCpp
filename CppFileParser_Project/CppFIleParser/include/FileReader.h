#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileData
{
	public:
		FileData(const std::string &sFilepath);
		~FileData();

		std::string GetFileName();
		bool Rename(const std::string &sNewName);

		int GetSize();
		std::string GetLine(int lineNumber);

		bool Replace(const std::string &sSrc, const std::string &sDst, bool bAllMatch = false, bool bCaseSensitiveSearch = true);

		bool AddAfter(int lineNumber, const std::string &sStatement);
		bool AddAfter(const std::string &sSearchLne, const std::string  &sStatement);

		bool AddBefore(int lineNumber, const std::string &sStatement);
		bool AddBefore(const std::string &sSearchLine, const std::string &sStatement);

		bool Remove(int lineNumber);
		bool Remove(const std::string &sSearchLine);
		bool SaveEditedData();

	protected:
		void Initialize(const std::string &sFilepath);
		std::string ExtractFileName(const std::string &sFilePath);

		void Release();
		bool ReadFileData();
		int SearchLine(const std::string &sSrc);
		bool SearchLine(const std::string &sSrc, std::vector<int> &v_SearchIndexes);

	private:
		bool ValidRange(int lineNumber);

	private:
		std::vector<std::string>		m_vFileLines;
		std::fstream 					m_fstream;	// TODO : use unique pointer
		std::string 					m_sFileName;
};

#endif
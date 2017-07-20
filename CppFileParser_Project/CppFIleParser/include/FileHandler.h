#ifndef __FILEHADNLER_H__
#define __FILEHANDLER_H__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class FileHandler
{
	public:
		FileHandler(const std::string &sFilepath);
		~FileHandler();

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
		bool ReadFileHandler(const std::string &sFilepath);
		int SearchLine(const std::string &sSrc, bool bCaseSensitiveSearch = true);
		bool SearchLine(const std::string &sSrc, std::vector<int> &v_SearchIndexes, bool bCaseSensitiveSearch = true);

	private:
		bool ValidRange(int lineNumber);

	private:
		std::vector<std::string>		m_vFileLines;
		std::fstream 					m_fstream;	// TODO : use unique pointer
		std::string 					m_sFileName;
};

#endif
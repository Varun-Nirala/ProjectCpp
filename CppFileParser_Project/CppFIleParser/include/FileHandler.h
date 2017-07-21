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

		std::string GetFileName() const;
		std::string GetFilePath() const;
		bool Rename(const std::string &sNewName);

		size_t GetSize() const;
		std::string GetLine(int lineNumber) const;

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
		bool ReadFileData(const std::string &sFilepath);
		int SearchLine(const std::string &sSrc, bool bCaseSensitiveSearch = true);
		bool SearchLine(const std::string &sSrc, std::vector<int> &v_SearchIndexes, bool bCaseSensitiveSearch = true);

		virtual void Display() const;

		// FRIEND FUNCTIONS
		friend std::ostream& operator<< (std::ostream &out, const FileHandler &fileHandler);

	private:
		bool ValidRange(int lineNumber) const;
		std::string GetFileNameFormRoot();

	private:
		std::vector<std::string>		m_vFileLines;
		std::fstream 					m_fstream;	// TODO : use unique pointer
		std::string 					m_sFileName;
		std::string 					m_sFilePath;
};

#endif
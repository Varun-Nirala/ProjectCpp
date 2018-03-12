#ifndef __FILESMANAGER_H__
#define __FILESMANAGER_H__

#include <vector>
#include <map>
#include "FileHandler.h"

class FilesManager
{
	public:
		FilesManager(const std::string &sFolderPath);
		~FilesManager();

		bool ParseAllFile(const std::string &sFolderPath);
		bool AddFile(const std::string &sFileName);

		size_t GetSize() const;
		std::string GetFilePath();
		bool GetAllFilesName(std::vector<std::string> &vAllFileName);

		FileHandler& GetFileHandler(const std::string &sFileName);

		std::string GetFileNameFormRoot(const std::string &sFilename) const;

	protected:
		bool GetAllFilesInDir(const std::string &sFolderPath, std::vector<std::string> &vAllFileName);
		bool Release();

		virtual void Display() const;

		// FRIEND FUNCTIONS
		friend std::ostream& operator<< (std::ostream &out, const FilesManager &filesManager);

	private:
		std::map<std::string /* NameOfFile */, FileHandler &>	m_mFiles;
		std::string 											m_sFolderPath;
};

#endif		//__FILESMANAGER_H__
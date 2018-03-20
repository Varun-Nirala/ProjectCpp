#include <iostream>
#include <dirent.h>
#include <algorithm>
#include <functional>

#include "FilesManager.h"
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
FilesManager::FilesManager(const string &sFolderPath)
{
	ParseAllFile(sFolderPath);
};

FilesManager::~FilesManager()
{
	if(!Release())
	{
		LOG_ERROR("Error while releasing files.");
		// probabaly throw exception
	}
}

bool FilesManager::ParseAllFile(const string &sFolderPath)
{
	vector<string> vAllFileName;

	m_sFolderPath = sFolderPath;
	if(GetAllFilesInDir(sFolderPath, vAllFileName))
	{
		vector<string>::iterator it;
		for(it = vAllFileName.begin(); it != vAllFileName.end(); ++it)
		{
			if (!AddFile(*it))
			{
				string sMsg = "Error adding file :: %s." + (*it);
				LOG_ERROR(sMsg);
				return false;
			}
		}
	}
	else
	{
		LOG_ERROR("Error while reading folder/files.");
	}
	return true;
}

bool FilesManager::AddFile(const string &sFileName)
{

	FileHandler fileHandler(m_sFolderPath + R"(\)" + sFileName);

	std::pair<std::map<string ,FileHandler &>::iterator, bool> ret;
	ret = m_mFiles.insert(std::make_pair(sFileName, std::ref(fileHandler)));

	if(!ret.second)
	{
		LOG_ERROR("Error in adding file" + sFileName);
		return false;
	}
	return true;
}

size_t FilesManager::GetSize() const
{
	return m_mFiles.size();
}

string FilesManager::GetFilePath()
{
	return m_sFolderPath;
}

bool FilesManager::GetAllFilesName(vector<string> &vAllFileName)
{
	vAllFileName.clear();

	for(const std::pair<string, FileHandler &> &mPair : m_mFiles)
	{
		vAllFileName.push_back(mPair.first);
	}
	return true;
}

FileHandler& FilesManager::GetFileHandler(const string &sFileName)
{
	return m_mFiles.at(sFileName);
}

string FilesManager::GetFileNameFormRoot(const string &sFilename) const
{
	return m_sFolderPath + "\\" + sFilename;
}

// PROTECTED MEMBERS
bool FilesManager::GetAllFilesInDir(const string &sFolderPath, vector<string> &vAllFileName)
{
	DIR *dir = NULL;
	struct dirent *ent = NULL;

	vAllFileName.clear();

	if ((dir = opendir(sFolderPath.c_str())) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
  		{
			if (ent->d_type != DT_DIR)
			{
				string fileName = ent->d_name;
				// Basic checking for onlu .cpp and .c files
				if (fileName.find_last_of(".cpp") != string::npos || fileName.find_last_of(".c") != string::npos)
				{
					vAllFileName.push_back(fileName);
				}
			}
		}
  		closedir(dir);
	}
	else
	{
  		/* could not open directory */
  		LOG_ERROR("Error opening directory.");
  		return false;
	}
	return true;
}

bool FilesManager::Release()
{
	m_mFiles.clear();	// Not required dtor can handle it on its own
	return true;
}

void FilesManager::Display() const
{
	size_t size = GetSize();
	cout << "\nFilPath         := " << m_sFolderPath;
	cout << "\nNumber of Files := " << size;

	size_t i = 1;
	for(const std::pair<string, FileHandler &> &mPair : m_mFiles)
	{
		cout << "\n\nFile " << i << "            :=\n";
		cout << "******************* START ********************\n";

		FileHandler &ref = mPair.second;
		ref.Display();
		//cout << mPair.second// << endl;
	}

	cout << "******************** END *********************" << endl;
}

std::ostream& operator<< (std::ostream &out, const FilesManager &filesManager)
{
	filesManager.Display();
	return out;
}
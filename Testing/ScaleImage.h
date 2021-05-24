#pragma once

#include "TGA_File.h"

namespace TGA
{
class ScaleImage
{
	public:
		bool scaleUsingNearestNeighbour(const std::string& fullPath, int percent);

	protected:
		bool parseFile(const std::string& fullPath);
		bool checkValidExtension(const std::string& fullPath) const;

		std::string getNameToSaveAs(double percent) const;

	private:
		TGAFile						m_tgaFile;
};
}

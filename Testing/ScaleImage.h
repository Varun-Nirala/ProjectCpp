#pragma once

#include "TGA_File.h"

namespace TGA
{
class ScaleImage
{
	public:
		enum class ALGO_TYPE
		{
			NEAREST_NEIGHBOUR,
			BILINEAR,
		};
		bool scale(const std::string& fullPath, ALGO_TYPE type, int percent = 50);
		
	protected:
		bool scaleUsingNearestNeighbour(int percent);
		bool scaleUsingBilinear(int percent);

		Color interpolateBiLinearly(uint8_t tx, uint8_t ty, Color& c00, Color& c10, Color& c01, Color& c11) const;

		bool parseFile(const std::string& fullPath);
		bool checkValidExtension(const std::string& fullPath) const;

		std::string getNameToSaveAs(int percent) const;

	private:
		TGAFile						m_tgaFile;
};
}

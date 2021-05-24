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

		inline Color lerp(const Color& a, const Color& b, uint8_t t) const
		{
			return a + (b - a) * t;
		}

		inline Color blerp(const Color& c00, const Color& c10, const Color& c01, const Color& c11, uint8_t tx, uint8_t ty) const
		{
			return lerp(lerp(c00, c10, tx), lerp(c01, c11, tx), ty);
		}

		bool parseFile(const std::string& fullPath);
		bool checkValidExtension(const std::string& fullPath) const;

		const std::string getNameToSaveAs(int percent) const
		{
			return "Scaled_to_" + std::to_string(percent) + "_" + m_tgaFile.getFileName();
		}

	private:
		TGAFile						m_tgaFile;
};
}

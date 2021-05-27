#include <string>
#include <vector>
#include <array>
#include <utility>
#include "ScaleImage.h"
#include "TGA_File.h"

namespace TGA {
bool ScaleImage::scale(const std::string& fullPath, ALGO_TYPE type, int percent)
{
	if (percent <= 0)
	{
		LOG_ERROR("Scale must be positive.");
		return false;
	}

	if (!parseFile(fullPath))
	{
		LOG_ERROR("Unable to parse file : " + fullPath);
		return false;
	}

	if (type == ALGO_TYPE::NEAREST_NEIGHBOUR)
	{
		if (scaleUsingNearestNeighbour(percent))
		{
			return m_tgaFile.encode("NN_" + getNameToSaveAs(percent));
		}
	}
	else if (type == ALGO_TYPE::BILINEAR)
	{
		if(scaleUsingBilinear(percent))
		{
			return m_tgaFile.encode("BL_" + getNameToSaveAs(percent));
		}
	}

	LOG_ERROR("Unkown scaling type");

	return false;
}

bool ScaleImage::scaleUsingBilinear(int percent)
{
	double rat = percent / 100.0;

	int newHeight = (int)(m_tgaFile.getHeight() * rat);
	int newWidth = (int)(m_tgaFile.getWidth() * rat);

	TGAFile::ColorMat& oldData = m_tgaFile.m_pixelMat;
	TGAFile::ColorMat newData(newHeight, TGAFile::ColorVec(newWidth));

	for (int row = 0, i = 0, j = 0; row < newHeight; ++row)
	{
		for (int col = 0; col < newWidth; ++col)
		{
			const double d_i = std::min(std::max(0.0, row / rat), (double)oldData.size() - 2);
			const double d_j = std::min(std::max(0.0, col / rat), (double)oldData[0].size() - 2);

			i = int(d_i);
			j = int(d_j);

			const Color c00 = oldData[i][j];
			const Color c10 = oldData[i + 1][j];
			const Color c01 = oldData[i][j + 1];
			const Color c11 = oldData[i + 1][j + 1];

			newData[row][col] = blerp(c00, c10, c01, c11, uint8_t(d_j - j), uint8_t(d_i - i));
		}
	}

	m_tgaFile.m_header.m_height = newHeight;
	m_tgaFile.m_header.m_width = newWidth;

	m_tgaFile.m_pixelMat = std::move(newData);

	return true;
}

bool ScaleImage::scaleUsingNearestNeighbour(int percent)
{
	double rat = percent / 100.0;

	int newHeight = (int)(m_tgaFile.getHeight() * rat);
	int newWidth = (int)(m_tgaFile.getWidth() * rat);

	TGAFile::ColorMat& oldData = m_tgaFile.m_pixelMat;
	TGAFile::ColorMat newData(newHeight, TGAFile::ColorVec(newWidth));

	int old_i, old_j;
	for (int i = 0; i < newHeight; ++i)
	{
		for (int j = 0; j < newWidth; ++j)
		{
			old_i = (int)std::min((size_t)std::max(0, int(i / rat)), oldData.size() - 1);
			old_j = (int)std::min((size_t)std::max(0, int(j / rat)), oldData[0].size() - 1);
			newData[i][j] = oldData[old_i][old_j];
		}
	}

	m_tgaFile.m_header.m_height = newHeight;
	m_tgaFile.m_header.m_width = newWidth;

	m_tgaFile.m_pixelMat = std::move(newData);

	return true;
}

bool ScaleImage::parseFile(const std::string& fullPath)
{
	if (!checkValidExtension(fullPath))
	{
		LOG_ERROR("Invalid extension.");
		return false;
	}

	return m_tgaFile.decode(fullPath);
}

bool ScaleImage::checkValidExtension(const std::string& fullPath) const
{
	if (fullPath.size() < 5)
	{
		LOG_ERROR("Invalid Filename");
		return false;
	}

	const std::array<std::string, 4> validExtensions {"tga", "icb", "vda", "vst"};

	std::string ext = fullPath.substr(fullPath.size() - 3);
	
	return validExtensions.end() != std::find(validExtensions.begin(), validExtensions.end(), ext);
}
}
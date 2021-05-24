#include <string>
#include <vector>
#include <algorithm>
#include "helper.h"
#include "ScaleImage.h"

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
		return scaleUsingNearestNeighbour(percent);
	}
	else if (type == ALGO_TYPE::BILINEAR)
	{
		return scaleUsingBilinear(percent);
	}

	LOG_ERROR("Unkown scaling type");

	return false;
}

bool ScaleImage::scaleUsingBilinear(int percent)
{
	return true;
}

bool ScaleImage::scaleUsingNearestNeighbour(int percent)
{
	double rat = percent / 100.0;

	int newHeight = (int)(m_tgaFile.getHeight() * rat);
	int newWidth = (int)(m_tgaFile.getWidth() * rat);

	TGAFile::uint32Mat& oldData = m_tgaFile.m_pixelMat;
	TGAFile::uint32Mat newData(newHeight, TGAFile::uint32Vec(newWidth));

	int old_i, old_j;
	for (int i = 0; i < newHeight; ++i)
	{
		for (int j = 0; j < newWidth; ++j)
		{
			old_i = std::min((unsigned)std::max(0, int(i / rat)), oldData.size() - 1);
			old_j = std::min((unsigned)std::max(0, int(j / rat)), oldData[0].size() - 1);
			newData[i][j] = oldData[old_i][old_j];
		}
	}

	m_tgaFile.m_header.m_height = newHeight;
	m_tgaFile.m_header.m_width = newWidth;

	m_tgaFile.m_pixelMat = std::move(newData);

	return m_tgaFile.encode(getNameToSaveAs(percent));
}

bool ScaleImage::parseFile(const std::string& fullPath)
{
	if (!checkValidExtension(fullPath))
	{
		LOG_ERROR("Invalid extension.");
		return false;
	}

	if (!m_tgaFile.decode(fullPath))
	{
		return false;
	}
	return true;
}

bool ScaleImage::checkValidExtension(const std::string& fullPath) const
{
	if (fullPath.size() < 5)
	{
		LOG_ERROR("Invalid Filename");
		return false;
	}

	const std::vector<std::string> validExtensions{ {"tga"}, {"icb"} ,{"vda"}, {"vst"} };

	std::string ext = fullPath.substr(fullPath.size() - 3);
	
	return validExtensions.end() != std::find(validExtensions.begin(), validExtensions.end(), ext);
}

std::string ScaleImage::getNameToSaveAs(int percent) const
{
	return "Scaled_to_" + std::to_string(percent) + "_" + m_tgaFile.getFileName();
}
}
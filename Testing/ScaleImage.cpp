#include <string>
#include <vector>
#include <algorithm>
#include "helper.h"
#include "ScaleImage.h"

namespace TGA {
bool ScaleImage::scaleUsingNearestNeighbour(const std::string& fullPath, int percent)
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

	/*
	const PixelHelper oldData(m_tgaFile.m_vPixels, m_tgaFile.getHeight(), m_tgaFile.getWidth());

	double rat = percent / 100.0;

	int newHeight = (int)(oldData.getHeight() * rat);
	int newWidth = (int)(oldData.getWidth() * rat);

	std::vector<uint32_t> m_vec;
	m_vec.resize(newHeight * newWidth);

	PixelHelper newData(m_vec, newHeight, newWidth);
	
	for (int i = 0; i < newHeight; ++i)
	{
		for (int j = 0; j < newWidth; ++j)
		{
			newData.setPixelAt(i, j) = oldData.getPixelAt(int(i / rat), int(j / rat));
		}
	}

	m_tgaFile.m_header.m_height = newHeight;
	m_tgaFile.m_header.m_width = newWidth;

	m_tgaFile.m_vPixels = m_vec;

	
	m_tgaFile.encode("Scaled_" + m_tgaFile.getFileName());
	*/
	return true;
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
}
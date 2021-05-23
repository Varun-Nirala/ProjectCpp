#pragma once

#include "TGA_File.h"

namespace TGA
{
class PixelHelper
{
	public:
		PixelHelper() = delete;
		PixelHelper(std::vector<uint32_t>& pixelVec, int height, int width)
			:m_v(pixelVec)
			,m_h(height)
			,m_w(width)
		{}

		uint32_t getPixelAt(int i, int j) const { return m_v[i * m_h + j]; }

		uint32_t& setPixelAt(int i, int j) { return m_v[i * m_h + j]; }
		const uint32_t& setPixelAt(int i, int j) const { return m_v[i * m_h + j]; }

		int getWidth() const { return m_w; }
		int getHeight() const { return m_h; }

	private:
		std::vector<uint32_t>&		m_v;
		int							m_h{};
		int							m_w{};
};

class ScaleImage
{
	public:
		bool scaleUsingNearestNeighbour(const std::string& fullPath, int percent);

	protected:
		bool parseFile(const std::string& fullPath);
		bool checkValidExtension(const std::string& fullPath) const;


	private:
		TGAFile						m_tgaFile;
};
}

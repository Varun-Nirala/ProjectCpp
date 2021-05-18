#include <iostream>
#include <iterator>
#include <algorithm>
#include "TGA_File.h"
#include "helper.h"

namespace TGA {

using std::string;
using std::cout;
using std::endl;
using std::vector;

enum ImageType {
	NO_IMAGE_DATA = 0,

	UNCOMPRESSED_INDEX = 1,		// Not handling
	UNCOMPRESSED_RGB = 2,
	UNCOMPRESSED_GRAY = 3,

	RLE_INDEXED = 9,			// Not handling
	RLE_RGB = 10,
	RLE_GRAY = 11,
};

void read1byte(const char const* srcbuffer, int& index, uint8_t& dst)
{
	memcpy(&dst, &srcbuffer[index++], 1);
}

void read2byte(const char const* srcbuffer, int& index, uint16_t& dst)
{
	memcpy(&dst, &srcbuffer[index], 2);
	index += 2;
}

void TGAHeader::parse(const char const* buffer)
{
	int index = 0;
	read1byte(buffer, index, m_idLength);
	read1byte(buffer, index, m_colorMapType);
	read1byte(buffer, index, m_imageType);

	read2byte(buffer, index, m_colorMapOrigin);
	read2byte(buffer, index, m_colorMapLength);

	read1byte(buffer, index, m_ColorMapbitsPerPixel);

	read2byte(buffer, index, m_xOrigin);
	read2byte(buffer, index, m_yOrigin);

	read2byte(buffer, index, m_width);
	read2byte(buffer, index, m_height);

	read1byte(buffer, index, m_bitsPerPixel);
	read1byte(buffer, index, m_imageDescriptor);
}

bool TGAHeader::isUnCompressed() const
{
	return m_imageType == UNCOMPRESSED_INDEX || m_imageType == UNCOMPRESSED_RGB || m_imageType == UNCOMPRESSED_GRAY;
}

bool TGAHeader::isRLE() const
{
	return m_imageType == RLE_INDEXED || m_imageType == RLE_RGB || m_imageType == RLE_GRAY;
}

bool TGAHeader::isIndexed() const
{
	return m_imageType == UNCOMPRESSED_INDEX || m_imageType == RLE_INDEXED;
}

bool TGAHeader::isRGB() const
{
	return m_imageType == RLE_RGB || m_imageType == UNCOMPRESSED_RGB;
}

bool TGAHeader::isGrayScale() const
{
	return m_imageType == UNCOMPRESSED_GRAY || m_imageType == RLE_GRAY;
}

int TGAHeader::bytesPerPixel() const
{
	return isRGB() ? 4 : 1;
}

bool TGAHeader::leftToRightOrder() const
{
	return (m_imageDescriptor & 0x10);
}

bool TGAHeader::topToBottomOrder() const
{
	return (m_imageDescriptor & 0x20);
}

int TGAHeader::getRowStride() const
{
	return m_width * bytesPerPixel();
}

int TGAHeader::getXoffset() const
{
	return leftToRightOrder() ? 1 : -1;
}

int TGAHeader::getYoffset() const
{
	return topToBottomOrder() ? 1 : -1;
}

int TGAHeader::getImageSize() const
{
	return getRowStride() * m_height
}

void TGAHeader::display() const
{
	std::cout << "ID length         :: " << (int)m_idLength << '\n';
	std::cout << "Color Map Type    :: " << (int)m_colorMapType << '\n';
	std::cout << "Image Type        :: " << (int)m_imageType << '\n';

	std::cout << "Color Map Origin  :: " << (int)m_colorMapOrigin << '\n';
	std::cout << "Color Map Length  :: " << (int)m_colorMapLength << '\n';
	std::cout << "Color Map Depth   :: " << (int)m_ColorMapbitsPerPixel << '\n';

	std::cout << "X Origin          :: " << (int)m_xOrigin << '\n';
	std::cout << "Y Origin          :: " << (int)m_yOrigin << '\n';
	std::cout << "Width in pixel    :: " << (int)m_width << '\n';
	std::cout << "Height in pixel   :: " << (int)m_height << '\n';
	std::cout << "Bits per Pixel    :: " << (int)m_bitsPerPixel << '\n';
	std::cout << "Image Descriptor  :: " << (int)m_imageDescriptor << '\n';
}

TGAFile::TGAFile(const string &sFilepath)
{
	initialize(sFilepath);
}

TGAFile::~TGAFile()
{
}

string TGAFile::getFileName() const
{
	return m_sFileName;
}

string TGAFile::getFilePath() const
{
	return m_sFilePath;
}

// PROTECTED MEMBERS
void TGAFile::initialize(const string &sFilepath)
{
	if(parse(sFilepath))
	{
		m_sFileName = extractFileName(sFilepath);
	}
}

string TGAFile::extractFileName(const string &sFilePath)
{
	string sFileName;
	if(sFilePath.empty())
	{
		LOG_ERROR("Provided filepath is empty.");
		//TODO::Throw exception
	}
	else
	{
		unsigned int matchIndex = sFilePath.rfind('\\') + 1;
		if(matchIndex != string::npos)
		{
			m_sFilePath = sFilePath.substr(0, matchIndex);
			sFileName = sFilePath.substr(matchIndex);
		}
		else
		{
			sFileName = sFilePath;
		}
	}
	return sFileName;
}

bool TGAFile::parse(const string& sFilepath)
{
	char* buffer = nullptr;
	int length = readFileInBuffer(sFilepath, buffer);

	if (length == -1)
	{
		return false;
	}

	readVersion(buffer, length);

	m_header.parse(buffer);

	int index = 18;	// as we have already read the header

	// Read image id
	if (m_header.m_idLength > 0)
	{
		int size = m_header.m_idLength;
		uint8_t val;
		while (size--)
		{
			read1byte(buffer, index, val);
			m_imageID.push_back((char)val);
		}
	}

	// Need to parse color Map
	if (m_header.m_colorMapType == 1)
	{
		// No color map data
		//parseColorMap(buffer, index);
	}
	else
	{
		readPixelData(buffer, index);
	}

	delete[] buffer;
	return true;
}

//void TGAFile::parseColorMap(const char const* buffer, int& index){}

void TGAFile::readPixelData(const char const* buffer, int& index)
{
	switch (m_header.m_imageType)
	{
		case UNCOMPRESSED_INDEX:
			// read as 1 byte
			LOG_ERROR("Error: currently UNCOMPRESSED_INDEX is not handled.");
			break;
		case UNCOMPRESSED_RGB:
			// read as 4 bytes
			readUnCompressedData(buffer, index);
			break;
		case UNCOMPRESSED_GRAY:
			LOG_ERROR("Error: currently UNCOMPRESSED_GRAY is not handled.");
			// read as 1 byte
			break;

		case RLE_INDEXED:
			LOG_ERROR("Error: currently RLE_INDEXED is not handled.");
			// read as 1 byte
			break;
		case RLE_RGB:
			readRleData(buffer, index);
			// read as 4 bytes
			break;
		case RLE_GRAY:
			// read as 1 byte
			LOG_ERROR("Error: currently RLE_GRAY is not handled.");
			break;
		default:
			LOG_ERROR("Error: Image type unkown.");
	}
}

void TGAFile::readUnCompressedData(const char const* buffer, int& index)
{
	m_vPixels.resize(m_header.getImageSize());

	int xOffset = m_header.getXoffset();
	int yOffset = m_header.getYoffset();

	int x = (xOffset == 1 ? 0 : m_header.m_width - 1);
	int y = (yOffset == 1 ? 0 : m_header.m_height - 1);

	for (int i = 0; i < m_header.m_height; ++i)
	{
		for (int j = 0; j < m_header.m_width; ++j)
		{
			uint8_t r, g, b, a;
			m_vPixels.push_back(r);
			m_vPixels.push_back(g);
			m_vPixels.push_back(b);
			m_vPixels.push_back(a);
		}
	}
}

void TGAFile::readRleData(const char const* buffer, int& index)
{
	m_vPixels.resize(m_header.getImageSize());

	int xOffset = m_header.getXoffset();
	int yOffset = m_header.getYoffset();

	int x = (xOffset == 1 ? 0 : m_header.m_width - 1);
	int y = (yOffset == 1 ? 0 : m_header.m_height - 1);
}

int TGAFile::readFileInBuffer(const std::string& sFilepath, char *& buffer) const
{
	std::ifstream file(sFilepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file)
	{
		LOG_ERROR("Error: Opening file :: " + sFilepath + "\n");
		file.close();
		return -1;
	}

	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);

	buffer = new char[length];

	file.read(buffer, length);

	if (!file)
	{
		LOG_ERROR("Error: Only :: " + std::to_string(file.gcount()) + " could be read" + "\n");
	}
	file.close();
}

void TGAFile::readVersion(const char const* buffer, int length)
{
	char singature[17]{};
	memcpy(singature, &buffer[length - 18], 16);
	if (strncmp("TRUEVISION-XFILE", singature, 16) == 0)
	{
		m_version = 2;
	}
}
}
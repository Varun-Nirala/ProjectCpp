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

void TGAHeader::parse(const UChar *buffer)
{
	int index = 0;
	read1byte(buffer, index, m_IDLength);
	read1byte(buffer, index, m_colorMapType);
	read1byte(buffer, index, m_imageType);

	read2byte(buffer, index, m_CMapOrigin);
	read2byte(buffer, index, m_CMapLength);

	read1byte(buffer, index, m_CMapBpp);

	read2byte(buffer, index, m_xOrigin);
	read2byte(buffer, index, m_yOrigin);

	read2byte(buffer, index, m_width);
	read2byte(buffer, index, m_height);

	read1byte(buffer, index, m_Bpp);
	read1byte(buffer, index, m_imageDescriptor);
}

void TGAHeader::display() const
{
	std::cout << "ID length         :: " << (int)m_IDLength << '\n';
	std::cout << "Color Map Type    :: " << (int)m_colorMapType << '\n';
	std::cout << "Image Type        :: " << (int)m_imageType << '\n';

	std::cout << "Color Map Origin  :: " << (int)m_CMapOrigin << '\n';
	std::cout << "Color Map Length  :: " << (int)m_CMapLength << '\n';
	std::cout << "Color Map Depth   :: " << (int)m_CMapBpp << '\n';

	std::cout << "X Origin          :: " << (int)m_xOrigin << '\n';
	std::cout << "Y Origin          :: " << (int)m_yOrigin << '\n';
	std::cout << "Width in pixel    :: " << (int)m_width << '\n';
	std::cout << "Height in pixel   :: " << (int)m_height << '\n';
	std::cout << "Bits per Pixel    :: " << (int)m_Bpp << '\n';
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
	UChar* buffer = nullptr;
	int length = readFileInBuffer(sFilepath, buffer);

	if (length == -1)
	{
		return false;
	}

	readVersion(buffer, length);

	m_header.parse(buffer);

	int index = 18;	// as we have already read the header

	// Read image id
	if (m_header.m_IDLength > 0)
	{
		int size = m_header.m_IDLength;
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
		// Need to parse color map data
		parseColorMap(buffer, index);
	}
	
	readPixelData(buffer, index);

	delete[] buffer;
	return true;
}

void TGAFile::parseColorMap(const UChar *buffer, int& index)
{
	m_pairColorMap.second = m_header.m_CMapLength * m_header.m_CMapBpp / 8;
	m_pairColorMap.first = new UChar[m_pairColorMap.second];

	memcpy(m_pairColorMap.first, &buffer[index], m_pairColorMap.second);

	index += m_pairColorMap.second;
}

void TGAFile::readPixelData(const UChar *buffer, int& index)
{
	int channelSize = m_header.m_Bpp / 8;	// 1, 2, 3 or 4

	channelSize = (channelSize == 2) ? 3 : channelSize;

	if (m_header.m_colorMapType == UNCOMPRESSED_INDEX || m_header.m_colorMapType == RLE_INDEXED)
	{
		channelSize = m_header.m_CMapBpp / 8;
	}

	m_pairPixels.second = m_header.m_width * m_header.m_height * channelSize;

	m_pairPixels.first = new UChar[m_pairPixels.second];

	switch (m_header.m_imageType)
	{
		case UNCOMPRESSED_INDEX:
			if (m_header.m_Bpp == 8)
			{
				read_mapped_8(buffer, index, channelSize);
			}
			else
			{
				LOG_ERROR("Error: Incorrect Data.");
			}
			break;
		case UNCOMPRESSED_RGB:
			switch (m_header.m_Bpp)
			{
				case 16:
					read_RGB_16(buffer, index, channelSize);
					break;
				case 24:
					read_RGB_24(buffer, index, channelSize);
					break;
				case 32:
					read_RGB_32(buffer, index, channelSize);
					break;
				default:
					LOG_ERROR("Error: Incorrect Data.");
					break;
			}

			break;
		case UNCOMPRESSED_GRAY:
			if (m_header.m_Bpp == 8)
			{
				memcpy(m_pairPixels.first, &buffer[index], m_pairPixels.second);
			}
			else
			{
				LOG_ERROR("Error: Incorrect Data.");
			}
			break;

		case RLE_INDEXED:
			if (m_header.m_Bpp == 8)
			{
				read_mapped_rle_8(buffer, index, channelSize);
			}
			else
			{
				LOG_ERROR("Error: Incorrect Data.");
			}
			break;
		case RLE_RGB:
			switch (m_header.m_Bpp)
			{
			case 16:
				read_RGB_rle_16(buffer, index, channelSize);
				break;
			case 24:
				read_RGB_rle_24(buffer, index, channelSize);
				break;
			case 32:
				read_RGB_rle_32(buffer, index, channelSize);
				break;
			default:
				LOG_ERROR("Error: Incorrect Data.");
				break;
			}
			break;
		case RLE_GRAY:
			if (m_header.m_Bpp == 8)
			{
				read_rle_8(buffer, index, channelSize);
			}
			else
			{
				LOG_ERROR("Error: Incorrect Data.");
			}
			break;
		default:
			LOG_ERROR("Error: Image type unkown.");
	}
}

void TGAFile::read_mapped_8(const UChar *buffer, int& index, int channelSize)
{
	for (int i = 0; i < m_pairPixels.second; ++i)
	{
		for (int j = 0; j < channelSize; ++j)
		{
			m_pairPixels.first[i + channelSize - j + 1] = m_pairColorMap.first[buffer[index + i] * channelSize + j];
		}
	}
}

void TGAFile::read_RGB_16(const UChar *buffer, int& index, int channelSize)
{
	int size = m_header.m_width * m_header.m_height;

	int id = 0;
	for (int i = 0; i < size; ++i)
	{
		m_pairPixels.first[id++] = (buffer[index + 1] << 1) & 0xF8;
		m_pairPixels.first[id++] = (buffer[index + 1] << 6) | (buffer[index] >> 2) &  0xF8;
		m_pairPixels.first[id++] = (buffer[index] << 3) & 0xF8;

		index += channelSize;
	}
}

void TGAFile::read_RGB_24(const UChar *buffer, int& index, int channelSize)
{
	int size = m_header.m_width * m_header.m_height;

	int id = 0;
	for (int i = 0; i < size; ++i)
	{
		m_pairPixels.first[id++] = buffer[index + 2];
		m_pairPixels.first[id++] = buffer[index + 1];
		m_pairPixels.first[id++] = buffer[index];

		index += channelSize;
	}
}

void TGAFile::read_RGB_32(const UChar *buffer, int& index, int channelSize)
{
	int size = m_header.m_width * m_header.m_height;

	int id = 0;
	for (int i = 0; i < size; ++i)
	{
		m_pairPixels.first[id++] = buffer[index + 2];
		m_pairPixels.first[id++] = buffer[index + 1];
		m_pairPixels.first[id++] = buffer[index];

		m_pairPixels.first[id++] = buffer[index + 3];

		index += channelSize;
	}
}

void TGAFile::read_mapped_rle_8(const UChar *buffer, int& index, int channelSize)
{
	int max = m_header.m_width * m_header.m_height * channelSize;

	for (int i = 0; i < max; ++i)
	{
		uint8_t runLengthByte = buffer[index + i];

		bool isRaw = ((runLengthByte & 0x80) == 0);	// check 7th bit , 0 means RAW packet, 1 means RLE
		int repitionCount = ((runLengthByte & 0x7f) + 1); // other 7 bit are for => repeat count - 1

		for (int j = 0; j < repitionCount; ++j)
		{
			for (int k = 0; k < channelSize; ++k)
			{
				m_pairPixels.first[i + channelSize - k + 1] = m_pairColorMap.first[buffer[index + i] * channelSize + k];
			}

			if (isRaw)
			{
				index += channelSize;
			}
		}

		if (!isRaw)
		{
			index += channelSize;
		}
	}
}

void TGAFile::read_RGB_rle_16(const UChar *buffer, int& index, int channelSize)
{
	int max = m_header.m_width * m_header.m_height * channelSize;

	int id = 0;
	for (int i = 0; i < max; ++i)
	{
		uint8_t runLengthByte = buffer[index + i];

		bool isRaw = ((runLengthByte & 0x80) == 0);	// check 7th bit , 0 means RAW packet, 1 means RLE
		int repitionCount = ((runLengthByte & 0x7f) + 1); // other 7 bit are for => repeat count - 1

		for (int j = 0; j < repitionCount; ++j)
		{
			m_pairPixels.first[id++] = (buffer[index + 1] << 1) & 0xF8;
			m_pairPixels.first[id++] = (buffer[index + 1] << 6) | (buffer[index] >> 2) & 0xF8;
			m_pairPixels.first[id++] = (buffer[index] << 3) & 0xF8;

			if (isRaw)
			{
				index += channelSize;
			}
		}

		if (!isRaw)
		{
			index += channelSize;
		}
	}
}

void TGAFile::read_RGB_rle_24(const UChar *buffer, int& index, int channelSize)
{
	int max = m_header.m_width * m_header.m_height * channelSize;

	int id = 0;
	for (int i = 0; i < max; ++i)
	{
		uint8_t runLengthByte = buffer[index + i];

		bool isRaw = ((runLengthByte & 0x80) == 0);	// check 7th bit , 0 means RAW packet, 1 means RLE
		int repitionCount = ((runLengthByte & 0x7f) + 1); // other 7 bit are for => repeat count - 1

		for (int j = 0; j < repitionCount; ++j)
		{
			m_pairPixels.first[id++] = buffer[index + 2];
			m_pairPixels.first[id++] = buffer[index + 1];
			m_pairPixels.first[id++] = buffer[index];

			if (isRaw)
			{
				index += channelSize;
			}
		}

		if (!isRaw)
		{
			index += channelSize;
		}
	}
}

void TGAFile::read_RGB_rle_32(const UChar *buffer, int& index, int channelSize)
{
	int max = m_header.m_width * m_header.m_height * channelSize;

	int id = 0;
	for (int i = 0; i < max; ++i)
	{
		uint8_t runLengthByte = buffer[index + i];

		bool isRaw = ((runLengthByte & 0x80) == 0);	// check 7th bit , 0 means RAW packet, 1 means RLE
		int repitionCount = ((runLengthByte & 0x7f) + 1); // other 7 bit are for => repeat count - 1

		for (int j = 0; j < repitionCount; ++j)
		{
			m_pairPixels.first[id++] = buffer[index + 2];
			m_pairPixels.first[id++] = buffer[index + 1];
			m_pairPixels.first[id++] = buffer[index];
			m_pairPixels.first[id++] = buffer[index + 3];

			if (isRaw)
			{
				index += channelSize;
			}
		}

		if (!isRaw)
		{
			index += channelSize;
		}
	}
}

void TGAFile::read_rle_8(const UChar *buffer, int& index, int channelSize)
{
	int max = m_header.m_width * m_header.m_height * channelSize;

	int id = 0;
	for (int i = 0; i < max; ++i)
	{
		uint8_t runLengthByte = buffer[index + i];

		bool isRaw = ((runLengthByte & 0x80) == 0);	// check 7th bit , 0 means RAW packet, 1 means RLE
		int repitionCount = ((runLengthByte & 0x7f) + 1); // other 7 bit are for => repeat count - 1

		for (int j = 0; j < repitionCount; ++j)
		{
			m_pairPixels.first[id++] = buffer[index];

			if (isRaw)
			{
				index += channelSize;
			}
		}

		if (!isRaw)
		{
			index += channelSize;
		}
	}
}

int TGAFile::readFileInBuffer(const std::string& sFilepath, UChar *& buffer) const
{
	std::ifstream file(sFilepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file)
	{
		LOG_ERROR("Error: Opening file :: " + sFilepath + "\n");
		file.close();
		return -1;
	}

	file.seekg(0, file.end);
	int length = (int)file.tellg();
	file.seekg(0, file.beg);

	buffer = new UChar[length];

	file.read((char *)buffer, length);

	if (!file)
	{
		LOG_ERROR("Error: Only :: " + std::to_string(file.gcount()) + " could be read" + "\n");
	}
	file.close();
	return length;
}

void TGAFile::readVersion(const UChar *buffer, int length)
{
	char singature[17]{};
	memcpy(singature, &buffer[length - 18], 16);
	if (strncmp("TRUEVISION-XFILE", singature, 16) == 0)
	{
		m_version = 2;
	}
}
}
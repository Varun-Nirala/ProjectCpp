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
	delete[] m_pairColorMap.first;
	delete[] m_pairPixels.first;
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

	// Check if we need to parse color Map
	if (m_header.m_colorMapType == 1)
	{
		parseColorMap(buffer, index);
	}
	
	readPixelData(buffer, index);

	delete[] buffer;
	return true;
}

void TGAFile::parseColorMap(const UChar* buffer, int& index)
{
	m_pairColorMap.second = m_header.m_CMapLength;

	m_pairColorMap.first = new uint32_t[m_pairColorMap.second];

	if (m_header.m_CMapBpp == 15 || m_header.m_CMapBpp == 16)
	{
		//read as 2 byte
		uint16_t val;
		for (int i = 0; i < m_pairColorMap.second; ++i)
		{
			read2byte(buffer, index, val);
			m_pairColorMap.first[i] = encodeAsRGBA(val);
		}
	}
	else if (m_header.m_CMapBpp == 24)
	{
		uint8_t r, g, b;
		for (int i = 0; i < m_pairColorMap.second; ++i)
		{
			read1byte(buffer, index, b);
			read1byte(buffer, index, g);
			read1byte(buffer, index, r);
			m_pairColorMap.first[i] = encodeAsRGBA(r, g, b);
		}
	}
	else if (m_header.m_CMapBpp == 32)
	{
		uint8_t r, g, b, a;
		for (int i = 0; i < m_pairColorMap.second; ++i)
		{
			read1byte(buffer, index, b);
			read1byte(buffer, index, g);
			read1byte(buffer, index, r);
			read1byte(buffer, index, a);
			m_pairColorMap.first[i] = encodeAsRGBA(r, g, b, a);;
		}
	}

	index += m_pairColorMap.second;
}

void TGAFile::readPixelData(const UChar *buffer, int& index)
{
	m_pairPixels.second = m_header.m_width * m_header.m_height * (m_header.m_Bpp / 8);
	m_pairPixels.first = new uint32_t[m_pairPixels.second];

	uint32_t(TGAFile:: *readAsFuncPtr)(const UChar*, int&);
	switch (m_header.m_imageType)
	{
		case UNCOMPRESSED_INDEX:
			if (m_header.m_Bpp == 8)
			{
				read_mapped_uc_8(buffer, index);
			}
			else
			{
				LOG_ERROR("Error: Incorrect Data.");
			}
			break;
		case UNCOMPRESSED_RGB:
			switch (m_header.m_Bpp)
			{
				case 15:
				case 16:
					readAsFuncPtr = &TGAFile::readColorAs16;
					break;
				case 24:
					readAsFuncPtr = &TGAFile::readColorAs24;
					break;
				case 32:
					readAsFuncPtr = &TGAFile::readColorAs32;
					break;
				default:
					LOG_ERROR("Error: Incorrect Data.");
					return;
			}
			read_RGB_uc(buffer, index, readAsFuncPtr);

			break;
		case UNCOMPRESSED_GRAY:
			if (m_header.m_Bpp == 8)
			{
				read_gray_uc_8(buffer, index);
			}
			else
			{
				LOG_ERROR("Error: Incorrect Data.");
			}
			break;

		case RLE_INDEXED:
			if (m_header.m_Bpp == 8)
			{
				read_mapped_rle_8(buffer, index);
			}
			else
			{
				LOG_ERROR("Error: Incorrect Data.");
			}
			break;
		case RLE_RGB:
			switch (m_header.m_Bpp)
			{
			case 15:
			case 16:
				readAsFuncPtr = &TGAFile::readColorAs16;
				break;
			case 24:
				readAsFuncPtr = &TGAFile::readColorAs24;
				break;
			case 32:
				readAsFuncPtr = &TGAFile::readColorAs32;
				break;
			default:
				LOG_ERROR("Error: Incorrect Data.");
				return;
			}
			read_RGB_rle(buffer, index, readAsFuncPtr);
			break;
		case RLE_GRAY:
			if (m_header.m_Bpp == 8)
			{
				read_gray_rle_8(buffer, index);
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

// UNCOMPRESSED DATA
void TGAFile::read_mapped_uc_8(const UChar* buffer, int& index)
{
	uint8_t val;
	int id = 0;
	for (int i = 0; i < m_header.m_height; ++i)
	{
		for (int j = 0; j < m_header.m_width; ++j)
		{
			read1byte(buffer, index, val);
			m_pairPixels.first[id++] = val;
		}
	}
}

void TGAFile::read_RGB_uc(const UChar* buffer, int& index, uint32_t(TGAFile::* readAsFuncPtr)(const UChar*, int&))
{
	int id = 0;
	for (int i = 0; i < m_header.m_height; ++i)
	{
		for (int j = 0; j < m_header.m_width; ++j)
		{
			m_pairPixels.first[id++] = readAsFuncPtr(buffer,index);
		}
	}
}

void TGAFile::read_gray_uc_8(const UChar* buffer, int& index)
{
	read_mapped_uc_8(buffer, index);
}

// COMPRESSED DATA
void TGAFile::read_mapped_rle_8(const UChar* buffer, int& index)
{
	int id = 0;
	uint8_t rcf;	// repetition count field
	uint8_t val;	// pixel value field
	int runCount;
	for (int i = 0; i < m_header.m_height; ++i)
	{
		for (int j = 0; j < m_header.m_width;)
		{
			read1byte(buffer, index, rcf);

			if (rcf & 0x80)
			{
				// RLE packet
				runCount = (rcf & 0x7F) + 1;
				j += runCount;
				read1byte(buffer, index, val);
				while (runCount--)
				{
					m_pairPixels.first[id++] = val;
				}
			}
			else
			{
				// Raw packet
				runCount = rcf + 1;
				j += runCount;
				while (runCount--)
				{
					read1byte(buffer, index, val);
					m_pairPixels.first[id++] = val;
				}
			}
		}
	}
}

void TGAFile::read_RGB_rle(const UChar* buffer, int& index, uint32_t(TGAFile::* readAsFuncPtr)(const UChar*, int&))
{
	int id = 0;
	uint8_t rcf;	// repetition count field
	uint32_t val;	// pixel value field
	int runCount;
	for (int i = 0; i < m_header.m_height; ++i)
	{
		for (int j = 0; j < m_header.m_width;)
		{
			read1byte(buffer, index, rcf);

			if (rcf & 0x80)
			{
				// RLE packet
				runCount = (rcf & 0x7F) + 1;
				j += runCount;
				val = readAsFuncPtr(buffer, index);
				while (runCount--)
				{
					m_pairPixels.first[id++] = val;
				}
			}
			else
			{
				// Raw packet
				runCount = rcf + 1;
				j += runCount;
				while (runCount--)
				{
					val = readAsFuncPtr(buffer, index);
					m_pairPixels.first[id++] = val;
				}
			}
		}
	}
}

void TGAFile::read_gray_rle_8(const UChar* buffer, int& index)
{
	read_mapped_rle_8(buffer, index);
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
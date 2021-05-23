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

const char TRUEVISION_SIGNATURE[] = "TRUEVISION-XFILE.\0";

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

void TGAHeader::writeToFile(std::ofstream& file) const
{
	file.put(m_IDLength);
	file.put(m_colorMapType);
	file.put(m_imageType);

	file.write((char *)&m_CMapOrigin, 2);
	file.write((char *)&m_CMapLength, 2);
	file.put(m_CMapBpp);

	file.write((char*)&m_xOrigin, 2);
	file.write((char*)&m_yOrigin, 2);
	file.write((char*)&m_width, 2);
	file.write((char*)&m_height, 2);
	file.put(m_Bpp);
	file.put(m_imageDescriptor);
}

void TGAHeader::display() const
{
	std::cout << "**************************** HEADER ****************************\n";
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
	std::cout << "Image Descriptor  :: " << (int)m_imageDescriptor << "\n\n";
}

int TGAFooter::parse(const UChar* buffer, int length)
{
	int version = 1;
	memcpy(m_signature, &buffer[length - 18], 18);
	if (strncmp(TRUEVISION_SIGNATURE, m_signature, 18) == 0)
	{
		version = 2;
		int index = length - 26;
		read4byte(buffer, index, m_extensionOffset);
		read4byte(buffer, index, m_developerOffset);
	}
	return version;
}

void TGAFooter::display() const
{
	std::cout << "**************************** FOOTER ****************************\n";
	if (strncmp(TRUEVISION_SIGNATURE, (char*)m_signature, 16) == 0)
	{
		std::cout << "Version                  :: 2\n";
		std::cout << "Extension area offset    :: " << (int)m_extensionOffset << '\n';
		std::cout << "Developer area offset    :: " << (int)m_developerOffset << "\n\n";
	}
	else
	{
		std::cout << "Version 1. No Footer data\n\n";
	}
}

TGAFile::TGAFile(const string& sFilepath)
	:m_sFullPath(sFilepath)
{}

TGAFile::~TGAFile()
{
	delete[] m_vFooterAndExtra.first;
}

bool TGAFile::decode()
{
	UChar* buffer = nullptr;
	int length = readFileInBuffer(m_sFullPath, buffer);

	if (length == -1)
	{
		LOG_ERROR("Parsing file failed.");
		return false;
	}

	m_header.parse(buffer);
	m_version = m_footer.parse(buffer, length);

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

	if (m_version == 2)
	{
		readVersion2Specific(buffer, length, index);
	}

	return true;
}

bool TGAFile::encode(const std::string& newFileName)
{
	std::ofstream file(getFilePath() + newFileName, std::ios::out | std::ios::binary);

	if (!file)
	{
		LOG_ERROR("Opening file :: " + getFilePath() + newFileName + "\n");
		file.close();
		return false;
	}

	m_header.writeToFile(file);

	for (int i = 0; i < m_header.m_IDLength; ++i)
	{
		file.put((char)m_imageID[i]);
	}

	writeColorMap(file);
	writeImageData(file);

	if (m_version == 2)
	{
		file.write((char*)&m_vFooterAndExtra.first, m_vFooterAndExtra.second);
	}

	file.close();
	return true;
}

string TGAFile::getFileName() const
{
	string sFileName;
	if(m_sFullPath.empty())
	{
		LOG_ERROR("Provided filepath is empty.");
		//TODO::Throw exception
	}
	else
	{
		unsigned int matchIndex = m_sFullPath.rfind('\\') + 1;
		if(matchIndex != string::npos)
		{
			sFileName = m_sFullPath.substr(matchIndex);
		}
	}
	return sFileName;
}

string TGAFile::getFilePath() const
{
	string sFilePath;
	if (m_sFullPath.empty())
	{
		LOG_ERROR("Provided filepath is empty.");
	}
	else
	{
		unsigned int matchIndex = m_sFullPath.rfind('\\') + 1;
		if (matchIndex != string::npos)
		{
			sFilePath = m_sFullPath.substr(0, matchIndex);
		}
	}
	return sFilePath;
}

bool TGAFile::parse()
{
	
}

void TGAFile::parseColorMap(const UChar* buffer, int& index)
{
	m_vColorMap.resize(m_header.m_CMapLength);
	if (m_header.m_CMapBpp == 15 || m_header.m_CMapBpp == 16)
	{
		//read as 2 byte
		uint16_t val;
		for (int i = 0; i < m_header.m_CMapLength; ++i)
		{
			read2byte(buffer, index, val);
			m_vColorMap[i] = encodeAsRGBA(val);
		}
	}
	else if (m_header.m_CMapBpp == 24)
	{
		for (int i = 0; i < m_header.m_CMapLength; ++i)
		{
			m_vColorMap[i] = readColorAs24(buffer, index);
		}
	}
	else if (m_header.m_CMapBpp == 32)
	{
		for (int i = 0; i < m_header.m_CMapLength; ++i)
		{
			m_vColorMap[i] = readColorAs32(buffer, index);
		}
	}

	index += m_header.m_CMapLength;
}

void TGAFile::readPixelData(const UChar *buffer, int& index)
{
	m_vPixels.resize(m_header.m_width * m_header.m_height * (m_header.m_Bpp / 8));

	switch (m_header.m_imageType)
	{
		case UNCOMPRESSED_INDEX:
		case UNCOMPRESSED_GRAY:
			if (m_header.m_Bpp == 8)
			{
				read_RGB_uc(buffer, index, &TGAFile::readColorAs8);
			}
			else
			{
				LOG_ERROR("Incorrect Data.");
			}
			break;

		case UNCOMPRESSED_RGB:
			switch (m_header.m_Bpp)
			{
				case 15:
				case 16:
					read_RGB_uc(buffer, index, &TGAFile::readColorAs16);
					break;
				case 24:
					read_RGB_uc(buffer, index, &TGAFile::readColorAs24);
					break;
				case 32:
					read_RGB_uc(buffer, index, &TGAFile::readColorAs32);
					break;
				default:
					LOG_ERROR("Incorrect Data.");
					return;
			}
			break;

		case RLE_INDEXED:
		case RLE_GRAY:
			if (m_header.m_Bpp == 8)
			{
				read_RGB_rle(buffer, index, &TGAFile::readColorAs8);
			}
			else
			{
				LOG_ERROR("Incorrect Data.");
			}
			break;

		case RLE_RGB:
			switch (m_header.m_Bpp)
			{
			case 15:
			case 16:
				read_RGB_rle(buffer, index, &TGAFile::readColorAs16);
				break;
			case 24:
				read_RGB_rle(buffer, index, &TGAFile::readColorAs24);
				break;
			case 32:
				read_RGB_rle(buffer, index, &TGAFile::readColorAs32);
				break;
			default:
				LOG_ERROR("Incorrect Data.");
				return;
			}
			break;

		default:
			LOG_ERROR("Image type unkown.");
	}
}

// UNCOMPRESSED DATA
void TGAFile::read_RGB_uc(const UChar* buffer, int& index, uint32_t(TGAFile::* readAsFuncPtr)(const UChar*, int&) const)
{
	int id = 0;
	for (int i = 0; i < m_header.m_height; ++i)
	{
		for (int j = 0; j < m_header.m_width; ++j)
		{
			m_vPixels[id++] = (this->*readAsFuncPtr)(buffer,index);
		}
	}
}

// COMPRESSED DATA
void TGAFile::read_RGB_rle(const UChar* buffer, int& index, uint32_t(TGAFile::* readAsFuncPtr)(const UChar*, int&) const)
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
				val = (this->*readAsFuncPtr)(buffer, index);
				while (runCount--)
				{
					m_vPixels[id++] = val;
				}
			}
			else
			{
				// Raw packet
				runCount = rcf + 1;
				j += runCount;
				while (runCount--)
				{
					val = (this->*readAsFuncPtr)(buffer, index);
					m_vPixels[id++] = val;
				}
			}
		}
	}
}

void TGAFile::readVersion2Specific(const UChar* buffer, int length, int& index)
{
	// Extract extra data after the image the data.
	m_vFooterAndExtra.second = length - index;
	m_vFooterAndExtra.first = new uint8_t[m_vFooterAndExtra.second]{};

	memcpy(m_vFooterAndExtra.first, &buffer[index], m_vFooterAndExtra.second);
}

int TGAFile::readFileInBuffer(const std::string& sFilepath, UChar *& buffer) const
{
	std::ifstream file(sFilepath, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file)
	{
		LOG_ERROR("Opening file :: " + sFilepath + "\n");
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
		LOG_ERROR("Only :: " + std::to_string(file.gcount()) + " could be read" + "\n");
	}
	file.close();
	return length;
}

void TGAFile::writeColorMap(std::ostream &file) const
{
	if (m_header.m_imageType == 1)
	{
		switch (m_header.m_CMapBpp)
		{
			case 15:
			case 16:
				for (size_t i = 0; i < m_vColorMap.size(); ++i)
				{
					writeColorAs16(file, m_vColorMap[i]);
				}
				break;
			case 24:
				for (size_t i = 0; i < m_vColorMap.size(); ++i)
				{
					writeColorAs24(file, m_vColorMap[i]);
				}
				break;
			case 32:
				for (size_t i = 0; i < m_vColorMap.size(); ++i)
				{
					writeColorAs32(file, m_vColorMap[i]);
				}
				break;
			default:

				break;
		}
	}
}

void TGAFile::writeImageData(std::ostream& file)
{
	int index = 0;
	switch (m_header.m_imageType)
	{
		case UNCOMPRESSED_INDEX:
		case UNCOMPRESSED_GRAY:
			for (size_t i = 0; i < m_vPixels.size(); ++i)
			{
				writeColorAs8(file, m_vPixels[i]);
			}
		break;

		case UNCOMPRESSED_RGB:
			switch (m_header.m_Bpp)
			{
				case 15:
				case 16:
					for (size_t i = 0; i < m_vPixels.size(); ++i)
					{
						writeColorAs16(file, m_vPixels[i]);
					}
					break;

				case 24:
					for (size_t i = 0; i < m_vPixels.size(); ++i)
					{
						writeColorAs24(file, m_vPixels[i]);
					}
					break;

				case 32:
					for (size_t i = 0; i < m_vPixels.size(); ++i)
					{
						writeColorAs32(file, m_vPixels[i]);
					}
					break;
			}
		break;

		case RLE_INDEXED:
		case RLE_GRAY:
			for (int i = 0; i < m_header.m_height; ++i)
			{
				writeRleLine(&TGAFile::writeColorAs8, file, index);
			}
			break;

		case RLE_RGB:
			switch (m_header.m_Bpp)
			{
				case 15:
				case 16:
					for (int i = 0; i < m_header.m_height; ++i)
					{
						writeRleLine(&TGAFile::writeColorAs16, file, index);
					}
					break;

				case 24:
					for (int i = 0; i < m_header.m_height; ++i)
					{
						writeRleLine(&TGAFile::writeColorAs24, file, index);
					}
					break;

				case 32:
					for (int i = 0; i < m_header.m_height; ++i)
					{
						writeRleLine(&TGAFile::writeColorAs32, file, index);
					}
					break;
			}
			break;

		default:
			LOG_ERROR("Image type unkown.");
	}
}

void TGAFile::writeRleLine(void(TGAFile::* writeAsFuncPtr)(std::ostream&, uint32_t) const, std::ostream& file, int &index)
{
	int id = 0;
	while (id < m_header.m_width)
	{
		int count = countRepeatPixel(index, id);

		if (count > 0)	// as RLE
		{
			uint8_t rcf = 0x80 | (uint8_t(count - 1));
			file.put(rcf);

			(this->*writeAsFuncPtr)(file, m_vPixels[index]);

			index += count;
		}
		else
		{	// as Raw
			count = countDifferentPixel(index, id);

			uint8_t rcf((uint8_t)count - 1);
			file.put(rcf);

			while (count--)
			{
				(this->*writeAsFuncPtr)(file, m_vPixels[index++]);
			}

			index += count;
		}
	}
}

int TGAFile::countRepeatPixel(int startIndex, int &id)  const
{
	static const int maxLengthToEncode = 128;
	
	int count = 0;
	uint32_t val = m_vPixels[startIndex++];

	for (id; id < m_header.m_width && count < maxLengthToEncode; ++id)
	{
		if (m_vPixels[startIndex] == val)
		{
			startIndex++;
			count++;
		}
	}

	return count;
}

int TGAFile::countDifferentPixel(int startIndex, int& id) const
{
	static const int maxLengthToEncode = 128;

	int count = 0;
	uint32_t val = m_vPixels[startIndex++];

	for (id; id < m_header.m_width && count < maxLengthToEncode; ++id)
	{
		if (m_vPixels[startIndex] != val)
		{
			startIndex++;
			count++;
		}
	}

	return count;
}
}

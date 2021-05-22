#ifndef __TGA_FILE_H__
#define __TGA_FILE_H__

#include <fstream>
#include <cstdio>
#include <vector>

namespace TGA
{
	using UChar = unsigned char;

	enum ImageType {
		NO_IMAGE_DATA = 0,

		UNCOMPRESSED_INDEX = 1,
		UNCOMPRESSED_RGB = 2,
		UNCOMPRESSED_GRAY = 3,

		RLE_INDEXED = 9,
		RLE_RGB = 10,
		RLE_GRAY = 11,
	};

	enum ReadType {
		AS_16_BIT,
		AS_24_BIT,
		AS_32_BIT,
	};

	inline void read1byte(const UChar* srcbuffer, int& index, uint8_t& dst)
	{
		memcpy(&dst, &srcbuffer[index++], 1);
	}

	inline void read2byte(const UChar* srcbuffer, int& index, uint16_t& dst)
	{
		memcpy(&dst, &srcbuffer[index], 2);
		index += 2;
	}

	struct TGAHeader
	{
		uint8_t		m_IDLength;						// Length of image ID field
		uint8_t		m_colorMapType;					// Whether a color map is included, 0 = No color map, 1 = Color map present
		uint8_t		m_imageType;					// Compression and color type

		// Color Map specification 5 bytes, Describes the color map
		uint16_t	m_CMapOrigin;					// index of first color map entry that is included in the file
		uint16_t	m_CMapLength;					// number of entries of the color map that are included in the file
		uint8_t		m_CMapBpp;						// number of bits per pixel in colorMap, typically 15, 16, 24 or 32 bit per value

		// Image specification 10 bytes, Describes the image dimensions and format
		uint16_t	m_xOrigin;						// absolute horizontal coordinate
		uint16_t	m_yOrigin;						// absolute vertical coordinate
		uint16_t	m_width;						// width in pixels
		uint16_t	m_height;						// height in pixels
		uint8_t		m_Bpp;							// bits per pixel [8, 16, 24, 32]
		uint8_t		m_imageDescriptor;				// bits 0-3 give the alpha channel depth, bits 5-4 give direction

		void display() const;
		void parse(const UChar * const buffer);
	};

	class TGAFile
	{
	public:
		TGAFile(const std::string& sFilepath);
		~TGAFile();

		std::string getFileName() const { return m_sFileName; }

		std::string getFilePath() const { return m_sFilePath; }

		void displayHeader() { m_header.display(); }

	protected:
		void initialize(const std::string& sFilepath);
		std::string extractFileName(const std::string& sFilePath);

		bool parse(const std::string& sFilepath);

		void parseColorMap(const UChar* buffer, int& index);

		void readPixelData(const UChar* buffer, int& index);

		// UNCOMPRESSED DATA
		void read_mapped_uc_8(const UChar* buffer, int& index);

		void read_RGB_uc(const UChar* buffer, int& index, uint32_t(TGAFile::*readAsFuncPtr)(const UChar*, int&));

		void read_gray_uc_8(const UChar* buffer, int& index);

		// COMPRESSED DATA
		void read_mapped_rle_8(const UChar* buffer, int& index);

		void read_RGB_rle(const UChar* buffer, int& index, uint32_t(TGAFile::*readAsFuncPtr)(const UChar*, int&));

		void read_gray_rle_8(const UChar* buffer, int& index);


		int readFileInBuffer(const std::string& sFilepath, UChar*& buffer) const;
		void readVersion(const UChar* buffer, int length);

		uint32_t readColorAs16(const UChar* buffer, int& index)
		{
			uint8_t a = 255;
			uint16_t val;
			read2byte(buffer, index, val);
			if (!(val & 0x8000))
				a = 0;
			return encodeAsRGBA(val, a);
		}

		inline uint32_t readColorAs24(const UChar* buffer, int& index)
		{
			uint8_t r, g, b;
			read1byte(buffer, index, b);
			read1byte(buffer, index, g);
			read1byte(buffer, index, r);
			return encodeAsRGBA(r, g, b);
		}

		uint32_t readColorAs32(const UChar* buffer, int& index)
		{
			uint8_t r, g, b, a;
			read1byte(buffer, index, b);
			read1byte(buffer, index, g);
			read1byte(buffer, index, r);
			read1byte(buffer, index, a);
			return encodeAsRGBA(r, g, b, a);
		}

		inline uint32_t encodeAsRGBA(uint16_t pixel, uint8_t a = 255)
		{
			uint8_t r = (pixel >> 10) & 0x1F;
			uint8_t g = (pixel >> 5) & 0x1F;
			uint8_t b = pixel & 0x1F;
			return encodeAsRGBA(r, g, b, a);
		}

		inline uint32_t encodeAsRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
		{
			return (r | (g << 8) || (b << 16) || (a << 24));
		}

	private:
		std::string 					m_sFileName;
		std::string 					m_sFilePath;

		int								m_version{ 1 };
		std::string						m_imageID;
		TGAHeader						m_header;
		std::pair<uint32_t*, int>		m_pairPixels{};
		std::pair<uint32_t*, int>		m_pairColorMap{};
	};
}
#endif		//#define __FILEHANDLER_H__
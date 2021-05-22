#ifndef __TGA_FILE_H__
#define __TGA_FILE_H__

#include <fstream>
#include <cstdio>
#include <vector>

namespace TGA
{
	using UChar = unsigned char;

	void read1byte(const UChar *srcbuffer, int& index, uint8_t& dst);
	void read2byte(const UChar *srcbuffer, int& index, uint16_t& dst);

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

		std::string getFileName() const;
		std::string getFilePath() const;

		void displayHeader() { m_header.display(); }

	protected:
		void initialize(const std::string& sFilepath);
		std::string extractFileName(const std::string& sFilePath);

		bool parse(const std::string& sFilepath);

		void parseColorMap(const UChar *buffer, int& index);

		void readPixelData(const UChar *buffer, int& index);

		int readFileInBuffer(const std::string& sFilepath, UChar*& buffer) const;
		void readVersion(const UChar *buffer, int length);


		void read_mapped_8(const UChar *buffer, int& index, int channelSize);
		void read_RGB_16(const UChar *buffer, int& index, int channelSize);
		void read_RGB_24(const UChar *buffer, int& index, int channelSize);
		void read_RGB_32(const UChar *buffer, int& index, int channelSize);

		void read_mapped_rle_8(const UChar *buffer, int& index, int channelSize);
		void read_RGB_rle_16(const UChar *buffer, int& index, int channelSize);
		void read_RGB_rle_24(const UChar *buffer, int& index, int channelSize);
		void read_RGB_rle_32(const UChar *buffer, int& index, int channelSize);

		void read_rle_8(const UChar *buffer, int& index, int channelSize);

	private:
		std::string 					m_sFileName;
		std::string 					m_sFilePath;

		int								m_version{ 1 };
		std::string						m_imageID;
		TGAHeader						m_header;
		std::pair<uint8_t*, int>		m_pairPixels{};
		std::pair<uint8_t*, int>		m_pairColorMap{};
	};
}
#endif		//#define __FILEHANDLER_H__
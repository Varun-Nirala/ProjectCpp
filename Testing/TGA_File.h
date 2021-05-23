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

	inline void read1byte(const UChar* srcbuffer, int& index, uint8_t& dst)
	{
		memcpy(&dst, &srcbuffer[index++], 1);
	}

	inline void read2byte(const UChar* srcbuffer, int& index, uint16_t& dst)
	{
		memcpy(&dst, &srcbuffer[index], 2);
		index += 2;
	}

	inline void read4byte(const UChar* srcbuffer, int& index, uint32_t& dst)
	{
		memcpy(&dst, &srcbuffer[index], 4);
		index += 4;
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

		void writeToFile(std::ofstream& file) const;
	};

	struct TGAFooter
	{
		uint32_t	m_extensionOffset{};
		uint32_t	m_developerOffset{};
		char		m_signature[18]{};

		void display() const;
		// return version of the file format
		int parse(const UChar* const buffer, int length);
	};

	class TGAFile
	{
	public:
		TGAFile() = delete;
		TGAFile(const std::string& sFilepath);
		~TGAFile();

		void decode();
		void encode(std::string& newFileName);

		std::string getFileName() const;
		std::string getFilePath() const;

		void displayHeader() const { m_header.display(); }
		void displayFooter() const { m_footer.display(); }

	// Related to decoding file
	protected:
		bool parse();

		void parseColorMap(const UChar* buffer, int& index);
		void readPixelData(const UChar* buffer, int& index);

		// UNCOMPRESSED DATA
		void read_RGB_uc(const UChar* buffer, int& index, uint32_t(TGAFile::*readAsFuncPtr)(const UChar*, int&) const);

		// COMPRESSED DATA
		void read_RGB_rle(const UChar* buffer, int& index, uint32_t(TGAFile::*readAsFuncPtr)(const UChar*, int&) const);

		void readVersion2Specific(const UChar* buffer, int length, int& index);

		int readFileInBuffer(const std::string& sFilepath, UChar*& buffer) const;

		inline uint32_t readColorAs8(const UChar* buffer, int& index) const
		{
			uint8_t val;
			read1byte(buffer, index, val);
			return val;
		}

		inline uint32_t readColorAs16(const UChar* buffer, int& index) const
		{
			uint8_t a = 255;
			uint16_t val;
			read2byte(buffer, index, val);

			if (!(val & 0x8000))
				a = 0;
			return encodeAsRGBA(val, a);
		}

		inline uint32_t readColorAs24(const UChar* buffer, int& index) const
		{
			uint8_t r, g, b;
			read1byte(buffer, index, b);
			read1byte(buffer, index, g);
			read1byte(buffer, index, r);
			return encodeAsRGBA(r, g, b);
		}

		inline uint32_t readColorAs32(const UChar* buffer, int& index) const
		{
			uint8_t r, g, b, a;
			read1byte(buffer, index, b);
			read1byte(buffer, index, g);
			read1byte(buffer, index, r);
			read1byte(buffer, index, a);
			return encodeAsRGBA(r, g, b, a);
		}

		inline uint32_t encodeAsRGBA(uint16_t pixel, uint8_t a = 255) const
		{
			uint8_t r = (pixel >> 10) & 0x1F;
			uint8_t g = (pixel >> 5) & 0x1F;
			uint8_t b = pixel & 0x1F;
			return encodeAsRGBA((r << 3 | r >> 2),
								(g << 3 | g >> 2),
								(b << 3 | b >> 2),
								(a << 3 | a >> 2));
		}

		inline uint32_t encodeAsRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) const
		{
			return (r | (g << 8) || (b << 16) || (a << 24));
		}
	
	// Related to encoding file
	protected:
		void writeColorMap(std::ostream& file) const;
		void writeImageData(std::ostream& file);

		void writeRleLine(void(TGAFile::* writeAsFuncPtr)(std::ostream&, uint32_t) const, std::ostream& file, int &index);

		int countRepeatPixel(int startIndex, int &id) const;
		int countDifferentPixel(int startIndex, int& id) const;

		inline void writeColorAs8(std::ostream& file, uint32_t val) const
		{
			file.put((uint8_t)val);
		}

		inline void writeColorAs16(std::ostream &file, uint32_t val) const
		{
			uint8_t r, g, b, a;
			decodeAsRGBA(val, r, g, b, a);
			
			uint16_t v = 
				((r >> 3) << 10) |
				((g >> 3) << 5) |
				((b >> 3)) |
				(a != 0 ? 0x8000 : 0);

			file.write((char *)&v, 2);
		}

		inline void writeColorAs24(std::ostream& file, uint32_t val) const
		{
			uint8_t r, g, b, a;
			decodeAsRGBA(val, r, g, b, a);
			file.put(b);
			file.put(g);
			file.put(r);
		}

		inline void writeColorAs32(std::ostream& file, uint32_t val) const
		{
			uint8_t r, g, b, a;
			decodeAsRGBA(val, r, g, b, a);
			file.put(b);
			file.put(g);
			file.put(r);
			file.put(a);
		}

		void decodeAsRGBA(uint32_t val, uint8_t& r, uint8_t& g, uint8_t& b, uint8_t& a) const
		{
			r = val & 0xFF;
			g = (val >> 8) & 0xFF;
			b = (val >> 16) & 0xFF;
			a = (val >> 24) & 0xFF;
		}

	private:
		std::string 					m_sFullPath;

		int								m_version{ 1 };
		std::string						m_imageID;
		
		TGAHeader						m_header{};
		TGAFooter						m_footer{};

		std::vector<uint32_t>			m_vPixels;
		std::vector<uint32_t>			m_vColorMap;

		std::pair<uint8_t*, int>		m_vFooterAndExtra{};
	};
}
#endif		//#define __FILEHANDLER_H__
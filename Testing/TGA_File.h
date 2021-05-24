#ifndef __TGA_FILE_H__
#define __TGA_FILE_H__

#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

#define LOG_ERROR(msg)  std::cout << "ERROR :: " << __FUNCTION__ << "::" << __LINE__ << ":: " << msg << std::endl

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

		void clear();

		void display() const;
		void parse(const UChar * const buffer);

		void writeToFile(std::ofstream& file) const;
	};

	struct TGAFooter
	{
		uint32_t	m_extensionOffset{};
		uint32_t	m_developerOffset{};
		char		m_signature[18]{};

		void clear();

		void display() const;
		// return version of the file format
		int parse(const UChar* const buffer, int length);
	};

	struct Color
	{
		uint8_t r{};	// also act as index in color of 8bit encoding
		uint8_t g{};
		uint8_t b{};
		uint8_t a{};

		explicit Color(uint8_t rr = 0, uint8_t gg = 0, uint8_t bb = 0, uint8_t aa = 255)
			:r(rr)
			, g(gg)
			, b(bb)
			, a(aa)
		{}

		inline bool operator==(const Color& c) const
		{
			return r == c.r && g == c.g && b == c.b && a == c.a;
		}

		inline bool operator!=(const Color& c) const
		{
			return !(*this == c);
		}

		inline Color operator*(uint8_t val) const
		{
			return Color{uint8_t(r*val), uint8_t(g*val), uint8_t(b*val), uint8_t(a*val)};
		}

		inline Color operator*(const Color& val) const
		{
			return Color{ uint8_t(r * val.r), uint8_t(g * val.g), uint8_t(b * val.b), uint8_t(a * val.a) };
		}

		inline Color operator+(uint8_t val) const
		{
			return Color{ uint8_t(r + val), uint8_t(g + val), uint8_t(b + val), uint8_t(a + val) };
		}

		inline Color operator+(const Color& val) const
		{
			return Color{ uint8_t(r + val.r), uint8_t(g + val.g), uint8_t(b + val.b), uint8_t(a + val.a) };
		}

		inline Color operator-(uint8_t val) const
		{
			return Color{ uint8_t(r - val), uint8_t(g - val), uint8_t(b - val), uint8_t(a - val) };
		}

		inline Color operator-(const Color& val) const
		{
			return Color{ uint8_t(r - val.r), uint8_t(g - val.g), uint8_t(b - val.b), uint8_t(a - val.a) };
		}
	};

	//
	class ScaleImage;
	class TGAFile
	{
		friend class ScaleImage;

	public:
		TGAFile() {};
		~TGAFile();

		bool decode(const std::string& sFilepath);
		bool encode(const std::string& newFileName);

		std::string getFileName() const;
		std::string getFilePath() const;

		inline int getWidth() const { return m_header.m_width; }
		inline int getHeight() const { return m_header.m_height; }

		inline void displayHeader() const { m_header.display(); }
		inline void displayFooter() const { m_footer.display(); }

	// Related to decoding file
	protected:
		void clear();

		void parseColorMap(const UChar* buffer, int& index);
		void readPixelData(const UChar* buffer, int& index);

		// UNCOMPRESSED DATA
		void read_RGB_uc(const UChar* buffer, int& index, Color(TGAFile::*readAsFuncPtr)(const UChar*, int&) const);

		// COMPRESSED DATA
		void read_RGB_rle(const UChar* buffer, int& index, Color(TGAFile::*readAsFuncPtr)(const UChar*, int&) const);

		void readVersion2Specific(const UChar* buffer, int length, int& index);

		int readFileInBuffer(const std::string& sFilepath, UChar*& buffer) const;

		inline Color readColorAs8(const UChar* buffer, int& index) const
		{
			Color c;
			read1byte(buffer, index, c.r);
			return c;
		}

		inline Color readColorAs16(const UChar* buffer, int& index) const
		{
			Color c;
			c.a = 255;
			uint16_t val;
			read2byte(buffer, index, val);

			if (!(val & 0x8000))
				c.a = 0;

			c.r = (val >> 10) & 0x1F;
			c.g = (val >> 5) & 0x1F;
			c.b = val & 0x1F;

			c.r = (c.r << 3 | c.r >> 2);
			c.g = (c.g << 3 | c.g >> 2);
			c.b = (c.b << 3 | c.b >> 2);
			c.a = (c.a << 3 | c.a >> 2);

			return c;
		}

		inline Color readColorAs24(const UChar* buffer, int& index) const
		{
			Color c;
			read1byte(buffer, index, c.b);
			read1byte(buffer, index, c.g);
			read1byte(buffer, index, c.r);
			return c;
		}

		inline Color readColorAs32(const UChar* buffer, int& index) const
		{
			Color c;
			read1byte(buffer, index, c.b);
			read1byte(buffer, index, c.g);
			read1byte(buffer, index, c.r);
			read1byte(buffer, index, c.a);
			return c;
		}
	
	// Related to encoding file
	protected:
		void writeColorMap(std::ostream& file) const;
		void writeImageData(std::ostream& file) const;

		void writeRleLine(void(TGAFile::* writeAsFuncPtr)(std::ostream&, Color) const, std::ostream& file, int row) const;

		int countRepeatPixel(int row, int col) const;
		int countDifferentPixel(int row, int col) const;

		inline bool isLastInRow(int row) const { return (row == m_pixelMat.size() - 1); }
		inline bool isLastInCol(int col) const { return (m_pixelMat.size() && col == m_pixelMat[0].size() - 1); }

		inline bool isLastInMat(int row, int col) const 
		{ 
			return isLastInRow(row) && isLastInCol(col);
		}

		inline void writeColorAs8(std::ostream& file, Color c) const
		{
			file.put(c.r);
		}

		inline void writeColorAs16(std::ostream &file, Color c) const
		{
			uint16_t v = 
				((c.r >> 3) << 10) |
				((c.g >> 3) << 5) |
				((c.b >> 3)) |
				(c.a != 0 ? 0x8000 : 0);

			file.write((char *)&v, 2);
		}

		inline void writeColorAs24(std::ostream& file, Color c) const
		{
			file.put(c.b);
			file.put(c.g);
			file.put(c.r);
		}

		inline void writeColorAs32(std::ostream& file, Color c) const
		{
			file.put(c.b);
			file.put(c.g);
			file.put(c.r);
			file.put(c.a);
		}

		using ColorVec = std::vector<Color>;
		using ColorMat = std::vector<std::vector<Color>>;
	private:
		std::string 					m_sFullPath;

		int								m_version{ 1 };
		std::string						m_imageID;
		
		TGAHeader						m_header{};
		TGAFooter						m_footer{};

		ColorVec						m_vColorMap;
		ColorMat						m_pixelMat;

		std::pair<uint8_t*, int>		m_vFooterAndExtra{};
	};
}
#endif		//#define __TGA_FILE_H__
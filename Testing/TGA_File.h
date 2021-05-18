#ifndef __TGA_FILE_H__
#define __TGA_FILE_H__

#include <fstream>
#include <vector>


struct TGAHeader
{
	// Header contains top 5 field in total of 18 bytes of data

	uint8_t		m_idLength;						// Length of image ID field
	uint8_t		m_colorMapType;					// Whether a color map is included, 0 = No color map, 1 = Color map present
	uint8_t		m_imageType;					// Compression and color type

	// Color Map specification 5 bytes, Describes the color map
	uint16_t	m_colorMapOrigin;				// index of first color map entry that is included in the file
	uint16_t	m_colorMapLength;				// number of entries of the color map that are included in the file
	uint8_t		m_ColorMapbitsPerPixel;			// number of bits per pixel, typically 15, 16, 24 or 32 bit per value

	// Image specification 10 bytes, Describes the image dimensions and format
	uint16_t	m_xOrigin;						// absolute horizontal coordinate
	uint16_t	m_yOrigin;						// absolute vertical coordinate
	uint16_t	m_width;						// width in pixels
	uint16_t	m_height;						// height in pixels
	uint8_t		m_bitsPerPixel;					// bits per pixel [24, 32]
	uint8_t		m_imageDescriptor;				// bits 0-3 give the alpha channel depth, bits 5-4 give direction

	void parse(const char const* buffer)
	{
		int index = 0;
		memcpy(&m_idLength, &buffer[index++], 1);
		memcpy(&m_colorMapType, &buffer[index++], 1);
		memcpy(&m_imageType, &buffer[index++], 1);

		memcpy(&m_colorMapOrigin, &buffer[index], 2);
		index += 2;

		memcpy(&m_colorMapLength, &buffer[index], 2);
		index += 2;

		memcpy(&m_ColorMapbitsPerPixel, &buffer[index++], 1);

		memcpy(&m_xOrigin, &buffer[index], 2);
		index += 2;

		memcpy(&m_yOrigin, &buffer[index], 2);
		index += 2;

		memcpy(&m_width, &buffer[index], 2);
		index += 2;

		memcpy(&m_height, &buffer[index], 2);
		index += 2;

		memcpy(&m_bitsPerPixel, &buffer[index++], 1);

		memcpy(&m_imageDescriptor, &buffer[index++], 1);
	}

	void display()
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
};

enum class ImageType {
	NO_IMAGE_DATA = 0,

	UNCOMPRESSED_COLOR_MAPPED = 1,
	UNCOMPRESSED_TRUE_COLOR = 2,
	UNCOMPRESSED_BLACK_WHITE = 3,

	RLE_COLOR_MAPPED = 9,
	RLE_TRUE_COLOR = 10,
	RLE_BLACK_WHITE = 11,
};

class TGAFile
{
	public:
		TGAFile(const std::string &sFilepath);
		~TGAFile();

		std::string getFileName() const;
		std::string getFilePath() const;

		size_t getSize() const;
		/*std::string getLine(int lineNumber) const;*/

		/*bool saveEditedData();*/

		// FRIEND FUNCTIONS
		friend std::ostream& operator<< (std::ostream& out, const TGAFile& fileHandler)
		{
			fileHandler.display();
			return out;
		}

	protected:
		void initialize(const std::string &sFilepath);
		std::string extractFileName(const std::string &sFilePath);

		void release();
		bool parse(const std::string &sFilepath);

		virtual void display() const;

	private:
		bool validRange(int lineNumber) const;
		std::string getFileNameFormRoot();

	private:
		std::vector<uint8_t>			m_pixels;
		std::string 					m_sFileName;
		std::string 					m_sFilePath;
		size_t							m_width{};	// In pixel
		size_t							m_height{};	// In pixel

		size_t							m_size{};

		size_t							m_bitsPerPixel{};
		bool							m_bIsCompressed{ true };
		int								m_version{1};
};

#endif		//#define __FILEHANDLER_H__
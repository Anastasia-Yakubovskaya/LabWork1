/**
 * @file bmp.h
 * @brief Declarations of BMPImage class and related structures for BMP image processing.
 *
 * This file contains definitions of the BMP headers and the BMPImage class,
 * which provides functionality to read, write, rotate, and apply filters to BMP images.
 */

#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <vector>
#include <string>
#include <fstream>

#pragma pack(push, 1)

/**
 * @struct BMPHeader
 * @brief Represents the BMP file header.
 *
 * Contains basic information about the BMP file such as file size,
 * file type, and offset to pixel data.
 */
struct BMPHeader {
    uint16_t bfType;        /**< File type (usually 'BM') */
    uint32_t bfSize;        /**< Size of the file in bytes */
    uint16_t bfReserved1;   /**< Reserved, must be 0 */
    uint16_t bfReserved2;   /**< Reserved, must be 0 */
    uint32_t bfOffBits;     /**< Offset to start of pixel data */
};

/**
 * @struct BMPInfoHeader
 * @brief Represents the BMP info header.
 *
 * Contains detailed information about the image such as dimensions,
 * color depth, and compression.
 */
struct BMPInfoHeader {
    uint32_t biSize;             /**< Size of this header (usually 40 bytes) */
    int32_t biWidth;             /**< Width of the image in pixels */
    int32_t biHeight;            /**< Height of the image in pixels */
    uint16_t biPlanes;           /**< Number of color planes (must be 1) */
    uint16_t biBitCount;         /**< Bits per pixel (e.g., 24 or 32) */
    uint32_t biCompression;      /**< Compression type (0 = none) */
    uint32_t biSizeImage;        /**< Size of image data in bytes */
    int32_t biXPelsPerMeter;     /**< Horizontal resolution (pixels per meter) */
    int32_t biYPelsPerMeter;     /**< Vertical resolution (pixels per meter) */
    uint32_t biClrUsed;          /**< Number of colors used (0 = default) */
    uint32_t biClrImportant;     /**< Number of important colors (0 = all) */
};

#pragma pack(pop)

/**
 * @class BMPImage
 * @brief Class for handling BMP images.
 *
 * Provides methods to read, write, rotate, and filter BMP images.
 *
 * Supports 24-bit and 32-bit uncompressed images.
 */
class BMPImage {
public:
    /**
     * @brief Default constructor.
     */
    BMPImage() {}

    /**
     * @brief Reads an image from a file.
     * @param filePath Path to the image file.
     * @return true if successful, false otherwise.
     *
     * Opens the file, reads headers and pixel data into memory.
     */
    bool read(const std::string& filePath);

    /**
     * @brief Writes the image to a file.
     * @param filePath Path where the image will be saved.
     * @return true if successful, false otherwise.
     *
     * Writes headers and pixel data from memory into a BMP file.
     */
    bool write(const std::string& filePath) const;

    /**
     * @brief Rotates the image 90 degrees clockwise.
     *
     * Changes the orientation of the image. Uses parallel processing for efficiency.
     */
    void rotateRight();

    /**
     * @brief Rotates the image 90 degrees counter-clockwise.
     *
     * Changes the orientation of the image. Uses parallel processing for efficiency.
     */
    void rotateLeft();

    /**
     * @brief Applies a Gaussian filter to the image with a specified kernel size.
     * @param kernelSize Size of the kernel (odd number from 3 to 11). Default is 3.
     *
     * Uses a Gaussian kernel for smoothing. The kernel size must be an odd number.
     */
    void applyGaussianFilter(int kernelSize = 3);

private:
    BMPHeader bmpHeader;             /**< The BMP file header. */
    BMPInfoHeader bmpInfoHeader;     /**< The BMP info header. */
    std::vector<uint8_t> pixels;     /**< Pixel data array. */

};

#endif // BMP_H

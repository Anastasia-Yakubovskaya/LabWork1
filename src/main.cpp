/*Yakubovskaya Anastasya st130155@student.spbu.ru LabWork1*/

#include <iostream>
#include "bmp.h"
#include <chrono>

int main() {
    auto total_start = std::chrono::high_resolution_clock::now();

    BMPImage image;

    auto start = std::chrono::high_resolution_clock::now();
    bool readSuccess = image.read("Airplane1.bmp");
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Reading time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    if (!readSuccess) {
        std::cerr << "Failed to read image!" << std::endl;
        return EXIT_FAILURE;
    }

    start = std::chrono::high_resolution_clock::now();
    image.rotateLeft();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Left rotation time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    bool writeSuccess = image.write("rotated_left.bmp");
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Writing rotated left time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    image.rotateRight();
    image.rotateRight();
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Double right rotation time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    writeSuccess &= image.write("rotated_right_second.bmp");
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Writing double rotated right time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    BMPImage leftImage;
    start = std::chrono::high_resolution_clock::now();
    readSuccess &= leftImage.read("rotated_left.bmp");
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Reading rotated left time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    leftImage.applyGaussianFilter(5);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Gaussian filter (left) time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    writeSuccess &= leftImage.write("filtered_rotated_left.bmp");
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Writing filtered left time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    BMPImage rightSecondImage;
    start = std::chrono::high_resolution_clock::now();
    readSuccess &= rightSecondImage.read("rotated_right_second.bmp");
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Reading rotated right second time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    rightSecondImage.applyGaussianFilter(5);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Gaussian filter (right second) time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    writeSuccess &= rightSecondImage.write("filtered_rotated_right_second.bmp");
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Writing filtered right second time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    auto total_end = std::chrono::high_resolution_clock::now();
    std::cout << "\nTotal execution time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(total_end - total_start).count()
              << " ms" << std::endl;

    return EXIT_SUCCESS;
}

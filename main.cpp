/*Yakubovskaya Anastasya st130155@student.spbu.ru LabWork1*/

#include <iostream>
#include "bmp.h"


int main()
{
    BMPImage image;

    image.read("Airplane.bmp");
 
    
    image.rotateLeft();
    image.write("rotated_left.bmp");
    


    image.rotateRight();
    image.rotateRight();
    image.write("rotated_right_second.bmp");


    BMPImage leftImage;
    leftImage.read("rotated_left.bmp");
    leftImage.applyGaussianFilter(5);
    leftImage.write("filtered_rotated_left.bmp");

    BMPImage rightSecondImage;
    rightSecondImage.read("rotated_right_second.bmp");
    rightSecondImage.applyGaussianFilter(5);
    rightSecondImage.write("filtered_rotated_right_second.bmp");

    return EXIT_SUCCESS;
}



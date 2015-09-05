#include "Checker.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Checker::Checker()
{

}

Checker::Checker(int _x, int _y)
{
    x = _x;
    y = _y;
}

std::string Checker::getBits()
{
    std::string bits = "";
    bits += r >= 128 ? '1' : '0';
    bits += g >= 128 ? '1' : '0';
    bits += b >= 128 ? '1' : '0';
    return bits;
}

void Checker::checkPixel(Mat* frame)
{
    Vec3b pixel = frame->at<Vec3b>(y, x);
    r = (int)pixel.val[2];
    g = (int)pixel.val[1];
    b = (int)pixel.val[0];
}

void Checker::printRGB()
{
    std::cout <<  " R: " << r
              << ", G: " << g
              << ", B: " << b << "\n";
}

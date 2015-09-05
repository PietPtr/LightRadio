#ifndef CHECKER_H
#define CHECKER_H

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Checker
{
    public:
        Checker();
        Checker(int x, int y);
        std::string getBits();
        void checkPixel(Mat* frame);
        void printRGB();
    protected:
    private:
        int r = 0;
        int g = 0;
        int b = 0;

        int x = 0;
        int y = 0;
};

#endif // CHECKER_H

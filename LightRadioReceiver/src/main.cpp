#include <iostream>
#include "Checker.h"

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

using namespace cv;

//640x480

int main(int argc, char* argv[])
{
    Checker checkers[12] = { };

    int checkIndex = 0;
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            checkers[checkIndex] = Checker(80 + x * 160, 80 + y * 160);
            checkIndex++;
        }
    }

    VideoCapture cap(-1);

    bool callibrating = true;
    int frameID = 0;
    int lastFrameID = 1;
    std::string totalBits;

    while( cap.isOpened() )
    {
        Mat frame;
        cap.read(frame);

        std::string bits = "";

        imshow("Float",frame);

        for (int i = 0; i < 12; i++)
        {
            checkers[i].checkPixel(&frame);
            bits += checkers[i].getBits();
        }
        //std::cout << bits << "\n";

        if (bits[0] == '1' && bits[1] == '0' && bits[2] =='0')
            frameID = 0;
        else
            frameID = 1;

        if (frameID != lastFrameID)
        {
            bits.erase(bits.begin(), bits.begin() + 3);
            totalBits += bits;
            std::cout << totalBits << "\n";
        }

        lastFrameID = frameID;

        int k = waitKey(17);
        if (k == 27)
            break;
        if (k == 10)
        {
            for (int i = 0; i < totalBits.length(); i+=8)
            {
                int value = 0;
                for (int b = 7; b >= 0; b--)
                {
                    if (totalBits[i + (7 - b)] == '1')
                        value += pow(2, b);
                }
                std::cout << (char)value;
            }
            std::cout << "\n";
        }
    }
    return 0;
}










#include <iostream>

#include <opencv2/core/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui/highgui.hpp>  // OpenCV window I/O

using namespace cv;

//640x480

int main(int argc, char* argv[])
{
    VideoCapture cap(-1);

    int i = 1000000;

    while( cap.isOpened() )
    {
        Mat frame;
        cap.read(frame);

        //imwrite("./frames/frame" + std::to_string(i) + ".jpg", frame);
        Vec3b pixel = frame.at<Vec3b>(0, 0);
        std::cout <<  " R: " << (int)pixel.val[2]
                  << ", G: " << (int)pixel.val[1]
                  << ", B: " << (int)pixel.val[0] << "\n";

        imshow("Float",frame);

        waitKey(17);
        i++;
    }
    return 0;
}

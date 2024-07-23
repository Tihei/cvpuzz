#include <iostream>
#include "C:\opencv\sources\include\opencv2\opencv.hpp"
#include <opencv2/opencv.hpp>
#include <mutex>


using namespace cv;

namespace cvpuzz {
    int blurring(Mat im,int row,int col) {


        Mat blurred(row, col, CV_8U);
        for (int i = 1; i < (row - 2); i++) {

            for (int j = 1; j < (col - 2); j++) {

                im.at<uchar>(i, j) =
                        (
                                (
                                        im.at<uchar>(i - 1, j - 1) + im.at<uchar>(i - 1, j) +
                                        im.at<uchar>(i - 1, j + 1) +
                                        im.at<uchar>(i, j - 1) + im.at<uchar>(i - 1, j) + im.at<uchar>(i - 1, j + 1) +
                                        im.at<uchar>(i + 1, j - 1) + im.at<uchar>(i - 1, j) + im.at<uchar>(i - 1, j + 1)
                                ) / 9
                        );
            }

        }


        return 0;
    }


    int difference(uchar a, uchar b) {

        int difference = 0;

        if ((a) > (b)) { difference = ((int) a - (int) b); }
        else { difference = ((int) b - (int) a); }

        return difference;

    }

    float difference(int a, int b) {

        int difference = 0;

        if ((a) > (b)) { difference = ( a - b ); }
        else { difference = ( b - a ) ; }

        return difference;

    }
};

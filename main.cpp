#include <iostream>
#include "C:\opencv\sources\include\opencv2\opencv.hpp"
#include <opencv2/opencv.hpp>
#include <mutex>

//Anleitung für das Compilieren des PRojekts:
//Opencv 4.10 direkt auf die C:/ Festplatte in einen Ordner "opencv" installieren (ca. 1 GB)
//Edit Configurations für den Compiler: Bei Clion, den Rechts neben der Run/Debug Funktion auf Edit Configurations
//Enviroment Variables -> PATH -> "C:/opencv/build/x64/vc16/bin;" hinzufügen, Enter, Apply





using namespace std;

using namespace cv;





    int templatematching (int threshold = 0,Mat origin = Mat() ,Mat excerpt = Mat() , int ii ,int jj)
    {
        int ie,je=0;
        while (abs(origin.at<int>(ii, jj) - excerpt.at<int>(ie, je)) < threshold && ii <= excerpt.rows) {

            ii++;
            ie++;

            while (je <= (excerpt.cols) ) {

                if (abs(origin.at<int>(ii, jj) - excerpt.at<int>(ie, je))> threshold)
                {break;}
                jj++;
                je++;
            }


        }
        return (ii-(ie/2));
    }


int location (int threshold = 10, Mat origin = Mat(), Mat excerpt = Mat())
{
    int w = origin.rows;
    int h = origin.cols;
    int wa = excerpt.rows;
    int ha = excerpt.cols;

    int ia,ja = 0;
    int i = 0;
    int j = 0;

    for (i;i<w;i++) {

        for (j; j < h; j++) {

            int match = templatematching(threshold,origin,excerpt,i,j);

            if (match!=h){return match;}
        }
    }

}



int main() {
    std::cout << "Hello, World!" << std::endl;
    cv::Mat testbild = cv::imread("tmp.jpg");
    cv::Mat ausschnitt = cv::imread("tmpausschnitt.png");
    cv::imshow("fenster", testbild);
    cv::waitKey(1000000);


   cout << location(10,testbild,ausschnitt);
    return 0;
    }

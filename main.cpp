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



    int templatematching (int threshold = 0, Mat origin = Mat() , Mat excerpt = Mat() , int ii=0, int jj=0)
    {
        int ie = 0;
        int je = 0;
        int width_excerpt = excerpt.cols;
        int height_excerpt = excerpt.rows;

        while (ii < width_excerpt) {

            ie++;

            if (abs(origin.at<int>((ii+ie), (jj+je)) - excerpt.at<int>(ie, je) ) < threshold )
            {
            while (je < (height_excerpt) ) {

                if (abs(origin.at<int>((ii+ie), (jj+je)) - excerpt.at<int>(ie, je)) < threshold)
                {
                    je++;
                }
                else
                    {return 1;}
                }

            }
            else
            {return 1;}
        }
        return (ii+(ie/2));
    }


int location (int threshold = 10 , Mat origin = Mat() , Mat excerpt = Mat() )
{
        Mat origin_bw;
        Mat excerpt_bw;
        cvtColor(origin,origin_bw,COLOR_BGR2GRAY);
        cvtColor(excerpt,excerpt_bw,COLOR_BGR2GRAY);

    int w = origin_bw.rows;
    int h = origin_bw.cols;

    for (int i = 0 ; i < h ; i++) {

        for (int j = 0; j < w; j++) {

            int match = templatematching(threshold,origin_bw,excerpt,i,j);
            if (match!=1){return match;}
        }
    }

}



int main() {
    std::cout << "Hello, World!" << std::endl;
    cv::Mat testbild = cv::imread("tmp2.jpg");
    cv::Mat ausschnitt = cv::imread("tmpausschnitt.png");
    cv::imshow("fenster", testbild);
    cv::waitKey(10);

    cout << location(10,testbild,ausschnitt);
    return 0;
    }

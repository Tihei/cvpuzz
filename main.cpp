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



    int templatematching (uchar threshold, Mat & origin, Mat excerpt , int ii, int jj)
    {
        int ie = 0;
        int je = 0;
        int width_excerpt = excerpt.cols;
        int height_excerpt = excerpt.rows;

        while (ii < width_excerpt) {



            if (abs(origin.at<uchar>((ii+ie), (jj+je)) - excerpt.at<uchar>(ie, je) ) < threshold )
            {

            while (je < height_excerpt ) {

                if (abs(origin.at<uchar>((ii+ie), (jj+je)) - excerpt.at<uchar>(ie, je)) < threshold)
                {
                    je++;
                    cout << "m" ;
                    origin.at<uchar>((ii+ie),(jj+je)) = 255;
                    circle(origin,Point((ii+ie),(jj+je)),5,Scalar_<double>(255,0,0));
                }
                else
                    {
                    cout << "N";
                    return 1;}
                }

            ie++;

            }
            else
            {return 1;}
        }

        return (ii+(width_excerpt/2)); // /2?
    }


    unsigned int location (uchar threshold , Mat& origin, Mat& excerpt)
    {
        Mat origin_bw(origin.rows,origin.cols,CV_8U);
        Mat excerpt_bw(excerpt.rows,excerpt.cols,CV_8U);;
        //origin.convertTo(origin_bw,)
        cvtColor(origin,origin_bw,COLOR_BGR2GRAY);
        cvtColor(excerpt,excerpt_bw,COLOR_BGR2GRAY);
        imshow("og_bw",origin_bw);
        waitKey(0);
        imshow("ex_bw",excerpt_bw);
        waitKey(0);
    int w = origin_bw.rows;
    int h = origin_bw.cols;
    int match = 0;

    for (int i = 0 ; i < h ; i++) {

        for (int j = 0; j < w; j++) {

            match = templatematching(threshold,origin_bw,excerpt_bw,i,j);
            if (match>1){return match;}
            cout << j << "x ";
        }
        cout << "i: "<< i << " " << endl;
    }

    return 1;
}



int main() {
    std::cout << "Hello, World!" << std::endl;
    cv::Mat testbild = cv::imread("tmp2.jpg");
    cv::Mat ausschnitt = cv::imread("tmpausschnitt.jpg");
    cv::imshow("fenster", testbild);
    cv::waitKey(100000);
    cv::imshow("Ausschitt",ausschnitt);
    waitKey(0);
    unsigned int result = location(2,testbild,ausschnitt);
    if(result!=1)
    {

        cout << "Bildausschnitt im Bild gefunden!\n" << "Es befindet sich in Reihe " << result << "" << endl;
        for(int i=0;i<testbild.rows;i++)
        {
            testbild.at<uchar>(result,i) = (255);

        }

        cout << result << endl;

        cv::imshow("fenster2", testbild); //Test test test i love uuu <3 work weiter bitch
        cv::waitKey(100000);

    }
    else
    {
        cout << "Bildausschnitt nicht im Bild gefunden!" << endl;
    }
    return 0;
    }

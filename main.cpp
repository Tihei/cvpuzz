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


    int difference (uchar a,uchar b)
    {

        int difference = 0;

        if(((int)a) > ((int)b)) {difference=((int)a-(int)b);}
        else {difference=( (int)b - (int) a );}

        return difference;

    }



unsigned int templatematching (int threshold, Mat & origin, Mat & excerpt , int ii, int jj) {
    int ie = 0;
    int je = 0;

    int width_origin = origin.cols;
    int height_origin = origin.rows;
    int width_excerpt = excerpt.cols;
    int height_excerpt = excerpt.rows;


    while ((ie < width_excerpt)) {

        uchar origin_at = origin.at<uchar>((ii + ie), (jj + je));
        uchar excerpt_at = excerpt.at<uchar>((ie), (je));

        int dif = difference(origin_at, excerpt_at);
        if (dif <= threshold) {

            while (je < (height_excerpt-1)) {
                origin_at = origin.at<uchar>((ii + ie), (jj + je));
                excerpt_at = excerpt.at<uchar>((ie), (je));
                dif = difference(origin_at, excerpt_at);

                if (dif < threshold) {
                    //cout << "m"
                    //circle(origin,Point_((ii+ie),(jj+je)),5,Scalar_<double>(255,0,0));
                } else {
                    //cout << "N";
                    return 1;
                }
                je++;
            }


        } else {
            return 1;
        }
        ie++;
    }

    if (!(((ii + ie) < width_origin) || ((jj + je) < height_origin)))
    {
        return 1;
    }
    else

    {

        unsigned int result = (ii + (width_excerpt / 2));
        return (result);
    }
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
        waitKey(0);
        imshow("ex_bw",excerpt_bw);
        waitKey(0);
    int w = (origin_bw.rows - 1 );
    int h = (origin_bw.cols - 1 );
    int we = (excerpt_bw.rows - 1 );
    int he = (excerpt_bw.cols - 1 );
    //cout << "w h we he" << w << h << we << he << endl;
    int match = 0;

    for (int i = 0 ; i < ((w-we)-1) ; i++) {

        for (int j = 0; j < (h-he); j++) {
            match = templatematching(threshold,origin_bw,excerpt_bw,i,j);
            if (match > 1)
            {
                cout << "match: " << match << endl;
                return match;
            }
        }
    }

    return 1;
}



int main() {
    std::cout << "Hello, World!" << std::endl;
    cv::Mat testbild = cv::imread("tmp2.jpg");
    cv::Mat ausschnitt = cv::imread("tmpausschnitt.jpg");
    cv::imshow("fenster", testbild);
    cv::waitKey(1000);
    //cv::imshow("Ausschitt",ausschnitt);
    //waitKey(0);
    int result = location( 10 ,testbild,ausschnitt);
    if(result > 1)
    {

        cout << "Bildausschnitt im Bild gefunden!\n" << "Es befindet sich in Reihe " << result << "" << endl;

        for(int i = (testbild.cols-1); i>0 ;i--)
        {
            testbild.at<uchar>( result,i) = (uchar) 0 ;
        }

        cout << result << endl;

        cv::imshow("fenster2", testbild); //Test test test i love uuu <3 work weiter bitch
        cv::waitKey(0000);

    }
    else
    {
        cout << "Bildausschnitt nicht im Bild gefunden!" << endl;
    }
    return 0;
    }

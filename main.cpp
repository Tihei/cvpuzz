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


    int blurring (Mat im)

    {
        Mat blurred (im.rows,im.cols,CV_8U);
        for(int i=1;i<(im.rows-2);i++)
        {

            for(int j=1;j < (im.cols-2);j++)
            {

                im.at<uchar>(i,j) =
                        (
                                (
                                        im.at<uchar>(i-1,j-1)   + im.at<uchar>(i-1,j) + im.at<uchar>(i-1,j+1) +
                                        im.at<uchar>(i,j-1)     + im.at<uchar>(i-1,j) + im.at<uchar>(i-1,j+1) +
                                        im.at<uchar>(i+1,j-1)   + im.at<uchar>(i-1,j) + im.at<uchar>(i-1,j+1)
                                ) /9
                        );
            }

        }


       return 0;
    }



    int difference (uchar a,uchar b)
    {

        int difference = 0;

        if((a) > (b)) {difference=((int)a-(int)b);}
        else {difference=( (int)b - (int) a );}

        return difference;

    }



    int templatematching (int threshold, Mat & origin, Mat & excerpt , int ii, int jj)
    {

    int ie        = 0;
    int je        = 0;
    int hits      = 0;
    int total_dif = 0;

    int width_origin = origin.cols;
    int height_origin = origin.rows;
    int width_excerpt = excerpt.cols;
    int height_excerpt = excerpt.rows;


    while (je < (height_excerpt-1))
    {
        if( ( (width_excerpt + ie + 1) >= width_origin) || ( (height_excerpt + je + 1) >= height_origin) )
        {
            ie=0;
            break;
        }

        uchar origin_at = origin.at<uchar>(   (jj + je),(ii + ie)  );
        uchar excerpt_at = excerpt.at<uchar> (je, ie);

        int dif = 0;

            while (ie < width_excerpt )
            {
                if( ( (width_excerpt + ie + 1) > width_origin) )
                {
                    ie=0;
                    break;
                }

                origin_at = origin.at<uchar>((jj + je),(ii + ie));
                excerpt_at = excerpt.at<uchar> (je, ie);
                dif = difference(origin_at,excerpt_at);

                //cout << " dif: " << dif << "  " ;


                if (dif <= threshold)
                {
                    total_dif += dif;
                   hits++;
                }

                //cout << "Hits Ie :" << hits << "     " << endl;
                ie++;
            }
        ie=0;
        je++;
    }

    if(hits == (width_excerpt*height_excerpt)) cout << "Bildausschnitt im Bild gefunden!\n"<< endl;
    //return hits;
    return total_dif;
    }


        Point_<int> location (int threshold , Mat& origin, Mat& excerpt)
    {
        Mat origin_bw(origin.cols,origin.cols,CV_8U);
        Mat excerpt_bw(excerpt.rows,excerpt.cols,CV_8U);;

        cvtColor(origin,origin_bw,COLOR_BGR2GRAY);
        cvtColor(excerpt,excerpt_bw,COLOR_BGR2GRAY);

        blurring(origin_bw);
        blurring(excerpt_bw);


        imshow("og_bw",origin_bw);
        waitKey(20);
        imshow("ex_bw",excerpt_bw);
        waitKey(0);

    int most_hits = 0;
    int min_dif = 100000 ;
    Point_<int> most_hits_point = Point_(0,0);
    int w = (origin_bw.cols - 1 );
    int h = (origin_bw.rows - 1 );
    int we = (excerpt_bw.cols - 1 );
    int he = (excerpt_bw.rows - 1 );

    for (int i = 0 ; i < ((w-we-1)) ; i++)
    {
        //Eine "Progress-Bar"
        if (i % (w/100) == 0)
        {
            cout << (i / ((w-we)/100)) << "%" << endl;
        }

        for (int j = 0; j < (((h-he)-1)/2); j++) {
            //cout << " J: " << j << "  / " << h <<"/" << he <<endl;

            int hits = templatematching(threshold,origin_bw,excerpt_bw,i,j*2);

            //cout << " Hits: " << hits << " " << endl ;

            if (hits == (origin_bw.cols*origin_bw.rows)) break;

            if (min_dif > hits)
            {
                min_dif = hits;
                most_hits_point = Point_( (i + (excerpt_bw.cols/2)),(j*2+(excerpt_bw.rows/2)) );
                cout << "Dif: " << min_dif << " at : " << most_hits_point << endl ;

            }


            /* if (hits > most_hits)
            {
                most_hits=hits;
                most_hits_point = Point_( (i + (excerpt_bw.cols/2)),(j*2+(excerpt_bw.rows/2)));
                cout << "Hits:" << most_hits << " at :" << most_hits_point << endl;
            }
            */
        }

    }
    return most_hits_point;
}




int main()
{

    cv::Mat testbild = cv::imread("tmp2.jpg");
    cv::Mat ausschnitt = cv::imread("tmpausschnitt3.jpg");
    cv::Mat ausschnitt2 = cv::imread("tmpausschnitt32.jpg");
    cv::imshow("fenster", testbild);
    cv::waitKey(10);

    //cv::imshow("Ausschitt",ausschnitt);
    //waitKey(0);

    Point_<int> result = location( 30 ,testbild,ausschnitt);
    cout << result << endl;

    if(result != Point_<int>(0,0))
    {
        waitKey(20);
        circle(testbild,result,50,Scalar_(0,0,255),4);
        circle(testbild,result,5,Scalar_(0,0,255),1);

        cout << result << endl;

        cv::imshow("fenster2",  testbild); //Test test test i love uuu <3 work weiter bitch

        cv::waitKey(10000);

        result = location(30,testbild,ausschnitt2);
        circle(testbild,result,50,Scalar_(0,0,255),4);
        circle(testbild,result,5,Scalar_(0,0,255),1);


        cv::imshow("fenster3",testbild);
        cv::waitKey(0);
        cv::waitKey(0);
    }
    else
    {
        cout << "Bildausschnitt nicht im Bild gefunden!" << endl;
        return 1;
    }



    return 0;
    }

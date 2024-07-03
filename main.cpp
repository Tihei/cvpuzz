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



    int templatematching (int threshold, Mat & origin, Mat & excerpt , int ii, int jj) {
    int ie = 0;
    int je = 0;
    int hits = 0;

    int width_origin = origin.cols;
    int height_origin = origin.rows;
    int width_excerpt = excerpt.cols;
    int height_excerpt = excerpt.rows;


    while (ie < (height_excerpt-1))
    {
        //Davon ausgeganen, das "ie" die breite und somit x sein soll, sind die Beiden Schleifen vertauscht
        //Somit sind x und Y verdreht, sind aber laut Code immer richtig zugewiesen,
        // aber in dieser Konfiguration scheint es zu funktionieren


        uchar origin_at = origin.at<uchar>((ii + ie), (jj + je));
        uchar excerpt_at = excerpt.at<uchar>((ie), (je));

        int dif = difference(origin_at, excerpt_at);

            //cout<< " I:" << ie << " / " << width_excerpt << endl;

            while (je < (width_excerpt-1) )
            {
                //cout<< " J:" << je << " / " << height_excerpt << " ";

                origin_at = origin.at<uchar>((ii + ie), (jj + je) );
                excerpt_at = excerpt.at<uchar>((ie), (je) );

                dif = difference(origin_at, excerpt_at);
                //cout << " dif: " << dif << "  " ;

                if (dif <= threshold)
                {
                   hits++;
                }

                je++;
                if( ( (width_excerpt + ie + 1) > width_origin) || ( (height_excerpt + je + 1) > height_origin) )
                {
                    break;
                }
            }


        ie++;
    }

    if(hits == (width_excerpt*height_excerpt)) cout << "Bildausschnitt im Bild gefunden!\n"<< endl;
    return hits;
}


        Point_<int> location (int threshold , Mat& origin, Mat& excerpt)
    {
        Mat origin_bw(origin.rows,origin.cols,CV_8U);
        Mat excerpt_bw(excerpt.rows,excerpt.cols,CV_8U);;

        //origin.convertTo(origin_bw,)
        cvtColor(origin,origin_bw,COLOR_BGR2GRAY);
        cvtColor(excerpt,excerpt_bw,COLOR_BGR2GRAY);
        blurring(origin_bw);
        blurring(excerpt_bw);


        imshow("og_bw",origin_bw);
        waitKey(0);
        imshow("ex_bw",excerpt_bw);
        waitKey(0);
    int most_hits = 0;
    Point_<int> most_hits_point = Point_(0,0);
    int w = (origin_bw.rows - 1 );
    int h = (origin_bw.cols - 1 );
    int we = (excerpt_bw.rows - 1 );
    int he = (excerpt_bw.cols - 1 );
    //cout << "w h we he" << w << h << we << he << endl;

    for (int i = 0 ; i < ((w-we-1)) ; i++)
    {
        //cout << origin_bw.cols << " / "<< origin_bw.rows << endl;
        cout << " I: " << i << endl;
        for (int j = 0; j < ((h-he-1)); j++) {


            int hits = templatematching(threshold,origin_bw,excerpt_bw,i,j);
            //cout << " Hits: " << hits << " " << endl ;
            if (hits == (origin_bw.cols*origin_bw.rows))break;
            if (hits > most_hits)
            {
                most_hits=hits;
                most_hits_point = Point_((j+(excerpt_bw.rows/2)) , (i + (excerpt_bw.cols/2)) );
                cout << "Hits:" << most_hits << " at :" << most_hits_point << endl;
            }

        }

    }
    return most_hits_point;
}




int main()
{

    cv::Mat testbild = cv::imread("tmp2.jpg");
    cv::Mat ausschnitt = cv::imread("tmpausschnitt3.jpg");
    cv::imshow("fenster", testbild);
    cv::waitKey(1000);
    //cv::imshow("Ausschitt",ausschnitt);
    //waitKey(0);

    Point_<int> result = location( 10 ,testbild,ausschnitt);
    cout << result << endl;

    if(result != Point_<int>(0,0))
    {

        circle(testbild,result,50,Scalar_(0,0,255),3);

        cout << result << endl;

        cv::imshow("fenster2",  testbild); //Test test test i love uuu <3 work weiter bitch
        cv::waitKey(0);

    }
    else
    {
        cout << "Bildausschnitt nicht im Bild gefunden!" << endl;
    }

    return 0;

    }

#include <iostream>
#include "C:\opencv\sources\include\opencv2\opencv.hpp"
#include <opencv2/opencv.hpp>
#include <mutex>
#include "cvpuzz_math.h"
#include <cmath>



using namespace std;

using namespace cv;





    int templatematching (int threshold, Mat & origin, Mat & excerpt , int starting_i, int starting_j)
    {

    int i_excerpt       = 0;
    int j_excerpt       = 0;
    int hits      = 0;
    int total_dif = 0;

    int width_origin = origin.cols;
    int height_origin = origin.rows;
    int width_excerpt = excerpt.cols;
    int height_excerpt = excerpt.rows;


    while (j_excerpt < (height_excerpt-1))
    {

        if( ( (width_excerpt + i_excerpt + 1) >= width_origin) || ( (height_excerpt + j_excerpt + 1) >= height_origin) )
        {
            i_excerpt=0;
            break;
        }


        uchar origin_at = origin.at<uchar>(   (starting_j + j_excerpt),(starting_i + i_excerpt)  );
        uchar excerpt_at = excerpt.at<uchar> (j_excerpt, i_excerpt);


        int dif = 0;


            while (i_excerpt < width_excerpt )
            {

                if( ( (width_excerpt + i_excerpt + 1) > width_origin) )

                {
                    i_excerpt=0;
                    break;
                }



                origin_at = origin.at<uchar>( (starting_j + j_excerpt) , (starting_i + i_excerpt) );

                excerpt_at = excerpt.at<uchar> (j_excerpt, i_excerpt);

                dif = cvpuzz::difference(origin_at,excerpt_at);


                //cout << " dif: " << dif << "  " ;

                total_dif += dif;


                if (dif <= threshold)
                {
                    //cout << " / " << total_dif << endl;
                    hits++;
                }

                else


                {
                    //Mit diesem Block sollen Punkte, die mehr als der Schwellwert abwecihen, extra bestraft werden
                    //total_dif += 255;
                }

                //cout << "Hits Ie :" << hits << "     " << endl;
                i_excerpt++;
            }


        i_excerpt=0;
        j_excerpt++;

    }

    if(hits == (width_excerpt*height_excerpt))
        cout << "Bildausschnitt im Bild gefunden!\n"<< endl;


    //return hits;
    return total_dif;


    }



        vector<Point_<int>> location (int threshold , Mat& origin, Mat& excerpt)

        {

        Mat origin_bw(origin.rows,origin.cols,CV_8U);
        Mat excerpt_bw(excerpt.rows,excerpt.cols,CV_8U);;

        cvtColor(origin,origin_bw,COLOR_BGR2GRAY);
        cvtColor(excerpt,excerpt_bw,COLOR_BGR2GRAY);



        cvpuzz::blurring(origin_bw,origin_bw.rows,origin_bw.cols);
        cvpuzz::blurring(excerpt_bw,excerpt_bw.rows,excerpt_bw.cols);


        imshow("og_bw",origin_bw);
        waitKey(200);
        imshow("ex_bw",excerpt_bw);
        waitKey(0);

    int most_hits = 0;
    int min_dif = 100000000 ;
    Point_<int> most_hits_point = Point_(0,0);
    Point_<int> most_hits_point_end = Point_(0,0);
    int w = (origin_bw.cols - 1 );
    int h = (origin_bw.rows - 1 );
    int we = (excerpt_bw.cols - 1 );
    int he = (excerpt_bw.rows - 1 );


    for (int i = 0 ; i < ((w-we-1)) ; i++)
    {
        //Eine "Progress-Bar"

        if (i % ( (w-we) / 100 ) == 0 )
        {
            cout << (i / ( (w-we) / 100 ) ) << "%" << endl;
        }

        for (int j = 0; j < (((h-he)-1)/2); j++) {
            //cout << " J: " << j << "  / " << h <<"/" << he <<endl;

            int hits = templatematching(threshold,origin_bw,excerpt_bw,i,j*2);

            //cout << " Hits: " << hits << " " << endl ;

            if (hits == (origin_bw.cols*origin_bw.rows)) break;

            if (min_dif > hits)
            {
                min_dif = hits;
                most_hits_point = Point_((i) , (j) );
                //cout << "Dif: " << min_dif << " at : " << most_hits_point << endl ;

            }


            /* if (hits > most_hits)
            {
                most_hits=hits;
                most_hits_point = Point_( );
                most_hits_point_end = Point_( (i + (excerpt_bw.cols/2)),(j*2+(excerpt_bw.rows/2));
                cout << "Hits:" << most_hits << " at :" << most_hits_point << endl;
            } */

        }

    }

    most_hits_point_end = Point_(( (most_hits_point.x) + (excerpt_bw.cols) ) , ( (most_hits_point.y) +(excerpt_bw.rows) ));


    return {most_hits_point , most_hits_point_end} ;

        }




int main()
{

        const String projectpath = "C:\\Users\\Tim\\CLionProject\\cvpuzz" ;

    cv::Mat testbild = cv::imread((projectpath+"\\pictures\\tmp2.jpg"));
    cv::Mat ausschnitt = cv::imread(projectpath+"\\pictures\\tmpausschnitt3.jpg");
    cv::Mat ausschnitt2 = cv::imread(projectpath+"\\pictures\\tmpausschnitt31.jpg");
    cv::Mat ausschnitt3 = cv::imread(projectpath+"\\pictures\\tmpausschnitt32.jpg");


    //cv::imshow("fenster", testbild);

    cv::waitKey(100);

    //cv::imshow("Ausschitt",ausschnitt);

    //waitKey(20000);


    vector<Point_<int>> result = location( 20 ,testbild,ausschnitt2);


    //circle(testbild,maxloc,5,(0,0,255,0),2);

    //cv::imshow("result",testbild);

    waitKey(10000);

    if(result[0] != Point_<int>(0,0))
    {

        waitKey(1000);
        cvtColor(testbild,testbild,COLOR_BGRA2BGR);

        //cv::circle(testbild,result[0],50,Scalar_(0,0,255,0),4);
        //cv::circle(testbild,result[0],5,Scalar_(0,0,255,0),1);
        //Diese beide Funktionen scheinen ohne Änderungen scheinbar Grundlos nicht mehr zu funktionieren.

        cv::rectangle(testbild,result[0],result[1],Scalar_<int>(0,255,0,0),4);

        //Zuerst wird meine Implementation des "Ausschnitt-Finderns" ausgeführt,
        //der leider eine Weile braucht, nach aktuellem unoptimiertem Stand.
        //In Folge wird die Opencv-interne Funktion aufgerufen, die effizienter läuft



        cv::Mat resultmat((testbild.rows),(testbild.cols),CV_32FC1);
        cv::matchTemplate(testbild,ausschnitt2,resultmat,3);

        Point_<int> maxloc = Point_(0,0);

        cv::minMaxLoc(resultmat,nullptr, nullptr,nullptr,&maxloc);
        cout << maxloc << endl;

        cv::rectangle(testbild,
                      Point_<int> ( (maxloc.x) , (maxloc.y) ),
                      Point_<int>( (maxloc.x) + (ausschnitt.cols) , (maxloc.y) + (ausschnitt.rows) ),
                      Scalar_<int>( 0,0,0,255 ) ,4
                      );
        float tmp_dif_row = cvpuzz::difference( (result[1].y) ,(result[0].y) );
        float tmp_dif_cols = cvpuzz::difference( (result[1].x) , (result[0].x) ) ;
        float difference_ = sqrt
                (
                        ( ( tmp_dif_row*tmp_dif_row ) + (tmp_dif_cols * tmp_dif_cols ) )
                );

        waitKey(1000);

        cout << result << endl;

        cout << "Difference between own and internal function:" << difference_ << endl;

        waitKey(1000);


        cv::imshow("Fenster3", testbild);
        cv::waitKey(100000);

        result = location(30, testbild, ausschnitt2);

            cv::circle(testbild,
                       Point_( ( (result[0].x) + (ausschnitt2.cols/2)),((result[0].y) + (ausschnitt2.rows/2)) ),
                       50, Scalar_(255, 0, 0,0), 4

                       );

            cv::rectangle(testbild,result[0],result[1],Scalar_<int>(255,0,0,0),3);
                                                                                            // B G R A

            cv::matchTemplate(testbild,ausschnitt2,resultmat,3);

            cv::minMaxLoc(resultmat, nullptr,nullptr,nullptr,&maxloc);





            cout << maxloc << endl;
        cv::circle(testbild,
                   maxloc ,
                   50, Scalar_(0, 0, 255,0), 4
                                                 //B G R A (Green)
                   );

            cv::waitKey(1000);
            cv::imshow("circled", testbild);
            cv::waitKey(0);

    }

    else

    {

        cout << "Bildausschnitt nicht im Bild gefunden!" << endl;

        return 1;

    }



    return 0;

    }

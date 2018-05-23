#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {

    Mat src, cannyResult, laplaceResult;
    Mat resultado, src_gray, thresholdResult,figure1;

    double largest_area=0;


//          src = imread( "2reais.png", 1 );
//          src = imread( "5reais.png", 1 );
//          src = imread( "10reais.png", 1 );
//          src = imread( "20reais.png", 1 );
//          src = imread( "20reais2.png", 1 );
//          src = imread( "50reais.png", 1 );
//          src = imread( "100reais.png", 1 );
//          src = imread( "150reais.JPG", 1 );
//          src = imread( "7reais.JPG", 1 );
//          src = imread( "30reais.JPG", 1 );
//          src = imread( "150reais.JPG", 1 );
          src = imread( "235reais.png", 1 );
//          src = imread( "145reais.png", 1 );
//          src = imread( "205reais.png", 1 );
//          src = imread( "17reais.JPG", 1 );

    /// Transformando a imagem para tons de cinza
    cvtColor( src, src_gray, COLOR_RGB2GRAY );

    /// Suaviaza imagem com blur
    cv::medianBlur(src_gray, resultado, 3);

    threshold( resultado, thresholdResult, 0, 255, 3);

    /// Método de canny para detecção de bordas
    Canny( thresholdResult, cannyResult, 20, 80, 3);

    namedWindow( "Canny", CV_WINDOW_AUTOSIZE );
    imshow( "Canny", cannyResult );

    /// Aplicação do método de Laplace para realce das bordas
    Laplacian(cannyResult, laplaceResult, CV_8U, 1,1,0,BORDER_DEFAULT );

    namedWindow( "Laplace", CV_WINDOW_AUTOSIZE );
    imshow( "Laplace", laplaceResult );

    Rect rect;
    vector<Rect> rects;
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

    /// Detecta os contornos
    findContours( laplaceResult, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    for(unsigned int i=0; i<contours.size(); i++) {

        /// Detecta a áredo do contorno da posição i
        double contourAreaResult = contourArea(contours[i], false);

        if(contourAreaResult > largest_area){
            largest_area = contourAreaResult;

            rect=boundingRect(contours[i]);
            rects.push_back(rect);

         }
    }

    int result=0;
    for(unsigned int j=0; j<rects.size(); j++) {
            src(rects[j]).copyTo(figure1);

            rectangle(src, rects[j],  Scalar(0,255,0), 2, 8,0);

            src(rects[j]).copyTo(figure1);

            cv::Mat blue_hsv;
            cvtColor(figure1, blue_hsv, cv::COLOR_RGB2HSV);


            Vec3b& hsv = blue_hsv.at<Vec3b>(7,7);

            int hue = 0;
            hue = hsv[0]; // valor de H (do HSV)

            if (hue>5 && hue <=16) {
                cout<<"\t Nota de 2 \n";
                result+=2;
            }
            else if (hue>130 && hue <=170) {
                cout<<"\t Nota de 5 \n";
                result+=5;
            }
            else if (hue>106 && hue <=120) {
                cout<<"\t Nota de 10 \n";
                result+=10;
            }
            else if (hue>80 && hue <=100) {
                cout<<"\t Nota de 20 \n";
                result+=20;
            }
            else if (hue>=101 && hue <=106) {
                cout<<"\t Nota de 50 \n";
                result+=50;
            }
            else if (hue>16 && hue <=35) {
                cout<<"\t Nota de 100 \n";
                result+=100;
            }
            else {
                cout<<"\t Valor não identificado \n";
            }
    }


    cout<<"Valor Total: "<<result<<" reais \n";

    namedWindow("Seleção das cédulas", CV_WINDOW_AUTOSIZE);
    imshow("Seleção das cédulas", src);

    waitKey(0);

    return 0;
}







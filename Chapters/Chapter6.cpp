//
//  Chapter6.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/9/21.
//

//############### Color Detection ###############

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    string path = "Resources/shapes.png";
    Mat img = imread(path);
    Mat imgHSV, mask;
    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 19, smax = 240, vmax = 255;
    
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    
    namedWindow("Trackbars", WINDOW_NORMAL);
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
   
    imshow("Image",img);
    imshow("Image HSV",imgHSV);
    
    while (true) {
    
        Scalar lower(hmin, smin, vmin);     //hue (0,180), saturation (0,255), value (0,255)
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV,lower,upper,mask);

        imshow("Image Mask",mask);
        waitKey(1);
    }
    
    return 0;
}*/

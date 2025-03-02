//
//  ColorPicker.cpp
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
    
    //VideoCapture cap(0);
    Mat img;
    Mat imgHSV, mask;
    int hmin = 20, smin = 130, vmin = 140;
    int hmax = 40, smax = 240, vmax = 255;
    
    namedWindow("Trackbars", WINDOW_NORMAL);
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
    
    while (true) {
        //cap.read(img);
        string path = "Resources/test.png";
        img = imread(path);
        
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        inRange(imgHSV,lower,upper,mask);

        imshow("Image",img);
        imshow("Image HSV",imgHSV);
        imshow("Image Mask",mask);
        cout << hmin << ", " << smin << ", " << vmin << ", " << hmax << ", " << smax << ", " << vmax << endl;
        waitKey(1);
    }
    
    return 0;
}
*/

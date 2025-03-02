//
//  Chapter3.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/8/21.
//

//############### Resize and Crop Images ###############

/*#include <stdio.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat imgResize, imgCrop;
    
    //cout << img.size() << endl;     //print out the size of the image
    resize(img, imgResize, Size(640,480));      //will resize
    resize(img, imgResize, Size(),0.5,0.5);     //will scale
    
    Rect roi(100,100,300,250);  //ROI is region of interest. From (100,100), we travel 300 points in the x-direction (right) and 250 points in the y-direction (down).
    imgCrop = img(roi);

    
    imshow("Image",img);
    imshow("Image Resize",imgResize);
    imshow("Image Crop",imgCrop);

    waitKey(0);
    
}*/

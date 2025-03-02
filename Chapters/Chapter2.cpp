//
//  Chapter2.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/8/21.
//

//############### Basic Functions ###############

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    string path = "Resources/test.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDia, imgErode;
    
    cvtColor(img,imgGray,COLOR_BGR2GRAY);    //convert to grayscale -- note the destination image is inside the function -- control click the function name to see its definition
    GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);    //Gaussian blur
    Canny(imgBlur,imgCanny,50,150);     //Canny edge detector -- commmon practice when using Canny edge detector to also use a little bit of blur before it
    
    //Sometimes when you detect edges, they are not completely filled, or they are not joined. To fix, you can dilate--increase their thickness, or you can erode--decrease their thickness. These come in handy when you are trying to detect the shape of different objects
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));  //kernel to be used with dilation or erosion (only use odd numbers) -- if we increase it will dilate more, if we decrease it will dilate less
    dilate(imgCanny, imgDia, kernel);
    erode(imgDia, imgErode, kernel);
    
    imshow("Image",img);
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDia);
    imshow("Image Erosion", imgErode);
    waitKey(0);
    
}*/

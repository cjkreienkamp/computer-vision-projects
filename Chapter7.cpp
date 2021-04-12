//
//  Chapter7.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/9/21.
//

//############### Shapes/Contour Detection ###############

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void getContours(Mat imgDil, Mat img) {
    
    vector<vector<Point>> contours;  //vector with more vectors inside
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());     //variable that we are introducing to the vector
    string objectType;
    
    // Filter to remove noise
    for (int i=0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        cout << area << endl;
        
        if (area>1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
            drawContours(img, conPoly, i, Scalar(255,0,255), 2);
            cout << conPoly[i].size() << endl;      //print the number of corner points
            
            // Create a bounding rectangle around each shape
            boundRect[i] = boundingRect(conPoly[i]);    //function we are calling to find the bounding rectangle around it
            //rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0), 5);
           
            // Write the type of shape above each shape
            int objCor = (int)conPoly[i].size();
            if (objCor == 3) {objectType = "Triangle";}
            if (objCor == 4) {
                
                float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
                if (aspRatio > 0.95 && aspRatio < 1.05) {
                    objectType = "Square";
                } else {
                    objectType = "Rectangle";
                }
            }
            if (objCor > 4) {objectType = "Circle";}
            putText(img,objectType,{boundRect[i].x, boundRect[i].y-5},FONT_HERSHEY_PLAIN,1,Scalar(0,69,255),1);
        }
    }
    
}

int main() {
    
    string path = "Resources/shapes.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
    
    // Preprocessing
    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);
    Canny(imgBlur,imgCanny,25,75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    dilate(imgCanny, imgDil, kernel);
    
    getContours(imgDil, img);
    
    imshow("Image",img);
    imshow("Image Gray",imgGray);
    imshow("Image Blur",imgBlur);
    imshow("Image Canny",imgCanny);
    imshow("Image Dilate",imgDil);
    waitKey(0);
    
    return 0;
}*/


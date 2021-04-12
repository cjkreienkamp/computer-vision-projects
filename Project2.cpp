//
//  Project2.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/9/21.
//

//############### Image Scanner ###############

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;


Mat imgOriginal, imgGray, imgCanny, imgThre, imgBlur, imgDil, imgErode, imgWarp, imgCrop;
vector<Point> initialPoints, docPoints;

float w = 420, h = 596;     // width and height of A4 paper multiplied by 2 (because too small if not 2x)


Mat preProcessing(Mat img)
{
    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    GaussianBlur(imgGray,imgBlur,Size(3,3),3,0);
    Canny(imgBlur,imgCanny,25,75);
    
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    dilate(imgCanny, imgDil, kernel);
    //erode(imgDil, imgErode, kernel);
    
    return imgDil;
}


vector<Point> getContours(Mat imgDil)
{
    
    vector<vector<Point>> contours;  //vector with more vectors inside
    vector<Vec4i> hierarchy;

    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    vector<vector<Point>> conPoly(contours.size());
    vector<Point> biggest = {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
    int maxArea = 0;
    
    // Filter to remove noise
    for (int i=0; i < contours.size(); i++)
    {
        int area = contourArea(contours[i]);
        
        if (area>1000)
        {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
            
            if (area > maxArea && conPoly[i].size() == 4) {
                //drawContours(imgOriginal, conPoly, i, Scalar(255,0,255), 5);
                biggest = {conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3]};
                maxArea = area;
                
            }
        }
    }
    
    return biggest;
}


void drawPoints(vector<Point> points, Scalar color)
{
    for (int i=0; i<points.size(); i++){
        circle(imgOriginal, points[i], 10, color, FILLED);
        putText(imgOriginal, to_string(i), points[i], FONT_HERSHEY_PLAIN, 4, color, 4);
    }
}


vector<Point> reorder(vector<Point> points)     // make the tl point be 0 and the br point be 3
{
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;
    
    for (int i=0; i<4; i++){
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }
    
    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);   //0
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);   //1
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]);   //2
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]);   //3
    
    return newPoints;
}


Mat getWarp(Mat img, vector<Point> points, float w, float h)
{
    Point2f src[4] = {points[0],points[1],points[2],points[3]};     //source points
    Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };       //destination points
    
    Mat matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w,h));
    
    return imgWarp;
}


int main() {
    
    // Image -- must remove extra "}" at the end due to the while loop when commenting out Webcam part
    //string path = "Resources/paper.jpg";
    //imgOriginal = imread(path);
    //resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);
    
    // Webcam
    VideoCapture cap(0);
    
    while (true) {
        
        cap.read(imgOriginal);
    
    
    // Image Preprocessing
    imgThre = preProcessing(imgOriginal);
    
    // Get Contours - Biggest
    initialPoints = getContours(imgThre);
    docPoints = reorder(initialPoints);
    //drawPoints(docPoints, Scalar(0,255,0));
    
    // Warp
    imgWarp = getWarp(imgOriginal, docPoints, w, h);
    
    // Crop
    int cropVal = 10;
    Rect roi(cropVal,cropVal,w-(2*cropVal),h-(2*cropVal));
    imgCrop = imgWarp(roi);
    
    imshow("Image",imgOriginal);
    imshow("Image Dilation",imgThre);
    imshow("Image Warp", imgWarp);
    imshow("Image Crop", imgCrop);
    waitKey(1);
    }

    return 0;
}
*/

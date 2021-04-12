//
//  Chapter5.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/9/21.
//

//############### Warp Perspective ###############
// Warping could be used to give a bird's eye view to an image taken from the side.

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

float w = 250, h=350;   //width and height of card
Mat matrix,imgWarp;

int main() {
    
    string path = "Resources/cards.jpg";
    Mat img = imread(path);
    
    Point2f src[4] = {{529,142},{771,190},{405,395},{674,457}};     //source points
    Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };       //destination points
    
    matrix = getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w,h));
    
    for (int i=0; i<4; i++) {
        circle(img, src[i], 10, Scalar(0,0,255), FILLED);       //make sure we actually chose the correct points
    }
    
    imshow("Image",img);
    imshow("Image Warp",imgWarp);
    waitKey(0);

    return 0;
}
*/

//
//  Chapter4.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/8/21.
//

//############### Drawing Shapes and Text ###############

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {

    // Blank Image
    Mat img(512,512, CV_8UC3, Scalar(255,255,255));  //CV_8UC3 means unsigned 8 bits -- a range from 0 to 255
    
    // Circle, Rectangle, Line, Text
    circle(img,Point(256,256),155,Scalar(0,69,255),10);     //thickness is 10
    circle(img,Point(256,256),155,Scalar(0,69,255),FILLED);     //circle is filled
    rectangle(img,Point(130,226),Point(382,286),Scalar(255,255,255),FILLED);  //if you define a rectangle as points, it will be the top left corner and the bottom right corner (as opposed to defining the top left corner and the width and height if you use Rect)
    line(img,Point(130,296),Point(382,296),Scalar(255,255,255),2);  //starting and ending point
    putText(img,"Murtaza's Workshop",Point(137,262),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,69,255),2);
    
    imshow("Image",img);

    waitKey(0);
    
}
*/

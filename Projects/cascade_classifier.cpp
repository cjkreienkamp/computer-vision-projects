//
//  cascade_classifier.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 12/20/21.
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

 
int main() {
 
    string path = "/Users/chriskreienkamp/OpenCV-C++/WaterPoloApp/WaterPoloApp/data/lindbergh/sluh-lindbergh/040717/video.mp4";
    VideoCapture cap(path);
    Mat img;
    Mat legend(300,100, CV_8UC3, Scalar(255,255,255));
    int frameCount = static_cast<int>(cap.get(CAP_PROP_FRAME_COUNT));
    int frameNumber = -1;
    
    putText(legend,"p: pause",Point(10,25),FONT_HERSHEY_DUPLEX,0.5,Scalar(0,0,255),1);
    putText(legend,"o: positive",Point(10,125),FONT_HERSHEY_DUPLEX,0.5,Scalar(0,0,255),1);
    putText(legend,"i: negative",Point(10,225),FONT_HERSHEY_DUPLEX,0.5,Scalar(0,0,255),1);
    imshow("Legend", legend);
    
    while (true) {
        
        cap.read(img);
        frameNumber++;
        
        //if (frameNumber<5700) {continue;}
        
        imshow("Image", img);
        int key = waitKey(1);
        
        if (key == 'p') {
            while (true) {
                key = waitKey(1);
                if (key == 'i') {
                    string fileName = string("Resources/cascade_classifier_training/negative/") + string(to_string(frameNumber)) + string(".jpg");
                    imwrite(fileName, img);
                    break;
                } else if (key == 'o') {
                    string fileName = string("Resources/cascade_classifier_training/positive/") + string(to_string(frameNumber)) + string(".jpg");
                    imwrite(fileName, img);
                    break;
                } else if (key == 'p') {
                    break;
                } else if (key == 'q') {
                    return 0;
                }
            }
        } else if (key == 'q') {
            break;
        }
        
        if (frameNumber > frameCount - 2) {
            break;
        }
        
    }
    
    return 0;
    
}

//
//  ex_03_04.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 3/3/21.
//

//############### Difference keying ###############
/*Implement a difference keying algorithm (see Section 3.1.3) (Toyama, Krumm, Brumitt et al. 1999), consisting of the following steps:
 1. Compute the mean and variance (or median and robust variance) at each pixel in an “empty” video sequence.
 2. For each new frame, classify each pixel as foreground or background (set the background pixels to RGBA=0).
 3. (Optional) Compute the alpha channel and composite over a new background.
 4. (Optional) Clean up the image using morphology (Section 3.3.1), label the connected components (Section 3.3.4), compute their centroids, and track them from frame to frame. Use this to build a “people counter”.*/

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <math.h>
#include <iostream>
#include <deque>

using namespace cv;
using namespace std;



Mat getMean(const deque<Mat>& images)
{
    if (images.empty()) return Mat();

    // Create a 0 initialized image to use as accumulator
    Mat m(images[0].rows, images[0].cols, CV_64FC3);
    m.setTo(Scalar(0,0,0,0));

    // Use a temp image to hold the conversion of each input image to CV_64FC3
    // This will be allocated just the first time, since all your images have
    // the same size.
    Mat temp;
    for (int i = 0; i < images.size(); ++i)
    {
        // Convert the input images to CV_64FC3 ...
        images[i].convertTo(temp, CV_64FC3);

        // ... so you can accumulate
        m += temp;
    }

    // Convert back to CV_8UC3 type, applying the division to get the actual mean
    m.convertTo(m, CV_8U, 1. / images.size());
    return m;
}


    
int main() {
    string path = "Resources/traffic.mp4";
    VideoCapture cap(path);
    
    Mat frame, foregroundBlur, foregroundErode, foregroundDil, preprocessingLast;
    deque<Mat> oldFrames;
    vector<Mat> preprocessing;
    
    cap.read(frame);
    Mat meanFrame = frame.clone();
    Mat foreground = Mat(frame.rows, frame.cols, frame.type());
    unsigned char variance = 15;
    
    
    while (true) {
        foreground = frame.clone();
        
        // iterate through each pixel in the frame to mark as background or foreground
        for (int r=0; r<frame.rows; r++) {
            for (int c=0; c<frame.cols; c++) {
                if (abs(static_cast<int>(frame.at<Vec3b>(Point(c,r))[0]) - static_cast<int>(meanFrame.at<Vec3b>(Point(c,r))[0])) < variance || abs(static_cast<int>(frame.at<Vec3b>(Point(c,r))[1]) - static_cast<int>(meanFrame.at<Vec3b>(Point(c,r))[1])) < variance || abs(static_cast<int>(frame.at<Vec3b>(Point(c,r))[2]) - static_cast<int>(meanFrame.at<Vec3b>(Point(c,r))[2])) < variance) {
                    foreground.at<Vec3b>(Point(c,r))[0] = 0;
                    foreground.at<Vec3b>(Point(c,r))[1] = 0;
                    foreground.at<Vec3b>(Point(c,r))[2] = 0;
                    foreground.at<Vec3b>(Point(c,r))[3] = 0;
                }
            }
        }
        
        // preprocessing
        preprocessing.clear();
        cvtColor(foreground, preprocessingLast, COLOR_BGR2GRAY); preprocessing.push_back(preprocessingLast);
        dilate(preprocessing.back(), preprocessingLast, getStructuringElement(MORPH_RECT, Size(5,5))); preprocessing.push_back(preprocessingLast);
        erode(preprocessing.back(), preprocessingLast, getStructuringElement(MORPH_RECT, Size(5,5))); preprocessing.push_back(preprocessingLast);
        medianBlur(preprocessing.back(), preprocessingLast, 3); preprocessing.push_back(preprocessingLast);
        
        // show the new frame and the preprocessed frame
        imshow("video",frame);
        imshow("foreground",preprocessing.back());
        if (waitKey(1) == 27){break;}
        
        // make the mean frame a rolling average
        oldFrames.push_front(frame);
        if (oldFrames.size() > 10) {oldFrames.pop_back();}
        meanFrame = getMean(oldFrames);
        
        // read in the new frame
        cap.read(frame);
    }
    
    return 0;
}

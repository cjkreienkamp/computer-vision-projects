//
//  ex_02_08.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 2/26/21.
//

//############### Skin Color Detection ###############
/*Devise a simple skin color detector (Forsyth and Fleck 1999; Jones and Rehg 2001; Vezhnevets, Sazonov, and Andreeva 2003; Kakumanu, Makrogiannis, and Bourbakis 2007) based on chromaticity or other color properties.
 1. Take a variety of photographs of people and calculate the xy chromaticity values for each pixel.
 2. Crop the photos or otherwise indicate with a painting tool which pixels are likely to be skin (e.g. face and arms).
 3. Calculate a color (chromaticity) distribution for these pixels. You can use something as simple as a mean and covariance measure or as complicated as a mean-shift segmentation algorithm (see Section 5.3.2). You can optionally use non-skin pixels to model the background distribution.
 4. Use your computed distribution to find the skin regions in an image. One easy way to visualize this is to paint all non-skin pixels a given color, such as white or black.
 5. How sensitive is your algorithm to color balance (scene lighting)?
 6. Does a simpler chromaticity measurement, such as a color ratio (2.116), work just as well?
 
 --> Instead of the above prompt, this program offers a variety of different ways to identify skin (these are not the only functions present)
        1) JonesRehg2002
        2) Peer2003
        3) BGR trackbar
        4) HSV trackbar
        5) XYZ trackbar
 The trackbar class offers a reusable class to test out upper and lower bounds in different color spaces.
 Further work needs to be done to figure out how to include the callback function for the trackbar inside the trackbar class.*/

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;



Mat JonesRehg2002(Mat img) {
    // Uses the Gaussian Mixture Model skin detector from "Statistical Color Models with Application to Skin Detection" from [Jones and Rehg 2002].
    // Advantages: High possibility for accuracy. Theta can be optimized to find accurate results, but it has not been tuned.
    // Disadvantages: Too slow for a video.
    
    double SKIN_mean_data[16][3] = {{73.53,29.94,17.76}, {249.71,233.94,217.49}, {161.68,116.25,96.95}, {186.07,136.62,114.40}, {189.26,98.37,51.18}, {247.00,152.20,90.84}, {150.10,72.66,37.76}, {206.85,171.09,156.34}, {212.78,152.82,120.04}, {234.87,175.43,138.94}, {151.19,97.74,74.59}, {120.52,77.55,59.82}, {192.20,119.62,82.32}, {214.29,136.08,87.24}, {99.57,54.33,38.06}, {238.88,203.08,176.91}};
    double SKIN_covariance_data[16][3] = {{765.40,121.44,112.80}, {39.94,154.44,396.05}, {291.03,60.48,162.85}, {274.95,64.60,198.27}, {633.18,222.40,250.69}, {65.23,691.53,609.92}, {408.63,200.77,257.57}, {530.08,155.08,572.79}, {160.57,84.52,243.90}, {163.80,121.57,279.22}, {425.40,73.56,175.11}, {330.45,70.34,151.82}, {152.76,92.14,259.15}, {204.90,140.17,270.19}, {448.13,90.18,151.29}, {178.38,156.27,404.99}};
    double SKIN_weight_data[16] = {0.0294, 0.0331, 0.0654, 0.0756, 0.0554, 0.0314, 0.0454, 0.0469, 0.0956, 0.0763, 0.110, 0.0676, 0.0755, 0.0500, 0.0667, 0.0749};
    double NONSKIN_mean_data[16][3] = {{254.37,254.41,253.82}, {9.39,8.09,8.52}, {96.57,96.95,91.53}, {160.44,162.49,159.06}, {74.98,63.23,46.33}, {121.83,60.88,18.31}, {202.18,154.88,91.04}, {193.06,201.93,206.55}, {51.88,57.14,61.55}, {30.88,26.84,25.32}, {44.97,85.96,131.95}, {236.02,236.27,230.70}, {207.86,191.20,164.12}, {99.83,148.11,188.17}, {135.06,131.92,123.10}, {135.96,103.89,66.88}};
    double NONSKIN_covariance_data[16][3] = {{2.77,2.81,5.46}, {46.84,33.59,32.48}, {280.69,156.79,436.58}, {355.98,115.89,591.24}, {414.84,245.95,361.27}, {2502.24,1383.53,237.18}, {957.42,1766.94,1582.52}, {562.88,190.23,447.28}, {344.11,191.77,433.40}, {222.07,118.65,182.41}, {651.32,840.52,963.67}, {225.03,117.29,331.95}, {494.04,237.69,533.52}, {955.88,654.95,916.70}, {350.35,130.30,388.43}, {806.44,642.20,350.36}};
    double NONSKIN_weight_data[16] = {0.0637, 0.0516, 0.0864, 0.0636, 0.0747, 0.0365, 0.0349, 0.0649, 0.0656, 0.1189, 0.0362, 0.0849, 0.0368, 0.0389, 0.0943, 0.0477};
        
    Mat mask = Mat(img.rows,img.cols, CV_8U, Scalar(0,0,0));
    double theta = 0;
    
    // Gaussian Mixture Model implementation
    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            double SKIN_probability = 0;
            double NONSKIN_probability = 0;
            unsigned char R = static_cast<int>(img.at<Vec3b>(Point(x,y))[2]);
            unsigned char G = static_cast<int>(img.at<Vec3b>(Point(x,y))[1]);
            unsigned char B = static_cast<int>(img.at<Vec3b>(Point(x,y))[0]);
    
            for (int i=0; i<16; i++) {
                double SKIN_RGBminusMEAN_array[3][1] = {{R-SKIN_mean_data[i][0]},{G-SKIN_mean_data[i][1]},{B-SKIN_mean_data[i][2]}};
                double NONSKIN_RGBminusMEAN_array[3][1] = {{R-NONSKIN_mean_data[i][0]},{G-NONSKIN_mean_data[i][1]},{B-NONSKIN_mean_data[i][2]}};
                Mat SKIN_RGBminusMEAN = Mat(3, 1, CV_64F, SKIN_RGBminusMEAN_array);
                Mat NONSKIN_RGBminusMEAN = Mat(3, 1, CV_64F, NONSKIN_RGBminusMEAN_array);
            
                double SKIN_covariance_array[3][3] = {{SKIN_covariance_data[i][0],0,0},{0,SKIN_covariance_data[i][1],0},{0,0,SKIN_covariance_data[i][2]}};
                double NONSKIN_covariance_array[3][3] = {{NONSKIN_covariance_data[i][0],0,0},{0,NONSKIN_covariance_data[i][1],0},{0,0,NONSKIN_covariance_data[i][2]}};
                Mat SKIN_covariance = Mat(3, 3, CV_64F, SKIN_covariance_array);
                Mat NONSKIN_covariance = Mat(3, 3, CV_64F, NONSKIN_covariance_array);
        
                double SKIN_denominator = pow((2*M_PI),3.0/2.0)*pow(determinant(SKIN_covariance),1.0/2.0);
                double NONSKIN_denominator = pow((2*M_PI),3.0/2.0)*pow(determinant(NONSKIN_covariance),1.0/2.0);
                Mat SKIN_exponent = -0.5 * SKIN_RGBminusMEAN.t() * SKIN_covariance.inv() * SKIN_RGBminusMEAN;
                Mat NONSKIN_exponent = -0.5 * NONSKIN_RGBminusMEAN.t() * NONSKIN_covariance.inv() * NONSKIN_RGBminusMEAN;
                double SKIN_numerator = exp(SKIN_exponent.at<double>(0,0));
                double NONSKIN_numerator = exp(NONSKIN_exponent.at<double>(0,0));
        
                SKIN_probability += SKIN_weight_data[i] * SKIN_numerator/SKIN_denominator;
                NONSKIN_probability += NONSKIN_weight_data[i] * NONSKIN_numerator/NONSKIN_denominator;
                theta = SKIN_probability/NONSKIN_probability;
            }
            int percent = y*100/img.rows;
            cout<<to_string(percent)<<"%"<<endl;
            if (theta>1) {
                circle(mask, Point(x,y), 1, Scalar(255,255,255));
            }
        }
    }
    return mask;
}



Mat Peer2003(Mat imgBGR) {
    // Uses the explicitly defined skin region model for RGB colorspace in "Human Skin Colour Clustering for Face Detection from [Peer et al. 2003].
    
    Mat mask = Mat(imgBGR.rows,imgBGR.cols, CV_8U, Scalar(0,0,0));
    
    for (int y = 0; y < imgBGR.rows; y++) {
        for (int x = 0; x < imgBGR.cols; x++) {
            
            int R = static_cast<int>(imgBGR.at<Vec3b>(Point(x,y))[2]);
            int G = static_cast<int>(imgBGR.at<Vec3b>(Point(x,y))[1]);
            int B = static_cast<int>(imgBGR.at<Vec3b>(Point(x,y))[0]);
            
            if (R>95 && G>40 && B>20 && R-G>15 && R>B) {
                circle(mask, Point(x,y), 1, Scalar(255,255,255),FILLED);
            }
            int percent = y*100/imgBGR.rows;
            cout<<to_string(percent)<<"%"<<endl;
        }
    }
    return mask;
}


// Trackbar
// Skin: X(63,249), Y(61,248), Z(51,226)
// Skin: B(33,211), G(76,252), R(114,255)
// Skin: H(3,24), S(51,242), V(50,255)
class trackbar {
public:
    Mat mask, window;
    string windowName;
    int height, length, leftTrackPos, rightTrackPos;
    vector<string> sliderName;
    vector<int> minPosition, maxPosition, minValue, maxValue, minValueLimit, maxValueLimit;
    vector<bool> clickingMin, clickingMax;
    Scalar lowerBound, upperBound;
    
    // Constructor
    trackbar(string windowName, vector<string> sliderName={"B","G","R"}, vector<int> maxValueLimit={255,255,255}) : windowName(windowName), sliderName(sliderName), maxValueLimit(maxValueLimit) {
        namedWindow(windowName);
        setMouseCallback(windowName, &trackbar::TrackCallBackFunc, this);
        height = 350;
        length = 500;
        window.create(height, length, CV_8UC3);
        leftTrackPos = 0.25*length;
        rightTrackPos = 0.8*length;
        minPosition = {leftTrackPos, leftTrackPos, leftTrackPos};
        maxPosition = {rightTrackPos, rightTrackPos, rightTrackPos};
        minValueLimit = {0,0,0};
        minValue = {0,0,0};
        maxValue = {255,255,255};
        clickingMin = {false, false, false};
        clickingMax = {false, false, false};
        drawTrackbar();
    }
    
    // Function which creates an interactive trackbar
    void drawTrackbar() {
        window.setTo(Scalar(255,255,255)); // create a blank canvas
        
        for (int i=0; i<sliderName.size(); i++) {
            minPosition[i] = minPosition[i] < leftTrackPos ? leftTrackPos : minPosition[i];
            maxPosition[i] = maxPosition[i] > rightTrackPos ? rightTrackPos : maxPosition[i];
            minValue[i] = maxValueLimit[i]*(minPosition[i] - leftTrackPos)/(rightTrackPos-leftTrackPos);
            maxValue[i] = maxValueLimit[i]*(maxPosition[i] - leftTrackPos)/(rightTrackPos-leftTrackPos);
        }
        
        for (int i=0; i<sliderName.size(); i++)         // create lines and text for trackbar
        {
            int trackHeight = height*i/sliderName.size() + height*0.1;
            putText(window, sliderName[i], Point(0.05*length,trackHeight), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,0,0), 2);
            putText(window, to_string(minValue[i]), Point(length*0.15,trackHeight), FONT_HERSHEY_PLAIN, 1.5, Scalar(255,0,0), 2);
            putText(window, to_string(maxValue[i]), Point(length*0.85,trackHeight), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,0,255), 2);
            line(window, Point(leftTrackPos,trackHeight), Point(rightTrackPos,trackHeight), Scalar(0,0,0), 2);
            if (minPosition[i] < maxPosition[i]) {line(window, Point(minPosition[i],trackHeight), Point(maxPosition[i],trackHeight), Scalar(0,0,0), 4);}
            circle(window, Point(minPosition[i],trackHeight), 8, Scalar(255,0,0), FILLED);
            circle(window, Point(maxPosition[i],trackHeight), 8, Scalar(0,0,255), FILLED);
        }
        
        lowerBound = Scalar(minValue[0], minValue[1], minValue[2]);
        upperBound = Scalar(maxValue[0], maxValue[1], maxValue[2]);
    }
    
    // Trackbar callback function
    static void TrackCallBackFunc(int event, int x, int y, int flags, void* userdata) {
        
        trackbar *track = (trackbar*) userdata;
        
        if  ( event == EVENT_LBUTTONDOWN ) {
            for (int i=0; i<track->sliderName.size(); i++) {
                int trackHeight = track->height*i/track->sliderName.size() + track->height*0.1;
                if (abs(y-trackHeight) < 15 && abs(x-track->minPosition[i]) < 10) {
                    track->minPosition[i] = x;
                    track->clickingMin[i] = true;
                }
                else if (abs(y-trackHeight) < 15 && abs(x-track->maxPosition[i]) < 10) {
                    track->maxPosition[i] = x;
                    track->clickingMax[i] = true;
                }
            }
            track->drawTrackbar();
         }
        
        else if ( event == EVENT_MOUSEMOVE) {
            for (int i=0; i<track->sliderName.size(); i++) {
                if (track->clickingMin[i]) {track->minPosition[i] = x; break;}
                else if (track->clickingMax[i]) {track->maxPosition[i] = x; break;}
            }
            track->drawTrackbar();
        }
        
        else if  ( event == EVENT_LBUTTONUP ) {
            for (int i=0; i<track->sliderName.size(); i++) {
                track->clickingMin[i] = false;
                track->clickingMax[i] = false;
            }
            track->drawTrackbar();
        }
    }
};


int main() {
    
    string path = "Resources/diversity.jpg";
    Mat img = imread(path);
   
    // Non-trackbar process
    //Mat mask = JonesRehg2002(img);                      // JonesRehg2002 Gaussian mixture model
    //Mat mask = Peer2003(img);                           // Peer2003 explicitly defined skin region model
    //imshow("image",img);
    //imshow("mask",mask);
     
    // Trackbar process
    trackbar track1("trackbar 1",{"B","G","R"},{255,255,255});
        // {"B","G","R"},{255,255,255}
        // {"X","Y","Z"},{255,255,255}
        // {"H","S","V"},{180,255,255}
    
    Mat imgColorspace, mask;
    img.copyTo(imgColorspace);                          //if using trackbar with BGR
    //cvtColor(img, imgColorspace, COLOR_BGR2HSV);      //if using trackbar with HSV
    //cvtColor(img, imgColorspace, COLOR_BGR2XYZ);      //if using trackbar with XYZ
    
    while (true)
    {
        inRange(imgColorspace,track1.lowerBound,track1.upperBound,mask);
        imshow(track1.windowName, track1.window);
        imshow("image",img);
        imshow("image mask",mask);
        
        int key=waitKey(20);
        if (key==27) {break;}
    }
    
    return 0;
}
*/

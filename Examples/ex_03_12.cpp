//
//  ex_03_12.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 3/4/21.
//

//############### Steerable filters ###############
/*Implement Freeman and Adelson’s (1991) steerable filter algorithm. The input should be a grayscale or color image and the output should be a multi-banded image consisting of G^0◦ and G^90◦ . The coefficients for the filters can be found in the paper by Freeman and Adelson (1991).
Test the various order filters on a number of images of your choice and see if you can reliably find corner and intersection features. These filters will be quite useful later to detect elongated structures, such as lines (Section 4.3).
 --> I didn't do any of this because the paper is provide insufficient instruction. I implemented a similar concept by means of a different algorithm.
 This could be improved by:
    1) using vectors/arrays to store data
    2) varying the 3-pixel wide area of interest to a larger area of interest
    3) draw lines centered on the pixel of interest, except whose length is to the degree that the pixel is in that direction
    4) increase number of possible directions
 */

/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <math.h>
#include <iostream>
#include <deque>

using namespace cv;
using namespace std;

int main() {
    
// ANALYZE THE DIRECTION AT EVERY 3 PIXELS
    
    // import image and perform necessary color space operations
    string path = "Resources/einstein.jpg";
    Mat img = imread(path);
    Mat mask = Mat(img.rows,img.cols,img.type(),Scalar(255,255,255));
    
    // create a for loop that gets the coordinates (col,row) of every 3rd pixel
    for (int r = 1; r < img.rows; r += 2) {
        for (int c = 1; c < img.cols; c += 2) {
            
    // compare the colors of a 3-pixel-wide vertical line, horizontal line, downward diagonal, and upward diagonal through the pixel of interest
            int pix1_0 = static_cast<int>(img.at<Vec3b>(Point(c-1,r-1))[0]);
            int pix1_1 = static_cast<int>(img.at<Vec3b>(Point(c-1,r-1))[1]);
            int pix1_2 = static_cast<int>(img.at<Vec3b>(Point(c-1,r-1))[2]);
            int pix2_0 = static_cast<int>(img.at<Vec3b>(Point(c,r-1))[0]);
            int pix2_1 = static_cast<int>(img.at<Vec3b>(Point(c,r-1))[1]);
            int pix2_2 = static_cast<int>(img.at<Vec3b>(Point(c,r-1))[2]);
            int pix3_0 = static_cast<int>(img.at<Vec3b>(Point(c+1,r-1))[0]);
            int pix3_1 = static_cast<int>(img.at<Vec3b>(Point(c+1,r-1))[1]);
            int pix3_2 = static_cast<int>(img.at<Vec3b>(Point(c+1,r-1))[2]);
            int pix4_0 = static_cast<int>(img.at<Vec3b>(Point(c-1,r))[0]);
            int pix4_1 = static_cast<int>(img.at<Vec3b>(Point(c-1,r))[1]);
            int pix4_2 = static_cast<int>(img.at<Vec3b>(Point(c-1,r))[2]);
            int pix5_0 = static_cast<int>(img.at<Vec3b>(Point(c,r))[0]);
            int pix5_1 = static_cast<int>(img.at<Vec3b>(Point(c,r))[1]);
            int pix5_2 = static_cast<int>(img.at<Vec3b>(Point(c,r))[2]);
            int pix6_0 = static_cast<int>(img.at<Vec3b>(Point(c+1,r))[0]);
            int pix6_1 = static_cast<int>(img.at<Vec3b>(Point(c+1,r))[1]);
            int pix6_2 = static_cast<int>(img.at<Vec3b>(Point(c+1,r))[2]);
            int pix7_0 = static_cast<int>(img.at<Vec3b>(Point(c-1,r+1))[0]);
            int pix7_1 = static_cast<int>(img.at<Vec3b>(Point(c-1,r+1))[1]);
            int pix7_2 = static_cast<int>(img.at<Vec3b>(Point(c-1,r+1))[2]);
            int pix8_0 = static_cast<int>(img.at<Vec3b>(Point(c,r+1))[0]);
            int pix8_1 = static_cast<int>(img.at<Vec3b>(Point(c,r+1))[1]);
            int pix8_2 = static_cast<int>(img.at<Vec3b>(Point(c,r+1))[2]);
            int pix9_0 = static_cast<int>(img.at<Vec3b>(Point(c+1,r+1))[0]);
            int pix9_1 = static_cast<int>(img.at<Vec3b>(Point(c+1,r+1))[1]);
            int pix9_2 = static_cast<int>(img.at<Vec3b>(Point(c+1,r+1))[2]);
            
            // vertical line
            float vertmean0 = (pix2_0 + pix5_0 + pix8_0)/3;
            float vertmean1 = (pix2_1 + pix5_1 + pix8_1)/3;
            float vertmean2 = (pix2_2 + pix5_2 + pix8_2)/3;
            float vertvariance0 = (pow((pix2_0-vertmean0),2) + pow((pix5_0-vertmean0),2) + pow((pix8_0-vertmean0),2))/2;
            float vertvariance1 = (pow((pix2_1-vertmean1),2) + pow((pix5_1-vertmean1),2) + pow((pix8_1-vertmean1),2))/2;
            float vertvariance2 = (pow((pix2_2-vertmean2),2) + pow((pix5_2-vertmean2),2) + pow((pix8_2-vertmean2),2))/2;
            float vertvariance = vertvariance0*vertvariance1*vertvariance2;
            
            // horizontal line
            float horzmean0 = (pix4_0 + pix5_0 + pix6_0)/3;
            float horzmean1 = (pix4_1 + pix5_1 + pix6_1)/3;
            float horzmean2 = (pix4_2 + pix5_2 + pix6_2)/3;
            float horzvariance0 = (pow((pix4_0-horzmean0),2) + pow((pix5_0-horzmean0),2) + pow((pix6_0-horzmean0),2))/2;
            float horzvariance1 = (pow((pix4_1-horzmean1),2) + pow((pix5_1-horzmean1),2) + pow((pix6_1-horzmean1),2))/2;
            float horzvariance2 = (pow((pix4_2-horzmean2),2) + pow((pix5_2-horzmean2),2) + pow((pix6_2-horzmean2),2))/2;
            float horzvariance = horzvariance0*horzvariance1*horzvariance2;
            
            // downward diagonal line
            float dndgmean0 = (pix1_0 + pix5_0 + pix9_0)/3;
            float dndgmean1 = (pix1_1 + pix5_1 + pix9_1)/3;
            float dndgmean2 = (pix1_2 + pix5_2 + pix9_2)/3;
            float dndgvariance0 = (pow((pix1_0-dndgmean0),2) + pow((pix5_0-dndgmean0),2) + pow((pix9_0-dndgmean0),2))/2;
            float dndgvariance1 = (pow((pix1_1-dndgmean1),2) + pow((pix5_1-dndgmean1),2) + pow((pix9_1-dndgmean1),2))/2;
            float dndgvariance2 = (pow((pix1_2-dndgmean2),2) + pow((pix5_2-dndgmean2),2) + pow((pix9_2-dndgmean2),2))/2;
            float dndgvariance = dndgvariance0*dndgvariance1*dndgvariance2;
            
            // upward diagonal line
            float updgmean0 = (pix3_0 + pix5_0 + pix7_0)/3;
            float updgmean1 = (pix3_1 + pix5_1 + pix7_1)/3;
            float updgmean2 = (pix3_2 + pix5_2 + pix7_2)/3;
            float updgvariance0 = (pow((pix3_0-updgmean0),2) + pow((pix5_0-updgmean0),2) + pow((pix7_0-updgmean0),2))/2;
            float updgvariance1 = (pow((pix3_1-updgmean1),2) + pow((pix5_1-updgmean1),2) + pow((pix7_1-updgmean1),2))/2;
            float updgvariance2 = (pow((pix3_2-updgmean2),2) + pow((pix5_2-updgmean2),2) + pow((pix7_2-updgmean2),2))/2;
            float updgvariance = updgvariance0*updgvariance1*updgvariance2;
            
// DRAW A LINE WHOSE LENGTH IS TO THE DEGREE THAT THE PIXEL IS IN THAT DIRECTION
                
    // whichever has the highest correlation, determine to what degree it has the best correlation
            if (vertvariance < horzvariance && vertvariance < dndgvariance && vertvariance < updgvariance) {
                line(mask, Point(c,r-1), Point(c,r+1), Scalar(0,0,0));
            } else if (horzvariance < vertvariance && horzvariance < dndgvariance && horzvariance < updgvariance) {
                line(mask, Point(c-1,r), Point(c+1,r), Scalar(0,0,0));
            } else if (dndgvariance < vertvariance && dndgvariance < horzvariance && dndgvariance < updgvariance) {
                line(mask, Point(c-1,r-1), Point(c+1,r+1), Scalar(0,0,0));
            } else if (updgvariance < vertvariance && updgvariance < horzvariance && updgvariance < dndgvariance) {
                line(mask, Point(c-1,r+1), Point(c+1,r-1), Scalar(0,0,0));
            } else {
                circle(mask, Point(c,r), 0.1, Scalar(0,0,0));
            }
        }
    }
    
// SHOW THE IMAGE AND THE NEW IMAGE
    
    // imshow the original image and the new image labeled as mask
    imshow("img", img);
    imshow("mask",mask);

    // keep the images open until the ESC key is pressed
    if (waitKey() == 27) {return 0;}
}
*/

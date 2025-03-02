//
//  ex_03_14.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 3/4/21.
//

//############### Connected components ###############
/*Implement one of the connected component algorithms from Section 3.3.4 or Section 2.3 from Haralick and Shapiro’s book (1992) and discuss its computational complexity.
 1. Threshold or quantize an image to obtain a variety of input labels and then compute the area statistics for the regions that you find.
 2. Use the connected components that you have found to track or match regions in different images or video frames.
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
    
// SPLIT THE IMAGE INTO HORIZONTAL RUNS OF ADJACENT PIXELS, COLORING THE RUNS WITH UNIQUE LABELS, RE-USING THE LABELS OF VERTICALLY ADJACENT RUNS WHEN POSSIBLE
    
    // read in the image and convert to grayscale
    string path = "Resources/mario.png";
    Mat img = imread(path);
    Mat step1 = Mat(img.rows,img.cols,CV_8UC3,Scalar(255,255,255));
    
    // iterate through the rows and color similar pixels with unique labels
    Vec3b pixelColor;
    Vec3b regionColor;
    regionColor[0] = rand() % 255 + 1;
    regionColor[1] = rand() % 255 + 1;
    regionColor[2] = rand() % 255 + 1;
    Vec3b lastPixelColor = static_cast<int>(img.at<int>(Point(0,0)));
    vector<vector<Point>> connectedComponents;
    vector<vector<Point>> components;
    vector<Point> component;
    for (int r=0; r<img.rows; r++) {
        for (int c=0; c<img.cols; c++) {
            pixelColor = img.at<Vec3b>(Point(c,r));
            if (abs(pixelColor[0]-lastPixelColor[0]) > 10 || abs(pixelColor[1]-lastPixelColor[1]) > 10 || abs(pixelColor[2]-lastPixelColor[2]) > 10) {
                regionColor[0] = rand() % 256;
                regionColor[1] = rand() % 256;
                regionColor[2] = rand() % 256;
                components.push_back(component);
                component.clear();
            }
            step1.at<Vec3b>(Point(c,r)) = regionColor;
            component.push_back(Point(c,r));
            lastPixelColor = pixelColor;
        }
        regionColor[0] = rand() % 256;
        regionColor[1] = rand() % 256;
        regionColor[2] = rand() % 256;
        components.push_back(component);
        component.clear();
        lastPixelColor = img.at<Vec3b>(Point(0,r+1));
    }
    
// MERGE ADJACENT RUNS OF DIFFERENT COLORS
    
    // recursively loop through a vector of components to compare just the values of the first pixels of each component, if they are the same then make them the same color...keep going until there are no vectors that have the same first pixel
    Mat step2 = Mat(img.rows,img.cols,CV_8UC3,Scalar(255,255,255));
    for (int c=0; c<img.cols; c++) {
        for (int r=0; r<img.rows-1; r++) {
            Vec3b imgNow = img.at<Vec3b>(Point(c,r));
            Vec3b imgNext = img.at<Vec3b>(Point(c,r+1));
            Vec3b step1Now = step1.at<Vec3b>(Point(c,r));
            Vec3b step1Next = step1.at<Vec3b>(Point(c,r+1));
            Vec3b step2Now = step2.at<Vec3b>(Point(c,r));
            Vec3b step2Next = step2.at<Vec3b>(Point(c,r+1));
            
            // if there is a similarity between two colors 1 row apart in the same column
            if (abs(imgNow[0]-imgNext[0]) < 10 && abs(imgNow[1]-imgNext[1]) < 10 && abs(imgNow[2]-imgNext[2]) < 10) {
                
                // if neither row in step2 has already been assigned a color for this similarity
                if (step2Next[0] == 255 && step2Next[1] == 255 && step2Next[2] == 255 && step2Now[0] == 255 && step2Now[1] == 255 && step2Now[2] == 255) {
                    step2.at<Vec3b>(Point(c,r)) = step1Now;
                    step2.at<Vec3b>(Point(c,r+1)) = step1Now;
                }
                
                // if both rows have been assigned then continue
                else if ((step2Next[0] != 255 || step2Next[1] != 255 || step2Next[2] != 255) && (step2Now[0] != 255 || step2Now[1] != 255 || step2Now[2] != 255)) {
                    
                    // ?? try some recursion because this just isn't working and is taking too long
                    
                    // need to go through the column again to reassign all values
                    for (int i=r; i>0; i--) {
                        if (img.at<Vec3b>(Point(c,r)) != img.at<Vec3b>(Point(c,r-1))) {break;}
                        else {
                            step2.at<Vec3b>(Point(c,r-1)) = step2.at<Vec3b>(Point(c,r));
                            for (int j=0; j<components.size(); j++) {
                                if (Point(c,r-1) == components[j][0]) {
                                    for (int k=0; k<components[j].size(); k++) {
                                        step2.at<Vec3b>(components[j][k]) = step2.at<Vec3b>(Point(c,r-1));
                                    }
                                }
                            }
                        }
                    }
                }
                
                // if the current row has already been assigned a color
                else if (step2Now[0] != 255 || step2Now[1] != 255 || step2Now[2] != 255){
                    step2.at<Vec3b>(Point(c,r+1)) = step2Now;
                }
                
                // if the next row in step2 has already been assigned
                else if (step2Next[0] != 255 || step2Next[1] != 255 || step2Next[2] != 255) {
                    step2.at<Vec3b>(Point(c,r)) = step2Next;
                }
                
                // if there is not a similarity
            } else {
                
                // if neither row in step2 has already been assigned
                if (step2Next[0] == 255 && step2Next[1] == 255 && step2Next[2] == 255 && step2Now[0] == 255 && step2Now[1] == 255 && step2Now[2] == 255) {
                    step2.at<Vec3b>(Point(c,r)) = step1Now;
                    step2.at<Vec3b>(Point(c,r+1)) = step1Now;
                }
                
                // if both rows have been assigned then continue
                else if ((step2Next[0] != 255 || step2Next[1] != 255 || step2Next[2] != 255) && (step2Now[0] != 255 || step2Now[1] != 255 || step2Now[2] != 255)) {}
                
                // if the current row has already been assigned a color but the next one has not
                else if (step2Now[0] != 255 || step2Now[1] != 255 || step2Now[2] != 255){
                    step2.at<Vec3b>(Point(c,r+1)) = step1Next;
                }
                
                // if the next row in step2 has already been assigned but the current one has not
                else if (step2Next[0] != 255 || step2Next[1] != 255 || step2Next[2] != 255) {
                    step2.at<Vec3b>(Point(c,r)) = step1Now;
                }
                
                
                
            }
            
            // color in the rest of the row that needs a color from step 1
            step2Now = step2.at<Vec3b>(Point(c,r));
            for (int i=0; i<components.size(); i++) {
                if (Point(c,r) == components[i][0]) {
                    for (int j=0; j<components[i].size(); j++) {
                        step2.at<Vec3b>(components[i][j]) = step2Now;
                    }
                }
            }
        }
        
        imshow("image",img);
        imshow("step2",step2);
        waitKey(20);
        cout<<to_string(c*100/img.cols)<<"%"<<endl;
        
    }
    
    // show the image until the ESC key is pressed
    imshow("image",img);
    //imshow("step1",step1);
    imshow("step2",step2);
    if (waitKey() == 27) {return (0);}
}
*/

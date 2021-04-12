//
//  Chapter8.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 1/9/21.
//

//############### Face Detection ###############
// Use an XML file to load an already-trained Haar cascade and then use it to find the faces.


/*#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>    //header file needed to work with Haar cascade files
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    string path = "Resources/test.png";
    Mat img = imread(path);
    
    CascadeClassifier faceCascade;      //load the cascade
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");
    
    if (faceCascade.empty()) {cout << "XML file not loaded" << endl;}
    
    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);  //can change the 1.1 and 10 values to fit your needs
    
    for (int i = 0; i < faces.size(); i++) {
        
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255,0,255), 3);
    }
    
    imshow("Image",img);
    waitKey(0);

    return 0;
}*/

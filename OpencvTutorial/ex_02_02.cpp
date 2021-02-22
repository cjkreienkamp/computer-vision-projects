//
//  ex_02_02.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 2/17/21.
//

//############### 2D Transform Editor ###############
/*Write a program that lets you interactively create a set of rectangles and then modify their “pose” (2D transform). You should implement the following steps:
1. Open an empty window (“canvas”).
2. Shift drag (rubber-band) to create a new rectangle.
3. Select the deformation mode (motion model): translation, rigid, similarity, affine, or perspective.
4. Drag any corner of the outline to change its transformation.
This exercise should be built on a set of pixel coordinate and transformation classes, either implemented by yourself or from a software library. Persistence of the created representation (save and load) should also be supported (for each rectangle, save its transformation).*/


#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Point2f startPoint;
int imgLength = 500;
int imgHeight = 500;
int buttonLength = 200;
Mat img(imgHeight,imgLength+buttonLength, CV_8UC3, Scalar(255,255,255));
bool imgDrawn = false;
bool clicking = false;
int buttonPressed = 5;
vector<string> deformation = {"translation", "rotation", "similarity", "affine", "perspective"};
string deformationType;
vector<vector<double>> newpts1, newpts2, newpts3, newpts4;
vector<vector<vector<double>>> newptvector;


vector<vector<double>> MxM(vector<vector<double>> A, vector<vector<double>> B) {
    vector<vector<double>> C;
    int sum;
    
    for (int i=0; i<A.size(); i++) {
        vector<double> c;
        for (int j=0; j<B[0].size(); j++) {
            sum = 0;
            for (int k=0; k<B.size(); k++) {
                sum += A[i][k]*B[k][j];
            }
            c.push_back(sum);
        }
        C.push_back(c);
    }
    return C;
}


void drawEmptyCanvasWithButtons() {
    img.setTo(Scalar(255,255,255));
    for (int i=0; i<5; i++)
    {
        putText(img, deformation[i], Point(imgLength+buttonLength*0.1,imgHeight*(i/5.0+0.1)), FONT_HERSHEY_PLAIN, 1.5, Scalar(0,0,255), 2);
        rectangle(img, Point(imgLength,imgHeight*i/5.0), Point(imgLength+buttonLength,imgHeight*(i/5.0+0.2)), Scalar(0,0,0), 2);
    }
    if (buttonPressed < 5) {
        putText(img, deformation[buttonPressed], Point(imgLength+buttonLength*0.1,imgHeight*(buttonPressed/5.0+0.1)), FONT_HERSHEY_PLAIN, 1.5, Scalar(255,0,0), 2);
    }
    if (imgDrawn) {
        line(img, Point(newpts1[0][0],newpts1[1][0]), Point(newpts2[0][0],newpts2[1][0]), Scalar(0,0,255), 3);
        line(img, Point(newpts2[0][0],newpts2[1][0]), Point(newpts3[0][0],newpts3[1][0]), Scalar(0,0,255), 3);
        line(img, Point(newpts3[0][0],newpts3[1][0]), Point(newpts4[0][0],newpts4[1][0]), Scalar(0,0,255), 3);
        line(img, Point(newpts4[0][0],newpts4[1][0]), Point(newpts1[0][0],newpts1[1][0]), Scalar(0,0,255), 3);
    }
}


class newRect {
public:
    Point2f startPoint;
    Point2f endPoint;
    Point2f pt1, pt2, pt3, pt4;
    vector<vector<double>> newpt1, newpt2, newpt3, newpt4;
    Point2f centroid;
    Point2f holderPoint;
    double holderAngle;
    
    void set_endPoint(Point tendPoint) {
        endPoint = tendPoint;
        pt1 = Point(startPoint.x, startPoint.y);
        pt2 = Point(endPoint.x, startPoint.y);
        pt3 = Point(endPoint.x, endPoint.y);
        pt4 = Point(startPoint.x, endPoint.y);
        centroid = Point((startPoint.x+endPoint.x)/2,(startPoint.y+endPoint.y)/2);
        newpt1 = {{pt1.x},{pt1.y},{1}};
        newpt2 = {{pt2.x},{pt2.y},{1}};
        newpt3 = {{pt3.x},{pt3.y},{1}};
        newpt4 = {{pt4.x},{pt4.y},{1}};
        newpts1 = newpt1; newpts2 = newpt2; newpts3 = newpt3; newpts4 = newpt4;
    }
    
    void set_ptsFromNewpts() {
        pt1.x = newpt1[0][0];
        pt1.y = newpt1[1][0];
        pt2.x = newpt2[0][0];
        pt2.y = newpt2[1][0];
        pt3.x = newpt3[0][0];
        pt3.y = newpt3[1][0];
        pt4.x = newpt4[0][0];
        pt4.y = newpt4[1][0];
    }
    
    void performTransformation(vector<vector<double>> transformationMatrix, bool pt1T = true, bool pt2T = true, bool pt3T = true, bool pt4T = true, bool display = true) {
        newpt1 = pt1T ? MxM(transformationMatrix, {{pt1.x},{pt1.y},{1}}) : newpt1;
        newpt2 = pt2T ? MxM(transformationMatrix, {{pt2.x},{pt2.y},{1}}) : newpt2;
        newpt3 = pt3T ? MxM(transformationMatrix, {{pt3.x},{pt3.y},{1}}) : newpt3;
        newpt4 = pt4T ? MxM(transformationMatrix, {{pt4.x},{pt4.y},{1}}) : newpt4;
        newpts1 = newpt1; newpts2 = newpt2; newpts3 = newpt3; newpts4 = newpt4;
        
        if (display) {
            drawEmptyCanvasWithButtons();
            line(img, Point(newpt1[0][0],newpt1[1][0]), Point(newpt2[0][0],newpt2[1][0]), Scalar(0,0,255), 3);
            line(img, Point(newpt2[0][0],newpt2[1][0]), Point(newpt3[0][0],newpt3[1][0]), Scalar(0,0,255), 3);
            line(img, Point(newpt3[0][0],newpt3[1][0]), Point(newpt4[0][0],newpt4[1][0]), Scalar(0,0,255), 3);
            line(img, Point(newpt4[0][0],newpt4[1][0]), Point(newpt1[0][0],newpt1[1][0]), Scalar(0,0,255), 3);
        }
    }
    
    void translation(Point p) {
        double x = p.x - holderPoint.x;
        double y = p.y - holderPoint.y;
        vector<vector<double>> T = {    {1, 0, x},
                                        {0, 1, y},
                                        {0, 0, 1}};
        performTransformation(T);
    }
    
    void rotation(Point p) {
        double theta = atan2(p.y-centroid.y, p.x-centroid.x) - holderAngle;
        vector<vector<double>> R = {    {cos(theta), -sin(theta), centroid.x},
                                        {sin(theta), cos(theta), centroid.y},
                                        {0, 0, 1}};
        pt1 -= centroid; pt2 -= centroid; pt3 -= centroid; pt4 -= centroid;
        performTransformation(R);
        pt1 += centroid; pt2 += centroid; pt3 += centroid; pt4 += centroid;
    }
    
    void similarity(Point p) {
        double dx = (p.x - holderPoint.x)*2/abs(pt1.x-pt3.x)+1;
        double scalex = dx; double scaley = dx;
        vector<vector<double>> S = {    {scalex, 0, -(scalex-1)*centroid.x},
                                        {0, scaley, -(scaley-1)*centroid.y},
                                        {0, 0, 1}};
        performTransformation(S);
    }
    
    void affine(Point p) {
        double theta = atan2(p.y-pt4.y, p.x-centroid.x) - holderAngle;
        vector<vector<double>> A1 = {    {cos(theta), -sin(theta), pt4.x},
                                        {sin(theta), cos(theta), pt4.y},
                                        {0, 0, 1}};
        vector<vector<double>> A2 = {    {cos(theta), -sin(theta), pt3.x},
                                        {sin(theta), cos(theta), pt3.y},
                                        {0, 0, 1}};
        pt1 -= pt4; pt2 -= pt3;
        performTransformation(A1, true, false, false, false, false);
        performTransformation(A2, false, true, false, false, true);
        pt1 += pt4; pt2 += pt3;
    }
    
    void perspective(Point p) {
        for (int i=0; i<4; i++) {
            if (abs(holderPoint.x-newptvector[i][0][0])<10 && abs(holderPoint.y-newptvector[i][1][0])<10) {
                if (i == 0) {newpt1 = {{static_cast<double>(p.x)},{static_cast<double>(p.y)},{1}};}
                else if (i == 1) {newpt2 = {{static_cast<double>(p.x)},{static_cast<double>(p.y)},{1}};}
                else if (i == 2) {newpt3 = {{static_cast<double>(p.x)},{static_cast<double>(p.y)},{1}};}
                else {newpt4 = {{static_cast<double>(p.x)},{static_cast<double>(p.y)},{1}};}
            }
        }
        performTransformation(newpt1,false,false,false,false,true);
    }
};

newRect rect1;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    if  ( event == EVENT_LBUTTONDOWN )
     {
         if  (x > imgLength && imgDrawn) {
             if (y<0.2*imgHeight) {buttonPressed = 0;}
             else if (y<0.4*imgHeight) {buttonPressed = 1;}
             else if (y<0.6*imgHeight) {buttonPressed = 2;}
             else if (y<0.8*imgHeight) {buttonPressed = 3;}
             else {buttonPressed = 4;}
             deformationType = deformation[buttonPressed];
             drawEmptyCanvasWithButtons();
         } else if (deformationType == "translation") {rect1.holderPoint = Point(x,y);}
         else if (deformationType == "rotation") {rect1.holderAngle = atan2(y-rect1.centroid.y, x-rect1.centroid.x);}
         else if (deformationType == "similarity") {rect1.holderPoint = Point(x,y);}
         else if (deformationType == "affine") {rect1.holderAngle = atan2(y-rect1.pt4.y, x-rect1.centroid.x);}
         else if (deformationType == "perspective") {
             rect1.holderPoint = Point(x,y);
             newptvector = {rect1.newpt1,rect1.newpt2,rect1.newpt3,rect1.newpt4};
         }
         else {
             drawEmptyCanvasWithButtons();
             rect1.startPoint = Point(x,y);
         }
         clicking = true;
     }
     else if  ( event == EVENT_LBUTTONUP )
     {
         if  (x > imgLength) {}
         else if (deformationType == "translation") {
             rect1.translation(Point(x,y));
             rect1.set_ptsFromNewpts();
             rect1.centroid = Point((rect1.pt1.x+rect1.pt3.x)/2,(rect1.pt1.y+rect1.pt3.y)/2);
         } else if (deformationType == "rotation") {
             rect1.rotation(Point(x,y));
             rect1.set_ptsFromNewpts();
         } else if (deformationType == "similarity") {
             rect1.similarity(Point(x,y));
             rect1.set_ptsFromNewpts();
         } else if (deformationType == "affine") {
             rect1.affine(Point(x,y));
             rect1.set_ptsFromNewpts();
             rect1.centroid = Point((rect1.pt1.x+rect1.pt3.x)/2,(rect1.pt1.y+rect1.pt3.y)/2);
         } else if (deformationType == "perspective") {
             rect1.perspective(Point(x,y));
             rect1.set_ptsFromNewpts();
             rect1.centroid = Point((rect1.pt1.x+rect1.pt3.x)/2,(rect1.pt1.y+rect1.pt3.y)/2);
         } else {
             rect1.set_endPoint(Point(x,y));
             rectangle(img, rect1.startPoint, rect1.endPoint, Scalar(0,0,255), 3);
             imgDrawn = true;
         }
         clicking = false;
     }
     else if ( event == EVENT_MOUSEMOVE)
     {
         if (clicking) {
             if  (x > imgLength) {}
             else if (deformationType == "translation") {rect1.translation(Point(x,y));}
             else if (deformationType == "rotation") {rect1.rotation(Point(x,y));}
             else if (deformationType == "similarity") {rect1.similarity(Point(x,y));}
             else if (deformationType == "affine") {rect1.affine(Point(x,y));}
             else if (deformationType == "perspective") {rect1.perspective(Point(x,y));}
             else {
             drawEmptyCanvasWithButtons();
             rectangle(img, rect1.startPoint, Point(x,y), Scalar(0,0,255), 3);
             }
         }
     }
}


int main() {
    
    // Create windows with callback functions for mouse events
    namedWindow("canvas");
    setMouseCallback("canvas", CallBackFunc, NULL);
    drawEmptyCanvasWithButtons();   // Create the deformation mode buttons
    
    // Use while loop to continually recreate "canvas" to display the rubber-band rectangle
    while (true)
    {
        int key=waitKey(20);
        imshow("canvas",img);
        if (key==27) {break;}
    }
    
    waitKey(0);
    return 0;
}

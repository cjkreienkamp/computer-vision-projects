/* To set up a new project:
    - choose macOS command line tool
    - add the Unix Executable Files (dynamic libraries) to the project, found in /usr/local/Cellar/opencv/ **version** /lib
    - enable the Resources folder access by going to "Edit Scheme"->"Options"->"Use custom working directory"->select your project folder which has "main.cpp" as a file
    - may need to enable camera access
    - Build Settings --> Header Search Paths --> /usr/local/Cellar/opencv/4.5.1/include/opencv4 --> recursive
    - Build Settings --> Library Search Paths --> /usr/local/Cellar/opencv/4.5.1/lib
    - Build Settings --> Documentation Comments --> No
    - Signing & Capabilities --> Disable Library Validation
*/





/*#include <opencv2/imgcodecs.hpp>
 #include <opencv2/highgui.hpp>
 #include <opencv2/imgproc.hpp>
 #include <iostream>

 using namespace cv;
 using namespace std;


 ///////////////// Webcam //////////////////////

 int main() {

  VideoCapture cap(0);
  Mat img;

  while (true) {

  cap.read(img);
  imshow("Image", img);
  waitKey(1);

  }
     return 0;
 }*/

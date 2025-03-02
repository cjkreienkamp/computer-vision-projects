//
//  trackbar.cpp
//  OpencvTutorial
//
//  Created by Chris Kreienkamp on 3/1/21.
//

/*void getContours(Mat imgDil, Mat img) {
 
 vector<vector<Point>> contours;  //vector with more vectors inside
 vector<Vec4i> hierarchy;

 findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
 
 vector<vector<Point>> conPoly(contours.size());
 vector<Rect> boundRect(contours.size());     //variable that we are introducing to the vector
 string objectType;
 
 // Filter to remove noise
 for (int i=0; i < contours.size(); i++) {
     int area = contourArea(contours[i]);
     if (area>10 && area<2000) {
         float peri = arcLength(contours[i], true);
         approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
         drawContours(img, conPoly, i, Scalar(255,0,255), 3);
     }
 }
}

void preprocessing(Mat img) {
 Mat imgGray, mask, imgBlur, imgCanny, imgDil, imgErode, imgMedian, imgFilter;
 mask = JonesRehg2002(img);
 GaussianBlur(img,imgBlur,Size(7,7),21);
 bilateralFilter(img, imgFilter, 5, 30, 30);
 erode(mask, imgErode, getStructuringElement(MORPH_RECT, Size(7,7)));
 medianBlur(imgErode, imgMedian, 7);
 cvtColor(img, imgMedian, COLOR_BGR2GRAY);
 Canny(imgMedian,imgCanny,25,75);
 dilate(imgCanny, imgDil, getStructuringElement(MORPH_RECT, Size(3,3)));
}*/

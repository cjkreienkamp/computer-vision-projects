//
//  kalman.cpp
//  OpenCVTutorial
//
//  Created by Chris Kreienkamp on 4/6/21.
//

//############### Kalman Filter ###############
/* Implement the Kalman Filter to see if it can work before inclusion into the water polo app.
 */

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    
    // ### SETUP ###
    
    // array sizes and number of iterations
    const int n_x = 2;
    const int n_u = 1;
    const int n_z = 1;
    const int numberOfIterations = 30;
    
    // input values of constant matrices
    double H_array[n_z][n_x] = {
        {1, 0}};
    double F_array[n_x][n_x] = {
        {1, 0.25},
        {0, 1}};
    double G_array[n_x][n_u] = {
        {0.0313},
        {0.25}};
    double Q_array[n_x][n_x] = {
        {pow(0.25,4)/4*pow(0.1,2), pow(0.25,3)/2*pow(0.1,2)},
        {pow(0.25,3)/2*pow(0.1,2), pow(0.25,2)*pow(0.1,2)}};
    double R_array[n_z][n_z] = {
        {400}};
    
    // create matrices
    cv::Mat x_hat = cv::Mat(n_x, 1, CV_64F);
    cv::Mat u = cv::Mat(n_u, 1, CV_64F);
    cv::Mat P = cv::Mat(n_x, n_x, CV_64F);
    cv::Mat F = cv::Mat(n_x, n_x, CV_64F, F_array);
    cv::Mat G = cv::Mat(n_x, n_u, CV_64F, G_array);
    cv::Mat Q = cv::Mat(n_x, n_x, CV_64F, Q_array);
    cv::Mat H = cv::Mat(n_z, n_x, CV_64F, H_array);
    cv::Mat z = cv::Mat(n_z, 1, CV_64F);
    cv::Mat R = cv::Mat(n_z, n_z, CV_64F, R_array);
    cv::Mat K = cv::Mat(n_x, n_z, CV_64F);
    cv::Mat I = cv::Mat::eye(n_x, n_x, CV_64F);
    
    // array of measured values
    double measurements[30] = {-32.4, -11.1, 18, 22.9, 19.5, 28.5, 46.5, 68.9, 48.2, 56.1, 90.5, 104.9, 140.9, 148, 187.6, 209.2, 244.6, 276.4, 323.5, 357.3, 357.4, 398.3, 446.7, 465.1, 529.4, 570.4, 636.8, 693.3, 707.3, 748.5};
    double controlVariables[30] = {39.72, 40.02, 39.97, 39.81, 39.75, 39.6, 39.77, 39.83, 39.73, 39.87, 39.81, 39.92, 39.78, 39.98, 39.76, 39.86, 39.61, 39.86, 39.74, 39.87, 39.63, 39.67, 39.96, 39.8, 39.89, 39.85, 39.9, 39.81, 39.81, 39.68};
    
    
    
    // ### INITIALIZE ###
    
    // Input: System State Initial Guess
    double x_hat_array[n_x][1] = {
        {0},
        {0}};
    x_hat = cv::Mat(n_x, 1, CV_64F, x_hat_array);
    double u_array[n_u][1] = {
        {9.8}};
    u = cv::Mat(n_u, 1, CV_64F, u_array);
    
    // Input: Estimate Uncertainty Initial Guess
    double P_array[n_x][n_x] = {
        {500, 0},
        {0, 500}};
    P = cv::Mat(n_x, n_x, CV_64F, P_array);
    
    
    
    for (int i=0; i<numberOfIterations; i++) {
           
        // ### PREDICT ###
        
        // Calculate the predicted state for the next iteration using system's Dynamic Model
        x_hat = F * x_hat + G * u;
        
        // Extrapolate the estimate uncertainty
        P = F * P * F.t() + Q;
        
        
        
        // ### MEASURE ###
        
        // Input: Measured Value
        z.at<double>(0,0) = measurements[i];
        u.at<double>(0,0) = controlVariables[i]-9.8;
        
        // Input Measurement Uncertainty
        R.at<double>(0,0) = 400;
        
        
        
        // ### UPDATE ###
        
        // Caculate the Kalman Gain (K_n) [nx x nu]
        K = P * H.t() * (H * P * H.t() + R).inv();
        
        // Estimate the current state using the State Update Equation
        x_hat = x_hat + K * (z - H * x_hat);
        
        // Estimate the current estimate uncertainty
        P = (I - K * H) * P * (I - K * H).t() + K * R * K.t();
    }
    
    // ### CHECK CALCULATIONS ###
    cout<<"K: "<<K<<endl;
    cout<<"x_hat: "<<x_hat<<endl;
    cout<<"P: "<<P<<endl;
}

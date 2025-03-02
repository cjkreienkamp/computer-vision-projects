# OpenCV C++ Experiments

This repository is a collection of C++ projects and tutorials that explore various functionalities of OpenCV, a powerful open-source computer vision library. The experiments range from basic image processing techniques to advanced computer vision algorithms.

## Table of Contents

- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Projects and Tutorials](#projects-and-tutorials)
- [Resources](#resources)

## Introduction

OpenCV (Open Source Computer Vision Library) provides a comprehensive set of tools for computer vision applications. This repository serves as a hands-on exploration of these tools, offering practical examples and tutorials to aid in understanding and implementing various OpenCV functionalities using C++.

## Project Structure

The repository is organized into the following directories and files:

- **Algorithms/**: Contains implementations of various computer vision algorithms.
- **Resources/**: Includes supplementary materials such as images and datasets used in the projects.
- **ObjectDetection/**: Focuses on object detection techniques and related projects.
- **Chapters/**:
  - **Chapter1.cpp**: Introduction to OpenCV and basic operations.
  - **Chapter2.cpp**: Image processing techniques.
  - **Chapter3.cpp**: Video processing and analysis.
  - **Chapter4.cpp**: Feature detection and description.
  - **Chapter5.cpp**: Object tracking methods.
  - **Chapter6.cpp**: Camera calibration and 3D reconstruction.
  - **Chapter7.cpp**: Machine learning with OpenCV.
  - **Chapter8.cpp**: Deep learning integration.
- **Projects/**:
  - **Project1.cpp**: Color Picker application.
  - **Project2.cpp**: Cascade classifier implementation.
  - **Project3.cpp**: Kalman filter for object tracking.
- **Extras/**:
  - **extraFunctions.cpp**: Utility functions supporting various projects and tutorials.
  - **OpenCVTutorial.entitlements**: Entitlement configurations for macOS.
  - **OpenCVTutorial.xcodeproj.zip**: Xcode project files for macOS users.


## Getting Started

To explore or execute the projects:

1. **Clone the repository**:

   ```bash
   git clone https://github.com/cjkreienkamp/opencv-cpp-experiments.git
   cd opencv-cpp-experiments
2. **Set up the development environment**:

  - **Install OpenCV**: Ensure OpenCV is installed on your system. Refer to the official OpenCV installation guide for instructions tailored to your operating system.
  - **Install a C++ compiler**: Ensure you have a C++ compiler installed (e.g., GCC for Linux, Clang for macOS, or MSVC for Windows).
  - **Install CMake**: CMake is used for building the projects. Download and install it from the official CMake website.

3. **Build the projects**:

  - Navigate to the project's directory:
    ```bash
    cd Chapters/Chapter1
    
  - Create a build directory:
    ```bash
    mkdir build
    cd build
    
  - Run Cmake to configure the project:
    ```bash
    cmake ..
    
  - Build the project:
    ```bash
    make
    
  - Execute the compiled program:
    ```bash
    ./Chapter1
    
  Repeat these steps for other chapters or projects as needed.

## Projects and Tutorials

Each chapter and project focuses on specific OpenCV functionalities:

- **Chapter1.cpp**: Introduction to OpenCV and basic operations.
- **Chapter2.cpp**: Image processing techniques.
- **Chapter3.cpp**: Video processing and analysis.
- **Chapter4.cpp**: Feature detection and description.
- **Chapter5.cpp**: Object tracking methods.
- **Chapter6.cpp**: Camera calibration and 3D reconstruction.
- **Chapter7.cpp**: Machine learning with OpenCV.
- **Chapter8.cpp**: Deep learning integration.
- **ColorPicker.cpp**: Application to pick and display colors from images.
- **cascade_classifier.cpp**: Implementation of cascade classifiers for object detection.
- **kalman.cpp**: Application of Kalman filter for object tracking.

For detailed explanations and code comments, refer to each source file.

## Resources

The **Resources/** directory contains supplementary materials such as images and datasets used in the projects.

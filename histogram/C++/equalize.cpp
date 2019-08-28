/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   equalize.cpp
 * Author: samuel
 *
 * Created on August 25, 2019, 3:54 PM
 */

#include <cstdlib>
#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

cv::Mat* equalize(cv::Mat&);

std::vector<int>* createHa(std::vector<int>*);
std::vector<int>* countingGray(cv::Mat&);

/*
 * 
 */
int main(int argc, char** argv) {

    cv::VideoCapture cam = cv::VideoCapture(0);

    if (not cam.isOpened()) {
        std::cout << "Camera não encontrada" << std::endl;
        std::exit(1);
    }

    std::string windowName = "frame and equalized frame";
    std::string exitKey = "e";

    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);

    cv::Mat frame;
    cv::Mat grayFrame;
    cv::Mat *equalizedFrame = NULL;
    cv::Mat grayFrameAndEqualizedFrame;
    cv::Mat test;

    while (exitKey != std::string(1, (char) (cv::waitKey(1) & 255))) {
        if (cam.read(frame)) {
            cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);

            equalizedFrame = equalize(grayFrame);
            cv::hconcat(grayFrame, *equalizedFrame, grayFrameAndEqualizedFrame);
            cv::imshow(windowName, grayFrameAndEqualizedFrame);
            cv::equalizeHist(grayFrame, test);
            cv::imshow("test", test);

        }

    }


    return 0;
}

cv::Mat* equalize(cv::Mat& image) {

    cv::Mat* equalizedImage = new cv::Mat(image.rows, image.cols, image.type());

    std::vector<int>* h = countingGray(image);

    std::vector<int>* ha = createHa(h);


    for (unsigned int i = 0; i < image.rows; i++)
        for (unsigned int j = 0; j < image.cols; j++) {
            int r = image.at<uchar>(i, j);
            equalizedImage->at<uchar>(i, j) = r / ha->at(r) * 255; // Dando valores abaixo de zero !!! PORQUE ??
            int verificarValor = (float) r / ha->at(r) * 255 ;
//            std::cout << verificarValor << std::endl;

        }

  


    return equalizedImage;

}

std::vector<int>* countingGray(cv::Mat& image) {
    std::vector<int> * countGray = new std::vector<int>(255, 0);

    for (unsigned int i = 0; i < image.rows; i++)
        for (unsigned int j = 0; j < image.cols; j++) {
            int r = image.at<uchar>(i, j);
            countGray->at(r)++;

        }

    return countGray;
}

std::vector<int>* createHa(std::vector<int>* h) {
    std::vector<int>* ha = new std::vector<int>(255, 0);
    ha->at(0) = h->at(0);

    for (unsigned int i = 1; i < 255; i++) {
        ha->at(i) = h->at(i) + ha->at(i - 1);
    }

    return ha;
}
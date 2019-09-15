//
// Created by samuel on 9/9/19.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Menu.h"

int main(int argvc, char **argv) {
    Menu menu;
    auto cam = cv::VideoCapture(0);
    std::string windowNameFilter = "Filtered";
    std::string windowNameCam = "Cam";
    std::string exitKey = "e";
    cv::namedWindow(windowNameCam);
    cv::namedWindow(windowNameFilter);

    if (not cam.isOpened()) {
        std::cout << "Camera não encotrada" << std::endl;
        std::exit(1);
    }
    std::string key = std::string(1, (char) (cv::waitKey(1) & 255));
    cv::Mat frame;
    cv::Mat grayFrame;
    cv::Mat filtered;
    while (exitKey != key) {
        if (cam.read(frame)) {
            cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
            menu.setOption(key);
            auto filtered32f = menu.getFilteredImage(grayFrame);
            filtered32f->convertTo(filtered,CV_8U);
            cv::imshow(windowNameCam, grayFrame);
            cv::imshow(windowNameFilter, filtered);

        }

    }


}
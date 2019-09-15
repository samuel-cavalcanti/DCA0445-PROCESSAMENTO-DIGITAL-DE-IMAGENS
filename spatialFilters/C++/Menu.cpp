//
// Created by samuel on 9/9/19.
//

#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Menu.h"

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))

Menu::Menu() {
    initializeKernels();
    mapCharToFunction();
    absolute = true;
    filter = &Menu::mean;
}

void Menu::initializeKernels() {

    float gauss[] = {1, 2, 1,
                     2, 4, 2,
                     1, 2, 1};

    float horizontal[] = {-1, 0, 1,
                          -2, 0, 2,
                          -1, 0, 1};

    float vertical[] = {-1, -2, -1,
                        0, 0, 0,
                        1, 2, 1};

    float laplacian[] = {0, -1, 0,
                         -1, 4, -1,
                         0, -1, 0};

    meanKernel = cv::Mat::ones(3, 3, CV_32F) / 9;
    gaussKernel = cv::Mat(3, 3, CV_32F, gauss) / 9;
    horizontalKernel = cv::Mat(3, 3, CV_32F, horizontal);
    verticalKernel = cv::Mat(3, 3, CV_32F, vertical);
    laplacianKernel = cv::Mat(3, 3, CV_32F, laplacian);
}


cv::Mat *Menu::mean(cv::Mat &image) {
    cv::Mat *temp = new cv::Mat(image.rows, image.cols, CV_32F);
    cv::filter2D(image, *temp, temp->depth(), meanKernel);
    return temp;

}

cv::Mat *Menu::gauss(cv::Mat &image) {


    cv::Mat *temp = new cv::Mat(image.rows, image.cols, CV_32F);
    cv::filter2D(image, *temp, temp->depth(), gaussKernel);
    return temp;
}

cv::Mat *Menu::horizontal(cv::Mat &image) {
    cv::Mat *temp = new cv::Mat(image.rows, image.cols, CV_32F);

    cv::filter2D(image, *temp, temp->depth(), horizontalKernel);
    return temp;
}

cv::Mat *Menu::vertical(cv::Mat &image) {
    cv::Mat *temp = new cv::Mat(image.rows, image.cols, CV_32F);

    cv::filter2D(image, *temp, temp->depth(), verticalKernel);
    return temp;

}

cv::Mat *Menu::laplacian(cv::Mat &image) {
    cv::Mat *temp = new cv::Mat(image.rows, image.cols, CV_32F);

    cv::filter2D(image, *temp, temp->depth(), laplacianKernel);

    return temp;

}

cv::Mat *Menu::laplace_over_gauss(cv::Mat &image) {
    cv::Mat *temp = new cv::Mat(image.rows, image.cols, CV_32F);

    cv::filter2D(image, *temp, temp->depth(), gaussKernel);
    cv::filter2D(*temp, *temp, temp->depth(), laplacianKernel);

    return temp;
}

void Menu::mapCharToFunction() {
//    options['a'] = &Menu::gauss;

    options["m"] = &Menu::mean;
    options["g"] = &Menu::gauss;
    options["v"] = &Menu::vertical;
    options["h"] = &Menu::horizontal;
    options["l"] = &Menu::laplacian;
    options["j"] = &Menu::laplace_over_gauss;


}

void Menu::setOption(std::string option) {
    if (option == "a")
        absolute = !absolute;
    else
        try {
            filter = options[option];
        }
        catch (std::string e) {
            return;
        }


}

cv::Mat *Menu::getFilteredImage(cv::Mat &image) {
    cv::Mat image32f;
    image.convertTo(image32f, CV_32F);
    filter = &Menu::gauss;
    cv::Mat *filtered = NULL;

    filtered = (this->*filter)(image32f);

    std::cout << filtered << std::endl;


    if (absolute) {
        image32f = cv::abs(*filtered);
        filtered = &image32f;
    }

    return filtered;
}






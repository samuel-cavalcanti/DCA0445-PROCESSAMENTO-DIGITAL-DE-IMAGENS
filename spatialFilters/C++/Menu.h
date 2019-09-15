//
// Created by samuel on 9/9/19.
//

#ifndef C___MENU_H
#define C___MENU_H


#include <map>
#include <opencv2/core/mat.hpp>


class Menu {
public:
    Menu();

    void setOption(std::string option);

    cv::Mat *getFilteredImage(cv::Mat &image);


private:
    using menuMemFn = cv::Mat *(Menu::*)(cv::Mat &);


    std::map<std::string, menuMemFn> options;

    void initializeKernels();

    void mapCharToFunction();

    cv::Mat *mean(cv::Mat &image);

    cv::Mat *gauss(cv::Mat &image);

    cv::Mat *horizontal(cv::Mat &image);

    cv::Mat *vertical(cv::Mat &image);

    cv::Mat *laplacian(cv::Mat &image);

    cv::Mat *laplace_over_gauss(cv::Mat &image);

    bool absolute;
    cv::Mat meanKernel;
    cv::Mat gaussKernel;
    cv::Mat horizontalKernel;
    cv::Mat verticalKernel;
    cv::Mat laplacianKernel;
    menuMemFn filter;

};


#endif //C___MENU_H

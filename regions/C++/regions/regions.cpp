#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <string>

cv::Mat loadImage(std::string pathImage);

void showImage(std::string title, cv::Mat& image);

int main(int argc, char** argv) {

    auto image = loadImage(argv[1]);
    
    auto rect2d = cv::selectROI(image);
    
    auto region = image(rect2d);
    
    region = 255 -region;
    
    showImage("image",image);



    return 0;

}

void showImage(std::string title, cv::Mat& image) {
    cv::namedWindow(title, cv::WINDOW_NORMAL);

    cv::imshow(title, image);
    cv::waitKey();
}

cv::Mat loadImage(std::string pathImage) {
    cv::Mat image = cv::imread(pathImage, cv::IMREAD_GRAYSCALE);

    if (not image.data) {
        std::cout << "imagem não carregada" << std::endl;
    }

    return image;
}
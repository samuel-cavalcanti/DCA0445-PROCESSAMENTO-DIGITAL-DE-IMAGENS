#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

#include "opencv2/core/types.hpp"
#include "opencv2/core/mat.hpp"

cv::Mat loadImage(std::string pathImage);

void showImage(std::string title, cv::Mat& image);

int main(int argc, char** argv) {

    cv::Mat image = loadImage(argv[1]);

    cv::Mat new_image;

    image.copyTo(new_image);


    cv::Rect A(0, 0, (int) image.rows / 2, (int) image.cols / 2);

    cv::Rect B((int) image.rows / 2, 0, (int) image.rows / 2, (int) image.cols / 2);

    cv::Rect C(0, (int) image.cols / 2, (int) image.rows / 2, (int) image.cols / 2);

    cv::Rect D((int) image.rows / 2, (int) image.cols / 2, (int) image.rows / 2, (int) image.cols / 2);

    image(A).copyTo(new_image(D));

    image(D).copyTo(new_image(A));

    image(B).copyTo(new_image(C));

    image(C).copyTo(new_image(B));


    showImage("puzzle biel", new_image);

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

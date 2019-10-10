#include <iostream>
#include <opencv2/opencv.hpp>
#include <list>

void onChange(int value, void *);

cv::Mat *loadImage(int &argc, char **&argv);

cv::Mat *cannyPointillism(cv::Mat &image, cv::Mat &restrictions);

cv::Mat *makeRestrictionsMat(int &cannySlider);

cv::Mat *originalImage;

int main(int argc, char **argv) {

    originalImage = loadImage(argc, argv);


    int value = 0;
    int radius =1;
    std::string windowName = "Canny Points";

    cv::namedWindow(windowName, cv::WINDOW_NORMAL);
    cv::createTrackbar("Canny threshold", windowName, &value, 100, onChange);
    cv::createTrackbar("Radius", windowName, &radius, 15, onChange);
    cv::createTrackbar("save image", windowName, &value, 1, onChange);


    onChange(value, nullptr);
    cv::imshow("Original image", *originalImage);
    cv::waitKey();
    return 0;

}

cv::Mat *loadImage(int &argc, char **&argv) {
    if (argc < 2) {
        std::cout << "por favor digite o caminho da imagem" << std::endl;
        std::exit(1);
    }
    cv::Mat *image = new cv::Mat(cv::imread(argv[1]));
    if (image->empty()) {
        std::cout << "imagem" << argv[1] << " não encontrada" << std::endl;
        std::exit(2);
    }

    return image;

}

void onChange(int value, void *) {
    std::vector<cv::Mat> outputBrg;
    cv::Mat outputImage;
    std::vector<cv::Mat> brg;

    cv::split(*originalImage, brg);
    auto restrictions = makeRestrictionsMat(value);

    std::string windowName = "Canny Points";
    for (auto layer : brg) {
        outputBrg.push_back(*cannyPointillism(layer, *restrictions));
    }

    cv::merge(outputBrg, outputImage);

    cv::imshow(windowName, outputImage);

    if (cv::getTrackbarPos("save image", windowName)) {
        cv::imwrite("cannyPointillism.png", outputImage);
    }


}

cv::Mat *cannyPointillism(cv::Mat &image, cv::Mat &restrictions) {
    cv::Mat *outputImage = new cv::Mat(image.size(), image.type(), cv::Scalar(255));

    int radius = cv::getTrackbarPos("Radius", "Canny Points");

    for (int i = 0; i < outputImage->rows; i++)
        for (int j = 0; j < outputImage->cols; j++) {
            int color = image.at<uchar>(i, j);
            if (restrictions.at<uchar>(i, j)) {
                cv::circle(*outputImage, cv::Point(j, i), radius, CV_RGB(color, color, color), -1, cv::LINE_AA);
            }
        }

    return outputImage;
}

cv::Mat *makeRestrictionsMat(int &cannySlider) {
    cv::Mat grayScaleImage;
    cv::Mat *restrictions = new cv::Mat(originalImage->size(), originalImage->type());

    cv::cvtColor(*originalImage, grayScaleImage, cv::COLOR_BGR2GRAY);
    cv::Canny(grayScaleImage, *restrictions, cannySlider, cannySlider * 3);

    return restrictions;

}

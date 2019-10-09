#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>


void shiftDFT(cv::Mat &image);

cv::Mat *defineHomomorphicFilter(cv::Size dftSize, float c, float d0, float gammaHigh, float gammaLow);

void onChange(int, void *);

cv::Mat *realToComplex(cv::Mat &real);

cv::Mat *complexToReal(cv::Mat &complex);

void createTrackbars(std::string &trackbarName, int *gammaLow, int *gammaHigh, int *c, int *d0);

void createWindows(std::string &filteredWindowName, std::string &originalWindowName);

void getTrackbarsPos(std::string &filteredWindowName, float &gammaLow, float &gammaHigh, float &c, float &d0);


static cv::Mat originalImage;
static cv::Mat dftResult;

int gammaLow = 0;
int gammaHigh = 1;
int d0 = 200;
int c = 7;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << " passe a imagem por parâmetro !!" << std::endl;
        std::exit(1);
    }

    originalImage = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);

    if (originalImage.empty()) {
        std::cout << " imagem" << argv[1] << " não carregada !!" << std::endl;
        exit(2);
    }

    cv::resize(originalImage, originalImage, cv::Size(1080, 720));

    cv::imwrite("../original.jpg", originalImage);

    std::string originalWindowName = "Original image";
    std::string filteredWindowName = "Filtered image";

    createWindows(filteredWindowName, originalWindowName);

    cv::Size dftSize(cv::getOptimalDFTSize(originalImage.cols), cv::getOptimalDFTSize(originalImage.rows));
    cv::Size paddedSize(dftSize.width - originalImage.cols, dftSize.height - originalImage.rows);


    cv::Mat padded;


    cv::copyMakeBorder(originalImage, padded, 0, paddedSize.height, 0, paddedSize.height, cv::BORDER_CONSTANT,
                       cv::Scalar(0));

    padded.convertTo(padded, CV_32F);

    cv::normalize(padded, padded, 0, 1, cv::NORM_MINMAX);

    auto complexImage = realToComplex(padded);

    cv::dft(*complexImage, dftResult);

    shiftDFT(dftResult);
    int *none = &dftSize.width;

    onChange(*none, none);

    cv::waitKey(0);

    return 0;
}


void shiftDFT(cv::Mat &image) {
    cv::Mat tmp, A, B, C, D;
    // se a imagem tiver tamanho impar, recorta a regiao para
    // evitar cópias de tamanho desigual
    image = image(cv::Rect(0, 0, image.cols & -2, image.rows & -2));
    int cx = image.cols / 2;
    int cy = image.rows / 2;

    // reorganiza os quadrantes da transformada
    // A B   ->  D C
    // C D       B A
    A = image(cv::Rect(0, 0, cx, cy));
    B = image(cv::Rect(cx, 0, cx, cy));
    C = image(cv::Rect(0, cy, cx, cy));
    D = image(cv::Rect(cx, cy, cx, cy));

    // A <-> D
    A.copyTo(tmp);
    D.copyTo(A);
    tmp.copyTo(D);

    // C <-> B
    C.copyTo(tmp);
    B.copyTo(C);
    tmp.copyTo(B);
}

cv::Mat *realToComplex(cv::Mat &real) {
    cv::Mat *complex = new cv::Mat(real.size(), CV_32FC2);
    for (int i = 0; i < real.rows; i++)
        for (int j = 0; j < real.cols; j++) {
            complex->at<cv::Vec2f>(i, j)[0] = cv::log(real.at<float>(i, j) + 1);
            complex->at<cv::Vec2f>(i, j)[1] = 0;
        }

    return complex;
}

cv::Mat *complexToReal(cv::Mat &complex) {
    auto real = new cv::Mat(complex.size(), CV_32F);

    for (int i = 0; i < real->rows; i++)
        for (int j = 0; j < real->cols; j++) {
            real->at<float>(i, j) = complex.at<cv::Vec2f>(i, j)[0];

        }


    return real;
}

void createTrackbars(std::string &trackbarName, int *gammaLow, int *gammaHigh, int *c, int *d0) {

    cv::createTrackbar("gamma low", trackbarName, gammaLow, 200, onChange);
    cv::createTrackbar("gamma high", trackbarName, gammaHigh, 200, onChange);
    cv::createTrackbar("D 0", trackbarName, d0, 200, onChange);
    cv::createTrackbar("c ", trackbarName, c, 200, onChange);


}

void onChange(int, void *) {
    std::string originalWindowName = "Original image";
    std::string filteredWindowName = "Filtered image";


    std::cout << "gammaHigh " << gammaHigh << " gammaLow " << gammaLow << " d0 " << d0 << " c " << c << std::endl;

    auto homomorphic = defineHomomorphicFilter(dftResult.size(), c, d0, gammaHigh, gammaLow);

    cv::Mat outputFilter;

    cv::mulSpectrums(dftResult, *homomorphic, outputFilter, 0);

    shiftDFT(outputFilter);

    cv::idft(outputFilter, outputFilter, cv::DFT_SCALE);

    cv::exp(outputFilter, outputFilter);

    auto real = complexToReal(outputFilter);

    cv::normalize(*real, *real, 0, 1, cv::NORM_MINMAX);


    cv::imshow(originalWindowName, originalImage);
    cv::imshow(filteredWindowName, *real);

    cv::normalize(*real, *real, 0, 255, cv::NORM_MINMAX);

    cv::imwrite("../filtered.jpg", *real);


}


cv::Mat *defineHomomorphicFilter(cv::Size dftSize, float c, float d0, float gammaHigh, float gammaLow) {
    cv::Mat *homomorphic = new cv::Mat(dftSize, CV_32FC2, cv::Scalar(0, 0));


    for (int i = 0; i < homomorphic->rows; i++)
        for (int j = 0; j < homomorphic->cols; j++) {
            double d_2 = cv::pow(i - homomorphic->rows / 2, 2) + cv::pow(j - homomorphic->cols / 2, 2);

            double value = (gammaHigh - gammaLow) * (1 - cv::exp(-c * d_2 / cv::pow(d0, 2))) + gammaLow;

            homomorphic->at<cv::Vec2f>(i, j)[0] = value;
            homomorphic->at<cv::Vec2f>(i, j)[1] = value;


        }


    return homomorphic;
}

void createWindows(std::string &filteredWindowName, std::string &originalWindowName) {


    cv::namedWindow(filteredWindowName, cv::WINDOW_NORMAL);
    cv::namedWindow(originalWindowName, cv::WINDOW_NORMAL);

    createTrackbars(filteredWindowName, &gammaLow, &gammaHigh, &c, &d0);
}

void getTrackbarsPos(std::string &filteredWindowName, float &gammaLow, float &gammaHigh, float &c, float &d0) {
    gammaLow = (float) cv::getTrackbarPos(filteredWindowName, "gamma low") - 199;

    gammaHigh = (float) cv::getTrackbarPos(filteredWindowName, "gamma high") + 1;

    d0 = (float) cv::getTrackbarPos(filteredWindowName, "D 0");

    c = (float) cv::getTrackbarPos(filteredWindowName, "c ");

}


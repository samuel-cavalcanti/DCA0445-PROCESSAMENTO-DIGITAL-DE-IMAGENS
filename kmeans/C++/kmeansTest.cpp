#include <iostream>
#include <opencv2/opencv.hpp>
#include <getopt.h>

cv::Mat *makeDataSet(cv::Mat &image);

void getOptions(int &argc, char **&argv, int &nClusters, int &rounds, cv::Mat &image, std::string &fileName);

void printHelp();

cv::Mat *executeKmeans(int &nClusters, int &rounds, cv::Mat &dataset, cv::Mat &image);

cv::Mat *makeLabeledImg(cv::Mat &image, cv::Mat &labels, cv::Mat &centers);

int main(int argc, char **argv) {
    int nClusters = -1;
    int rounds = -1;

    std::string fileName = "-1";
    cv::Mat image;

    getOptions(argc, argv, nClusters, rounds, image, fileName);

    auto dataset = makeDataSet(image);
    std::srand(std::time(nullptr));

    if (fileName == "-1") {
        for (int i = 0; i < 25; i++) {
            auto labeled = executeKmeans(nClusters, rounds, *dataset, image);
            cv::imwrite(std::to_string(i) + ".jpg", *labeled);
        }

    } else {
        auto labeled = executeKmeans(nClusters, rounds, *dataset, image);

        cv::imshow("clustered image", *labeled);
        cv::imwrite(fileName, *labeled);
        cv::waitKey();
    }


    return 0;
}

cv::Mat *makeDataSet(cv::Mat &image) {
    auto dataSet = new cv::Mat(image.rows * image.cols, 3, CV_32F);

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int z = 0; z < 3; z++) {
                dataSet->at<float>(y + x * image.rows, z) = image.at<cv::Vec3b>(y, x)[z];
            }
        }
    }

    return dataSet;
}

void printHelp() {
    std::cout <<
              "--rounds <r>:\trecebe o número de execuçoes do k-means\n"
              "--help:\tmostra o help na tela\n"
              "--clusters <c>:\t recebe o número de médias do k-means\n";

    exit(1);
}

void getOptions(int &argc, char **&argv, int &nClusters, int &rounds, cv::Mat &image, std::string &fileName) {
    const option longOpts[] = {
            {"rounds",   required_argument, nullptr, 'r'},
            {"clusters", required_argument, nullptr, 'c'},
            {"output",   required_argument, nullptr, 'o'},
            {"image",    required_argument, nullptr, 'i'},
            {"help",     no_argument,       nullptr, 'h'}
    };

    int opt = 1;

    while (opt != -1) {
        opt = getopt_long_only(argc, argv, "r: i: c: o:", longOpts, nullptr);

        switch (opt) {
            case 'r':
                rounds = std::stoi(optarg);
                break;
            case 'c':
                nClusters = std::stoi(optarg);
                break;
            case 'h':
                printHelp();
                break;
            case 'i':
                image = cv::imread(optarg);
                break;
            case 'o':
                fileName = optarg;
                break;
            case '?':
                printHelp();
                break;
        }

    }

    if (image.empty()) {
        std::cout << "erro ao carregar a imagem " << std::endl;
        exit(2);
    }

    if (nClusters == -1) {
        std::cout << " por favor atribua um valor para -clusters" << std::endl;
        exit(3);
    }


    if (rounds == -1) {
        std::cout << " por favor atribua um valor para -rounds" << std::endl;
        exit(4);
    }


}

cv::Mat *executeKmeans(int &nClusters, int &rounds, cv::Mat &dataset, cv::Mat &image) {
    int maxIt = 1e4;
    float epsilon = 0.1e-4;
    cv::Mat labels;
    cv::Mat centers;

    cv::kmeans(dataset, nClusters, labels,
               cv::TermCriteria(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS, maxIt, epsilon), rounds,
               cv::KMEANS_RANDOM_CENTERS, centers);


    return makeLabeledImg(image, labels, centers);;
}

cv::Mat *makeLabeledImg(cv::Mat &image, cv::Mat &labels, cv::Mat &centers) {


    auto labeled = new cv::Mat(image.size(), image.type());

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            int indice = labels.at<int>(y + x * image.rows, 0);
            labeled->at<cv::Vec3b>(y, x)[0] = (uchar) centers.at<float>(indice, 0);
            labeled->at<cv::Vec3b>(y, x)[1] = (uchar) centers.at<float>(indice, 1);
            labeled->at<cv::Vec3b>(y, x)[2] = (uchar) centers.at<float>(indice, 2);
        }
    }

    return labeled;

}



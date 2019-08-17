#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

cv::Mat loadImage(std::string);
int countObjects(cv::Mat& image, int gray_scale_color=255);
void showImage(std::string title, cv::Mat& image);
void removingObjectsOnLimits(cv::Mat&);
int countHoles(cv::Mat&);
void countObjectsWithHoles(cv::Mat,int&,int&,int&);
int main(int argc, char const *argv[]){

    cv::Mat image = loadImage(argv[1]);
    
    int allObjects;
    int holes;
    int noHoles;

    countObjectsWithHoles(image.clone(),allObjects,holes,noHoles);
    
    int nObjects = countObjects(image);


    std::cout << "counting objects and holes" << std::endl << std::endl;

    std::cout << "all Objects: " << allObjects << std::endl;
    std::cout << "Objects with holes: " << holes << std::endl;
    std::cout << "Objects with not holes: " << noHoles << std::endl << std::endl << std::endl;
    

    std::cout << "just counting objects: " << std::endl << std::endl;

    std::cout << "all Objects: " << nObjects << std::endl;



    // std::cout << nObjects << std::endl;
    

  

  
    


    /* code */
    return 0;
}



cv::Mat loadImage(std::string file_name){
    cv::Mat image = cv::imread(file_name,cv::IMREAD_GRAYSCALE);

    if ( not image.data){
        std::cout << "não foi possível carregar a imagem !!" << std::endl;
        std::exit(-1);
    }

    return image;

}
void showImage(std::string title, cv::Mat& image) {
    cv::namedWindow(title, cv::WINDOW_NORMAL);

    cv::imshow(title, image);
    cv::waitKey();
}

int countObjects(cv::Mat& image, int gray_scale_color){
    int n_objects = 1;

    for (int i = 0; i < image.rows; i++)
        for(int j =0; j < image.cols; j++)
            if (image.at<uchar>(i,j) == gray_scale_color ){
                if (n_objects >= 255){
                    cv::floodFill(image,cv::Point(j,i),100);
                }else{
                    cv::floodFill(image,cv::Point(j,i),n_objects);
                }
                n_objects++;
            }

    return n_objects -1;
}


void removingObjectsOnLimits(cv::Mat& image){
    int black = 0;
    int limit_i = image.rows -1;
    int limit_j = image.cols -1;

    for (int i = 0; i < image.rows; i++)
        for ( int j=0; j < image.cols; j++){
            uchar color = image.at<uchar>(i,j);

          if (( j == 0 or j == limit_j) and color > black)
              cv::floodFill(image,cv::Point(j,i),black);

          else if ((i == 0 or i == limit_i) and color > black)
              cv::floodFill(image,cv::Point(j,i),black );
        }
            
    
}

int countHoles(cv::Mat& image){
    int white = 255;
    int black = 0;
    int holes = 0;

    for (int i =0; i< image.rows;i++)
        for (int j=1; j< image.cols;j++){
            if (image.at<uchar>(i,j) == black and (black > image.at<uchar>(i,j-1) < white) ){
                cv::floodFill(image,cv::Point(j-1,i),black);
                cv::floodFill(image,cv::Point(j,i),white);
                holes++;
            }
            
        }

    return holes;
}


void countObjectsWithHoles(cv::Mat image,int&allObjects,int&holes,int&noHoles){

    removingObjectsOnLimits(image);

    allObjects = countObjects(image);
    holes = countHoles(image);
  
    noHoles = allObjects - holes;

}
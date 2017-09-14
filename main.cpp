#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "csv_dataproc.h"
#include <stdlib.h>
#include <stdio.h>

using namespace std;
using namespace cv;


//argv[1]: classified datasets after SOM, must be .csv
//argv[2]: result after SOM, must be .csv
//argv[3]: input image
//argv[4]: output image
//argv[5]: numbers of classified groups
int main(int argc, char **argv)
{
    if(argc < 2){
        cout<<"numbers of parameter error"<<endl;
        return -1;
    }

    csv_t input;

    int ret = csv_read(&input, argv[1]);
    if(ret != 0){
        cout<<"load "<< argv[1]<< "failed"<<endl;
        return -1;
    }

    csv_t distribute;
    ret = csv_read(&distribute, argv[2]);
    if(ret != 0){
        cout<<"load "<< argv[2]<< "failed"<<endl;
        return -1;
    }

    //csv_print(input);
    csv_print(distribute);

    Mat img = imread(argv[3], CV_LOAD_IMAGE_COLOR);
    if(!img.data){
        cout<<"load "<< argv[3]<< "failed"<<endl;
        return -1;
    }
    int count = 0;

    for(int i=0; i<img.rows; i++){
        for(int j=img.cols-1; j>=0; j--){
            int number = (int)csv_get_value(input, count++, 0);
            for(int k=0; k<3; k++){
                if(number == k){
                    img.at<Vec3b>(j,i)[0] = csv_get_value(distribute, k, 0);
                    img.at<Vec3b>(j,i)[1] = csv_get_value(distribute, k, 1);
                    img.at<Vec3b>(j,i)[2] = csv_get_value(distribute, k, 2);
                    break;
                }
            }
        }
    }
/*
    for(int i=0; i<img.rows; i++){
        for(int j=img.cols-1; j>=0; j--){
            switch((int) csv_get_value(input, count++, 0)){
                case 0:
                    img.at<Vec3b>(j,i)[0] = csv_get_value(distribute, 0, 0);
                    img.at<Vec3b>(j,i)[1] = csv_get_value(distribute, 0, 1);
                    img.at<Vec3b>(j,i)[2] = csv_get_value(distribute, 0, 2);
                    break;
                case 1:
                    img.at<Vec3b>(j,i)[0] = csv_get_value(distribute, 1, 0);
                    img.at<Vec3b>(j,i)[1] = csv_get_value(distribute, 1, 1);
                    img.at<Vec3b>(j,i)[2] = csv_get_value(distribute, 1, 2);
                    break;
                case 2:
                    img.at<Vec3b>(j,i)[0] = csv_get_value(distribute, 2, 0);
                    img.at<Vec3b>(j,i)[1] = csv_get_value(distribute, 2, 1);
                    img.at<Vec3b>(j,i)[2] = csv_get_value(distribute, 2, 2);
                    break;
            }
        }
    }
*/
    imwrite(argv[4], img);

    return 0;
}

//头文件+dll动态库
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void main(){
	//读取一张图片，返回Mat对象
	Mat src = imread("D:/photo.jpg");

	Mat dst;

	cvtColor(src, dst, COLOR_BGR2GRAY);


	//将Mat对象写入文件
	imwrite("D:/copy.jpg", dst);

	//显示图片
	imshow("test", dst);

	//openCV的等待
	waitKey(0);
}
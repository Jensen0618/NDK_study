//ͷ�ļ�+dll��̬��
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void main(){
	//��ȡһ��ͼƬ������Mat����
	Mat src = imread("D:/photo.jpg");

	Mat dst;

	cvtColor(src, dst, COLOR_BGR2GRAY);


	//��Mat����д���ļ�
	imwrite("D:/copy.jpg", dst);

	//��ʾͼƬ
	imshow("test", dst);

	//openCV�ĵȴ�
	waitKey(0);
}
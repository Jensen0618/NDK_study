//ͷ�ļ�+dll��̬��
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

void main(){
	//��ȡһ��ͼƬ������Mat����
	Mat src = imread("D:/photo.jpg");

	//Mat dst;

	//cvtColor(src, dst, COLOR_BGR2GRAY);


	//��Mat����д���ļ�
	//imwrite("D:/copy.jpg", dst);

	for (size_t i = 0; i < src.rows; i++)
	{
		uchar* point = src.ptr<uchar>(i); //��ȡ��i�е���ָ��

		for (size_t j = 0; j < src.cols; j++)
		{
			//��ȡÿ�����ص��BGRֵ
			//Vec3b bgr = src.at<Vec3b>(i, j);
			//���ÿ�����ص��BGRֵ
			//printf("��%d�У���%d�е����ص��BGRֵΪ��%d,%d,%d\n", i, j, bgr[0], bgr[1], bgr[2]);
			//ȡ��ÿһ�����ص��BGRֵ
			uchar b = point[j * 3 + 0]; //��ɫͨ��
			uchar g = point[j * 3 + 1]; //��ɫͨ��
			uchar r = point[j * 3 + 2]; //��ɫͨ��

			uchar gray = 0.11 * b + 0.59 * g + 0.3 * r; //�Ҷ�ֵ

			point[j * 3 + 0] = gray; //��ɫͨ��
			point[j * 3 + 1] = gray; //��ɫͨ��
			point[j * 3 + 2] = gray; //��ɫͨ��
		}

	}

	//��ʾͼƬ
	imshow("test", src);

	//���ߡ�ͨ����
	printf("ͼƬ�Ŀ�ȣ�%d��ͼƬ�ĸ߶ȣ�%d��ͼƬ��ͨ������%d\n", src.cols,src.rows,src.channels());

	//openCV�ĵȴ�
	waitKey(0);
}
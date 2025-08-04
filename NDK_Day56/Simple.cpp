//ͷ�ļ�+dll��̬��
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
/*
void main(){
	//��ȡһ��ͼƬ������Mat����
	Mat src = imread("D:/����.jpg");

	//Mat dst;

	//cvtColor(src, dst, COLOR_BGR2GRAY);


	//��Mat����д���ļ�
	//imwrite("D:/copy.jpg", dst);

	//Mat�Ǹ����󣬾����������أ�ÿ��������n��ͨ��
	for (size_t i = 0; i < src.rows; i++)
	{
		uchar* point = src.ptr<uchar>(i); //��ȡ��i�����ص���ָ��

		//����ÿ������
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

			//0.11 * r + 0.59 * g + 0.3 * b �����ʽ������Ҳ�ǻҶ�ͼƬ��ϸ�����в�ͬ
			//0.11+0.59+0.3=1���ù�ʽ�����ֵΪ255����uchar��Χ��
			//uchar gray = 0.11 * b + 0.59 * g + 0.3 * r; //�Ҷ�ֵ

			//point[j * 3 + 0] = gray; //��ɫͨ��
			//point[j * 3 + 1] = gray; //��ɫͨ��
			//point[j * 3 + 2] = gray; //��ɫͨ��

			//�������
			//saturate_cast<uchar>(1.2*b)����ȫת����ʹ����uchar����ֵ��Χ��
			point[j * 3 + 0] = saturate_cast<uchar>(1.2*b); //��ɫͨ��
			point[j * 3 + 1] = saturate_cast<uchar>(1.2 * g); //��ɫͨ��
			point[j * 3 + 2] = saturate_cast<uchar>(1.2 * r); //��ɫͨ��
		}

	}

	imwrite("D:/copy.jpg", src);

	//��ʾͼƬ
	imshow("test", src);

	//���ߡ�ͨ����
	printf("ͼƬ�Ŀ�ȣ�%d��ͼƬ�ĸ߶ȣ�%d��ͼƬ��ͨ������%d\n", src.cols,src.rows,src.channels());

	//openCV�ĵȴ�
	waitKey(0);
}*/

/*void main() {
	//openCV�е���ɫ˳����BGR��BGR��BGR
	//Mat���캯��

	//rows,cols,type����ֱ���ĸ���ǰ�����ں�
	//Mat mat(30, 60, CV_8UC1);

	//��Size���ͱȽϺ������
	//Mat mat(Size(10, 20), CV_8UC3, Scalar(255, 0, 0));

	Mat mat = imread("D:/����2.jpg");

	if (mat.empty())
	{
		cout << "imread error" << endl;
		getchar();
		return;
	}
	//����
	if (!mat.data)
	{
		cout << "imread error" << endl;
		getchar();
		return;
	}


	//�������캯��
	Mat copy_mat(mat);

	//���÷�����
	Mat dst;
	//����
	//mat.copyTo(dst);
	//ת�� ûЧ������
	mat.convertTo(dst, CV_8UC1);
	//��Ҳ�Ǹ���
	mat.clone();


	//cout << mat << endl;
	imshow("test", dst );
	waitKey(0);

}*/

/*void main() {
	//��ȡһ��ͼƬ������Mat����
	Mat src = imread("D:/����.jpg");
	int width = src.cols;
	int height = src.rows;
	int channels = src.channels();
	cout << "w:" << width << ", h:" << height << ", channels:" << channels << endl;

	//�½�һ�����󣬽�ȡ��ԭͼ��һ�룻
	//�������캯������û�и��Ƴ�����һ�ݣ���ǳ��������������޸Ļ�ֱ�ӷ�Ӧ��ԭͼ�ϡ�
	Mat temp = src(Rect(0, 0, width / 2, height));
	//���Ǹ���
	Mat dst = temp.clone();

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (channels == 3)
			{
				//��ȡ���ص㣬at������3ͨ��ʹ��Vec3b
				Vec3b vec = dst.at<Vec3b>(i, j);
				int b = vec[0];
				int g = vec[1];
				int r = vec[2];

				//��ƬЧ��
				dst.at<Vec3b>(i, j)[0] = 255 - b;
				dst.at<Vec3b>(i, j)[1] = 255 - g;
				dst.at<Vec3b>(i, j)[2] = 255 - r;

			}


		}
	}

	imshow("src", dst);
	waitKey(0);
}*/


void main(){
	//��ȡһ��ͼƬ������Mat����
	Mat src = imread("D:/sfz.jpg");
	int width = src.cols;
	int height = src.rows;
	int channels = src.channels();
	cout << "w:" << width << ", h:" << height << ", channels:" << channels << endl;

	Mat dst(height,width,CV_8UC1);

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (channels == 3)
			{
				//��ȡ���ص㣬at������3ͨ��ʹ��Vec3b
				
				Vec3b vec = src.at<Vec3b>(i, j);
				uchar b = vec[0];
				uchar g = vec[1];
				uchar r = vec[2];
				
				int gray = 0.11 * b + 0.59 * g + 0.3 * r;

				dst.at<uchar>(i, j) = gray;
			}


		}
	}

	Mat dst2;
	cvtColor(src, dst2, COLOR_BGR2GRAY);
	imwrite("D:/sfzcopy2.jpg",dst2);

	imwrite("D:/sfzcopy.jpg",dst);

	imshow("dst", dst);
	waitKey(0);
}
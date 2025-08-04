//头文件+dll动态库
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
/*
void main(){
	//读取一张图片，返回Mat对象
	Mat src = imread("D:/张三.jpg");

	//Mat dst;

	//cvtColor(src, dst, COLOR_BGR2GRAY);


	//将Mat对象写入文件
	//imwrite("D:/copy.jpg", dst);

	//Mat是个矩阵，矩阵里是像素，每个像素有n个通道
	for (size_t i = 0; i < src.rows; i++)
	{
		uchar* point = src.ptr<uchar>(i); //获取第i行像素的首指针

		//遍历每个像素
		for (size_t j = 0; j < src.cols; j++)
		{
			//获取每个像素点的BGR值
			//Vec3b bgr = src.at<Vec3b>(i, j);
			//输出每个像素点的BGR值
			//printf("第%d行，第%d列的像素点的BGR值为：%d,%d,%d\n", i, j, bgr[0], bgr[1], bgr[2]);

			//取出每一个像素点的BGR值
			uchar b = point[j * 3 + 0]; //蓝色通道
			uchar g = point[j * 3 + 1]; //绿色通道
			uchar r = point[j * 3 + 2]; //红色通道

			//0.11 * r + 0.59 * g + 0.3 * b 这个公式出来的也是灰度图片，细节上有不同
			//0.11+0.59+0.3=1，该公式的最大值为255，在uchar范围内
			//uchar gray = 0.11 * b + 0.59 * g + 0.3 * r; //灰度值

			//point[j * 3 + 0] = gray; //蓝色通道
			//point[j * 3 + 1] = gray; //绿色通道
			//point[j * 3 + 2] = gray; //红色通道

			//提高亮度
			//saturate_cast<uchar>(1.2*b)，安全转换，使其在uchar的数值范围内
			point[j * 3 + 0] = saturate_cast<uchar>(1.2*b); //蓝色通道
			point[j * 3 + 1] = saturate_cast<uchar>(1.2 * g); //绿色通道
			point[j * 3 + 2] = saturate_cast<uchar>(1.2 * r); //红色通道
		}

	}

	imwrite("D:/copy.jpg", src);

	//显示图片
	imshow("test", src);

	//宽、高、通道数
	printf("图片的宽度：%d，图片的高度：%d，图片的通道数：%d\n", src.cols,src.rows,src.channels());

	//openCV的等待
	waitKey(0);
}*/

/*void main() {
	//openCV中的颜色顺序是BGR，BGR，BGR
	//Mat构造函数

	//rows,cols,type，反直觉的高在前，宽在后
	//Mat mat(30, 60, CV_8UC1);

	//用Size来就比较合理，宽高
	//Mat mat(Size(10, 20), CV_8UC3, Scalar(255, 0, 0));

	Mat mat = imread("D:/张三2.jpg");

	if (mat.empty())
	{
		cout << "imread error" << endl;
		getchar();
		return;
	}
	//或者
	if (!mat.data)
	{
		cout << "imread error" << endl;
		getchar();
		return;
	}


	//拷贝构造函数
	Mat copy_mat(mat);

	//常用方法：
	Mat dst;
	//复制
	//mat.copyTo(dst);
	//转换 没效果啊？
	mat.convertTo(dst, CV_8UC1);
	//这也是复制
	mat.clone();


	//cout << mat << endl;
	imshow("test", dst );
	waitKey(0);

}*/

/*void main() {
	//读取一张图片，返回Mat对象
	Mat src = imread("D:/张三.jpg");
	int width = src.cols;
	int height = src.rows;
	int channels = src.channels();
	cout << "w:" << width << ", h:" << height << ", channels:" << channels << endl;

	//新建一个对象，截取了原图的一半；
	//拷贝构造函数，并没有复制出另外一份，是浅拷贝，在上面的修改会直接反应在原图上。
	Mat temp = src(Rect(0, 0, width / 2, height));
	//这是复制
	Mat dst = temp.clone();

	for (int i = 0; i < dst.rows; i++)
	{
		for (int j = 0; j < dst.cols; j++)
		{
			if (channels == 3)
			{
				//获取像素点，at方法，3通道使用Vec3b
				Vec3b vec = dst.at<Vec3b>(i, j);
				int b = vec[0];
				int g = vec[1];
				int r = vec[2];

				//底片效果
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
	//读取一张图片，返回Mat对象
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
				//获取像素点，at方法，3通道使用Vec3b
				
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
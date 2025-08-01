//头文件+dll动态库
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

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
}
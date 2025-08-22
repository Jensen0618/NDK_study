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


/*void main() {//RGB转单通道灰度图
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
}*/

/*void main() {//图像混合
	Mat src = imread("D:/张三.jpg");
	Mat src2 = imread("D:/sfz_pic.jpg");
	//区域截图
	Mat src1 = src(Rect(0, 0, src2.cols, src2.rows));
	Mat dst;
	//add(src, src2,dst);//add方法要求混合的两张图尺寸一致，否则报错；简单混合，无法调整权重。

	// 加权融合参数
	double alpha = 0.7;  // img1 权重 (70%)
	double beta = 0.3;   // img2 权重 (30%)
	double gamma = -100;   // 亮度调节值

	// 执行融合：dst = img1*alpha + img2*beta + gamma
	addWeighted(src1, alpha, src2, beta, gamma, dst);

	imshow("混合", dst);
	waitKey(0);
}*/

//亮度、对比度、饱和度
/*void main() {
	//读取一张图片，返回Mat对象
	Mat src = imread("D:/张三.jpg");

	double alpha = 0.5;
	double beta = 50;

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			//获取像素点，at方法，3通道使用Vec3b
			Vec3b vec = src.at<Vec3b>(i, j);
			int b = vec[0];
			int g = vec[1];
			int r = vec[2];

			//修改亮度和对比度公式：g(x)=αf(x)+β
			//需要使用安全转换，否则会溢出
			src.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(alpha * b + beta);
			src.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(alpha * g + beta);
			src.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(alpha * r + beta);

		}
	}

	imshow("src", src);
	waitKey(0);
}*/

/*inline int max(int a, int b) {
	return a >= b ? a : b;
}

void main(){

	int result = max(1, 2);
	cout << "result:" << result << endl;

	getchar();

}*/

/*void main() {//绘制形状和文字

	//Mat src = imread("D:/U－奥尔加玛丽初始.png");
	//创建黑色空画布
	Mat src = Mat::zeros(600, 800, CV_8UC3);

	//直线
	line(src, Point(100, 100), Point(200, 200), Scalar(255, 0, 0), 10, LINE_AA);//AA明显比8要圆润

	//矩形
	//thickness：线宽 >0 时画边框；设为 -1表示填充矩形​
	rectangle(src, Point(50, 100), Point(200, 250), Scalar(0, 255, 255));//空心
	rectangle(src, Rect(250, 100, 150, 150), Scalar(0, 255, 0), -1);//实心

	//圆形
	circle(src, Point(150, 300), 50, Scalar(0, 0, 255), 2, LINE_AA);
	circle(src, Point(350, 300), 50, Scalar(0, 255, 255), -1);//黄色填充

	//椭圆
	ellipse(src, Point(500, 200), Size(150, 80), 30, 0, 360, Scalar(255, 0, 255), 2);
	ellipse(src, Point(500, 400), Size(100, 50), 0, 0, 180, Scalar(0, 255, 255), -1);

	//多边形
	//花括号直接创建数组
	vector<Point> polyPoints = { {100,50},{200,30},{250,100},{150,150},{50,100} };
	vector<vector<Point>> contours = { polyPoints };

	polylines(src, contours, true, Scalar(0, 255, 0), 2);// 绘制多边形轮廓（绿色边框）
	fillPoly(src, contours, Scalar(255, 0, 0));// 填充多边形（蓝色内部）

	//文字
	putText(src, "Hello OpenCV", Point(400, 400), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));

	//随机画线
	RNG rng(time(NULL));//cv的随机数
	for (int i = 0; i < 100; i++)
	{
		Point p1(rng.uniform(0, src.cols), rng.uniform(0, src.rows));
		Point p2(rng.uniform(0, src.cols), rng.uniform(0, src.rows));
		line(src, p1, p2, Scalar(255, 255, 255));
	}


	imshow("src", src);
	waitKey(0);

}*/


/*void main() {//手动卷积
	Mat src = imread("D:/photo.jpg");
	imshow("photo", src);

	Mat dst(src.size(), src.type());
	dst = src.clone();

	int rows = src.rows;
	int channels = src.channels();
	int cols = src.cols * channels;

	//经典锐化卷积核
	//	0 - 1	0
	//	- 1	5 - 1
	//	0 - 1	0


		//手动卷积-使用ptr循环遍历每个像素
	for (size_t i = 1; i < rows - 1; i++)
	{
		uchar* prev = src.ptr<uchar>(i - 1); //获取第i行像素的首指针
		uchar* curr = src.ptr<uchar>(i); //获取第i行像素的首指针
		uchar* next = src.ptr<uchar>(i + 1); //获取第i+1行像素的首指针
		uchar* dst_curr = dst.ptr<uchar>(i); //获取dst第i行像素的首指针

		for (size_t j = 1; j < cols - 1; j++)
		{
			dst_curr[j] = saturate_cast<uchar>(
				-1 * prev[j] + //上
				-1 * curr[j - channels] + //左
				5 * curr[j] + //中
				-1 * curr[j + channels] + //右
				-1 * next[j]); //下
		}

	}


	//这个写法明显不如上面的优雅
	//for (size_t i = 1; i < rows - 1; i++)
	//{
	//	for (size_t j = 1; j < src.cols - 1; j++)
	//	{
	//		Vec3b top = src.at<Vec3b>(i - 1, j);
	//		Vec3b bottom = src.at<Vec3b>(i + 1, j);
	//		Vec3b center = src.at<Vec3b>(i, j);
	//		Vec3b left = src.at<Vec3b>(i, j - 1);
	//		Vec3b right = src.at<Vec3b>(i, j + 1);
	//		//Vec3b dst_curr = dst.at<Vec3b>(i, j);//不能用这个值去赋值，已经是另一个地址了。

	//		dst.at<Vec3b>(i, j)[0] = saturate_cast<uchar>(
	//			-1 * top[0] + //上
	//			-1 * left[0] + //左
	//			5 * center[0] + //中
	//			-1 * right[0] + //右
	//			-1 * bottom[0]); //下
	//		dst.at<Vec3b>(i, j)[1] = saturate_cast<uchar>(
	//			-1 * top[1] + //上
	//			-1 * left[1] + //左
	//			5 * center[1] + //中
	//			-1 * right[1] + //右
	//			-1 * bottom[1]); //下
	//		dst.at<Vec3b>(i, j)[2] = saturate_cast<uchar>(
	//			-1 * top[2] + //上
	//			-1 * left[2] + //左
	//			5 * center[2] + //中
	//			-1 * right[2] + //右
	//			-1 * bottom[2]); //下
	//	}

	//}

	imshow("卷积结果", dst);
	waitKey(0);
}*/

//均值滤波
/*void main() {
	Mat src = imread("D:/U－奥尔加玛丽初始.png");
	if (src.empty())
	{
		cout << "opencv read errlr!" << endl;
		waitKey(0);
		return;
	}

	imshow("src", src);

	Mat dst;

	blur(src, dst, Size(3,3));

	imshow("blur 3*3", dst);

	Mat dst2;

	blur(src, dst2, Size(5, 5));

	imshow("blur 5*5", dst2);

	waitKey(0);


}*/

/*void main() {//高斯模糊
	Mat src = imread("D:/U－奥尔加玛丽初始.png");
	if (src.empty())
	{
		cout << "opencv read errlr!" << endl;
		waitKey(0);
		return;
	}
	imshow("src", src);

	Mat dst;
	GaussianBlur(src, dst, Size(3, 3),0);
	imshow("GaussianBlur 3*3", dst);

	Mat dst2;
	GaussianBlur(src, dst2, Size(3, 3), 10);
	imshow("GaussianBlur 5*5", dst2);

	waitKey(0);
}*/

/*void main() {//中值滤波
	Mat src = imread("D:/jyzs.png");
	if (src.empty())
	{
		cout << "opencv read errlr!" << endl;
		waitKey(0);
		return;
	}
	imshow("src", src);

	Mat dst;
	medianBlur(src, dst, 3);
	imshow("medianBlur 3", dst);

	Mat dst2;
	medianBlur(src, dst2, 5);
	imshow("medianBlur 5", dst2);

	waitKey(0);
}*/


int g_d = 15;
int g_sigmaColor = 20;
int g_sigmaSpace = 50;

Mat src;
Mat dst;

/*
void on_Trackbar(int, void*) {
	bilateralFilter(src, dst, g_d, g_sigmaColor, g_sigmaSpace);
	imshow("output", dst);
}*/


/*
void main() {//双边滤波
	src = imread("D:/641.webp");
	if (src.empty())
	{
		cout << "opencv read errlr!" << endl;
		waitKey(0);
		return;
	}
	imshow("src", src);

	bilateralFilter(src, dst, g_d, g_sigmaColor, g_sigmaSpace);

	namedWindow("output");//新建窗口

	createTrackbar("核直径", "output", &g_d, 50, on_Trackbar);
	createTrackbar("颜色空间方差", "output", &g_sigmaColor, 100, on_Trackbar);
	createTrackbar("坐标空间方差", "output", &g_sigmaSpace, 100, on_Trackbar);

	imshow("output", dst);

	//Mat dst2;
	//Mat kernel = (Mat_<int>(3, 3) <<
		//0, -1, 0,
		//-1, 5, -1,
		//0, -1, 0);

	//找补一些模糊
	//filter2D(src, dst2, src.depth(), kernel);
	//imshow("锐化", dst2);

	waitKey(0);
}*/


int element_size = 1;
int max_size = 21;

void on_dilate_trackbar(int pos, void* userdata) {
	int size = element_size * 2 + 1;
	//获取自定义核
	Mat kernel = getStructuringElement(MORPH_RECT, Size(size, size));
	//膨胀操作
	dilate(src, dst, kernel);
	imshow("膨胀后", dst);

}

/*
void main() {//膨胀
	src = imread("D:/Ndk/black_white.jpeg");
	if (src.empty())
	{
		cout << "opencv read errlr!" << endl;
		waitKey(0);
		return;
	}
	imshow("src", src);

	namedWindow("膨胀后");//新建窗口

	//获取自定义核
	Mat kernel = getStructuringElement(MORPH_RECT, Size(element_size, element_size));
	//膨胀操作
	dilate(src, dst, kernel);
	imshow("膨胀后", dst);

	createTrackbar("核直径", "膨胀后", &element_size, 50, on_dilate_trackbar);

	waitKey(0);
}*/

/*
void on_erode_trackbar(int pos, void* userdata) {
	int size = element_size * 2 + 1;
	//获取自定义核
	Mat kernel = getStructuringElement(MORPH_RECT, Size(size, size));
	//腐蚀操作
	erode(src, dst, kernel);
	imshow("腐蚀后", dst);

}*/

/*
void main() {//腐蚀
	src = imread("D:/Ndk/white_black.png");
	if (src.empty())
	{
		cout << "opencv read errlr!" << endl;
		waitKey(0);
		return;
	}
	imshow("src", src);

	namedWindow("腐蚀后");//新建窗口

	//获取自定义核
	Mat kernel = getStructuringElement(MORPH_RECT, Size(element_size, element_size));
	//腐蚀
	erode(src, dst, kernel);
	imshow("腐蚀后", dst);

	createTrackbar("核直径", "腐蚀后", &element_size, 50, on_erode_trackbar);

	waitKey(0);
}
*/

/*
* 开运算
void main() {
	src = imread("D:/Ndk/white_spot.jpg");
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	//CV_WINDOW_NORMAL：可使用鼠标拖动边缘改变窗口大小
	namedWindow("src", CV_WINDOW_NORMAL);
	//设置窗口大小
	resizeWindow("src", 300, 300);
	imshow("src", src);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	morphologyEx(src, dst, CV_MOP_OPEN, kernel);//开运算

	namedWindow("dst", CV_WINDOW_NORMAL);
	resizeWindow("dst", 300, 300);
	imshow("dst", dst);

	waitKey(0);
}
*/
/*
void main() {//闭运算
	src = imread("D:/Ndk/black_spot.png");
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	//CV_WINDOW_NORMAL：可使用鼠标拖动边缘改变窗口大小
	namedWindow("src", CV_WINDOW_NORMAL);
	//设置窗口大小
	resizeWindow("src", 300, 300);
	imshow("src", src);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(30,30));
	morphologyEx(src, dst, CV_MOP_CLOSE, kernel);//闭运算

	namedWindow("dst", CV_WINDOW_NORMAL);
	resizeWindow("dst", 300, 300);
	imshow("dst", dst);

	waitKey(0);
}
*/

/*
void main() {//梯度
	src = imread("D:/Ndk/black_spot.png");
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	//CV_WINDOW_NORMAL：可使用鼠标拖动边缘改变窗口大小
	namedWindow("src", CV_WINDOW_NORMAL);
	//设置窗口大小
	resizeWindow("src", 300, 300);
	imshow("src", src);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));
	morphologyEx(src, dst, CV_MOP_GRADIENT, kernel);//梯度

	namedWindow("dst", CV_WINDOW_NORMAL);
	resizeWindow("dst", 300, 300);
	imshow("dst", dst);

	waitKey(0);
}*/

/*
void main() {//顶帽
	src = imread("D:/Ndk/black_spot.png");
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	//CV_WINDOW_NORMAL：可使用鼠标拖动边缘改变窗口大小
	namedWindow("src", CV_WINDOW_NORMAL);
	//设置窗口大小
	resizeWindow("src", 300, 300);
	imshow("src", src);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));


	Mat open;
	morphologyEx(src, open, CV_MOP_OPEN, kernel);
	namedWindow("open", CV_WINDOW_NORMAL);
	resizeWindow("open", 300, 300);
	imshow("open", open);


	morphologyEx(src, dst, CV_MOP_TOPHAT, kernel);//

	namedWindow("dst", CV_WINDOW_NORMAL);
	resizeWindow("dst", 300, 300);
	imshow("dst", dst);

	waitKey(0);
}*/

/*void main() {//黑帽
	src = imread("D:/Ndk/black_spot.png");
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	//CV_WINDOW_NORMAL：可使用鼠标拖动边缘改变窗口大小
	namedWindow("src", CV_WINDOW_NORMAL);
	//设置窗口大小
	resizeWindow("src", 300, 300);
	imshow("src", src);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(15, 15));


	Mat close;
	morphologyEx(src, close, CV_MOP_CLOSE, kernel);
	namedWindow("close", CV_WINDOW_NORMAL);
	resizeWindow("close", 300, 300);
	imshow("close", close);


	morphologyEx(src, dst, CV_MOP_BLACKHAT, kernel);//

	namedWindow("dst", CV_WINDOW_NORMAL);
	resizeWindow("dst", 300, 300);
	imshow("dst", dst);

	waitKey(0);
}*/


/*
void main() {//验证码去除影响元素
	src = imread("yzm.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//灰度图
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	imshow("gray", gray);
	imshow("~gray", ~gray);//~取反，gray=255-gray


	//二值化
	Mat binary;
	adaptiveThreshold(~gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 0);
	imshow("binary", binary);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(7, 7));

	//先腐蚀，去掉干扰
	erode(binary, dst, kernel);

	//恢复一些轮廓
	dilate(dst, dst, kernel);

	bitwise_not(dst, dst);//取反，因为上面做二值化的时候用的是取反的灰度图，这里转回去。
	imshow("dst", dst);

	waitKey(0);
}*/

/*
void main() {//找水平或垂直线段
	src = imread("line.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//灰度图
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	imshow("gray", gray);
	imshow("~gray", ~gray);//~取反，gray=255-gray


	//二值化
	Mat binary;
	adaptiveThreshold(~gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 0);
	imshow("binary", binary);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(src.cols, 1));//水平
	//Mat kernel = getStructuringElement(MORPH_RECT, Size(1, src.rows/8));//垂直

	//去掉水平外的线条
	erode(binary, dst, kernel);

	////恢复一些轮廓
	dilate(dst, dst, kernel);

	bitwise_not(dst, dst);//取反，因为上面做二值化的时候用的是取反的灰度图，这里转回去。
	imshow("dst", dst);

	waitKey(0);
}*/

/*void main() {//上采样和降采样
	src = imread("U－奥尔加玛丽初始.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	//imshow("src", src);

	//上采样
	pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
	imwrite("U-up.png",dst);

	//降采样
	pyrDown(src, dst, Size(src.cols / 2, src.rows / 2));
	imwrite("U-down.png", dst);


	waitKey(0);
}*/


/*
void main() {//自定义卷积核实现均值模糊
	src = imread("U－奥尔加玛丽初始.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	int size = 3;
	//均值模糊
	Mat dst1;
	blur(src, dst1, Size(size, size));
	imshow("blur", dst1);

	//自己写卷积核实现均值模糊
	Mat dst2;
	//类型里虽然写了float，但是1/9是整数除法，赋值之前已经是0了。
	//Mat kernel = (cv::Mat_<float>(size, size) << 1 / 9, 1 / 9, 1 / 9, 1 / 9, 1 / 9, 1 / 9, 1 / 9, 1 / 9, 1 / 9);
	//改为浮点数除法即可，这里使用简化写法1.f
	//Mat kernel = (Mat_<int>(size, size) << 1.f / 9, 1.f / 9, 1.f / 9, 1.f / 9, 1.f / 9, 1.f / 9, 1.f / 9, 1.f / 9, 1.f / 9);
	//初始化全是1的滤波器核
	//Mat kernel = Mat::ones(Size(size, size), CV_32F) / (size * size);
	//使用矩阵的初始化方法
	//CV_32F表示32位的浮点数
	Mat kernel(size, size, CV_32F, Scalar(1.f / (size * size)));

	cout << kernel << endl;
	filter2D(src, dst2, src.depth(), kernel);
	imshow("filter", dst2);

	waitKey(0);
}
*/


/*
void main() {//二值化
	src = imread("U－奥尔加玛丽初始.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);

	threshold(gray, dst, 100, 255, THRESH_TRUNC);
	imshow("dst", dst);

	waitKey(0);
}*/

/*
void main() {//边缘检测-Sobel算子，Scharr算子
	src = imread("D:\\Ndk\\yhk.jpg");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//先降噪
	Mat gaussian;
	GaussianBlur(src, gaussian, Size(3, 3), 0);

	//转灰度图
	Mat gray;
	cvtColor(gaussian, gray, CV_BGR2GRAY);
	imshow("gray", gray);

	//sobel边缘检测
	Mat mat_x;
	Mat mat_y;

	//Mat sobel_x = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	//Mat sobel_y = (Mat_<int>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
	//filter2D(gray, mat_x, src.depth(), sobel_x);
	//filter2D(gray, mat_y, src.depth(), sobel_y);

	//自己写算子调滤波效果还是不如opencv已经封装好的方法
	//depth参数应该使用更高的精度
	//Sobel(gray, mat_x, CV_32F, 1, 0, 3);
	//Sobel(gray, mat_y, CV_32F, 0, 1, 3);
	////使用Sobel方法需要将梯度值转为绝对值
	//convertScaleAbs(mat_x, mat_x);
	//convertScaleAbs(mat_y, mat_y);


	//Sobel的优化版本，精度更高
	Scharr(gray, mat_x, CV_64F, 1, 0);
	Scharr(gray, mat_y, CV_64F, 0, 1);
	//需要转为绝对值
	convertScaleAbs(mat_x, mat_x);
	convertScaleAbs(mat_y, mat_y);


	imshow("sobel_x", mat_x);
	imshow("sobel_y", mat_y);

	//将x、y方向上的边缘合成
	addWeighted(mat_x, 1, mat_y, 1, 0,dst);

	//手写合成，将像素值相加，效果跟上面差不多
	//Mat dst(gray.size(), gray.type());
	//int width = src.cols;
	//int height = src.rows;
	//for (int i = 0; i < height; i++)
	//{
		//for (int j=0;j<width;j++)
		//{
			//int x = mat_x.at<uchar>(i, j);
			//int y = mat_y.at<uchar>(i, j);
			//dst.at<uchar>(i, j) = saturate_cast<uchar>(x + y);
		//}
	//}

	imshow("dst", dst);

	waitKey(0);
}*/

/*
void main() {//边缘检测-lpls算子
	src = imread("D:\\Ndk\\yhk.jpg");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//先降噪
	Mat gaussian;
	GaussianBlur(src, gaussian, Size(3, 3), 0);

	//转灰度图
	Mat gray;
	cvtColor(gaussian, gray, CV_BGR2GRAY);
	imshow("gray", gray);

	Mat lpls;
	Laplacian(gray, lpls, gray.depth(), 5);
	//使用更高精度需要转为绝对值
	//convertScaleAbs(lpls, lpls);
	imshow("lpls", lpls);

	threshold(lpls, dst, 0, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("dst", dst);

	waitKey(0);
}*/


/*
void main() {//边缘检测-canny
	src = imread("D:\\Ndk\\yhk.jpg");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//canny方法都做了些什么？
	//1. 高斯降噪
	//2. 转灰度
	//3. 计算梯度 Sobel/Scharr
	//4. 非最大信号抑制
	//5. 高低阈值输出二值图像
	//在threshold1~threshold2之间，取最大值255，否则取0；尽量1:2或1:3；像30~60，30~90，50~100，50~150
	//L2gradient  true：使用平方相加再开根号的运算，慢一点，精度高；false：使用绝对值相加的方式，快，近似值；

	Canny(src, dst, 50, 150);
	imshow("dst", dst);

	waitKey(0);
}
*/



/*
void main() {//霍夫直线检测
	src = imread("hough.jpg");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	GaussianBlur(gray, gray, Size(5, 5), 0);

	Mat canny;
	Canny(src, canny, 100, 200);
	imshow("canny", canny);

	vector<Vec4f> lines;
	HoughLinesP(canny, lines, 1.0, CV_PI / 180, 100, 30, 50);

	for (int i = 0; i < lines.size(); i++)
	{
		Vec4f line = lines[i];
		cv::line(src, Point(line[0], line[1]), Point(line[2], line[3]), Scalar(0, 255, 0));
	}


	imshow("dst", src);

	waitKey(0);
}
*/


/*
void main() {//霍夫圆检测
	src = imread("houghCircle.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	Mat gray, blurImg;
	cvtColor(src, gray, CV_BGR2GRAY);
	GaussianBlur(gray, blurImg, Size(5, 5), 0);


	//圆心，半径，需要3个值
	vector<Vec3f> circles;

	HoughCircles(blurImg, circles, HOUGH_GRADIENT,1,10,100,50,5,20);

	for (int i=0;i<circles.size();i++)
	{
		Vec3f cc = circles[i];
		circle(src, Point(cc[0], cc[1]), cc[2], Scalar(255, 0, 0));
	}


	imshow("dst", src);

	waitKey(0);
}*/


/*
void main() {//重映射
	src = imread("U－奥尔加玛丽初始.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//水平翻转
	Mat map_x, map_y;
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			map_x.at<float>(i, j) = src.cols - j - 1;//x坐标取反
			map_y.at<float>(i, j) = i;				 //y坐标不变
		}
	}
	remap(src, dst, map_x, map_y, INTER_LINEAR);

	imshow("dst", dst);

	waitKey(0);
}*/


/*
void main() {//直方图均衡化
	src = imread("U－奥尔加玛丽初始.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//单通道直接上手
	Mat gray;
	cvtColor(src, gray, CV_BGR2GRAY);
	imshow("gray", gray);

	equalizeHist(gray, dst);
	imshow("dst", dst);

	//彩色图像需转换到YCrCb空间，仅均衡化亮度通道(Y)
	Mat ycrcb;
	cvtColor(src, ycrcb, CV_BGR2YCrCb);

	vector<Mat> channels;
	split(ycrcb, channels);//将通道分离
	equalizeHist(channels[0], channels[0]);//均衡化Y通道
	merge(channels, ycrcb);//将均衡化后的数据合并回图像
	cvtColor(ycrcb, dst,CV_YCrCb2BGR);//转为显示用的BGR图像
	imshow("dst", dst);

	waitKey(0);
}*/


void main() {//直方图均衡化
	src = imread("U－奥尔加玛丽初始.png");//只写文件名，读取当前目录下的文件
	if (src.empty())
	{
		cout << "image read error!" << endl;
		waitKey(0);
	}
	imshow("src", src);

	//1. 分离BGR通道
	vector<Mat> bgr;
	split(src, bgr);

	//显示出来的是三张灰度图
	//分离后每个通道变成了独立的单通道矩阵（每个像素只有一个值，表示该通道的亮度）
	//imshow遵循单通道矩阵→显示为灰度图，三通道矩阵→显示为彩色图
	//显示每个通道的真实颜色，需要使用三通道图（其余通道的值为0）
	//imshow("blue", bgr[0]);
	//imshow("green", bgr[1]);
	//imshow("red", bgr[2]);

	//2. 设置直方图参数
	int histSize = 256;          // 直方图bin数量，值（0-255）共256个数
	float range[] = { 0, 256 };    // 像素值范围，左闭右开，不含256
	const float* histRange = { range };//​​指针数组​​ histRange，其唯一元素指向 range数组的首地址
	bool uniform = true, accumulate = false;
	Mat b_hist, g_hist, r_hist;

	//3. 计算各通道直方图
	//const Mat* images, 一个图像矩阵，指针
	// int nimages,	图像数量，通常为1
	//const int* channels, 通道索引数组
	// InputArray mask,	掩膜（指定统计区域），Mat()表示都统计
	//OutputArray hist, 输出
	// int dims,	直方图维度（1 表示一维直方图，2 表示二维联合直方图）
	// const int* histSize,	每个维度的 bin 数量
	//const float** ranges, 统计的像素值值范围
	// bool uniform = true,		true时自动均匀分 bin；false需手动指定每个 bin 的边界
	// bool accumulate = false	true时保留上次计算结果（用于多图累积统计）
	calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	//创建直方图画布
	int hist_w = 512, hist_h = 300;//宽度设为256的2倍，高度随意
	//cvRound	将浮点数四舍五入到最接近的整数
	int bin_w = cvRound((double)hist_w / histSize);//计算每个bin的宽度
	Mat histImage(Size(hist_w, hist_h), CV_8UC3, Scalar(0, 0, 0));//黑色背景

	//归一化直方图数据到画布高度

	//InputArray      src,        // 输入矩阵（图像/数据）
	//OutputArray     dst,        // 输出矩阵
	//double          alpha = 1,  // 目标范围下限 或 范数缩放值
	//double          beta = 0,  // 目标范围上限（仅限 NORM_MINMAX）
	//int             norm_type = NORM_L2,  // 归一化类型
	//int             dtype = -1, // 输出数据类型（-1 表示与输入一致）
	//InputArray      mask = noArray()  // 掩码（可选）

	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//绘制三通道直方图（折线图形式）
	for (int i = 1; i < histSize; i++)
	{
		//i从1开始，保证不会越界
		// 起点
		// x坐标： bin_w * (i - 1) 
		// y坐标：hist_h - cvRound(b_hist.at<float>(i - 1)) openCV坐标原点在左上角，直方图需要从左下角开始画，需要处理下
		//蓝色
		line(histImage,
			Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * i, hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2);

		//绿色
		line(histImage,
			Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * i, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2);

		//红色
		line(histImage,
			Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * i, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2);
	}

	imshow("hist", histImage);
	waitKey(0);
}

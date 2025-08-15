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


void main() {//边缘检测-laps算子
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
}
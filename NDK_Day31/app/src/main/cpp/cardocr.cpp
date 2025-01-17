//
// Created by linzs on 2025-01-15.
//

#include "cardocr.h"
#include <vector>

using namespace std;

//这里就不是输入类名，要输入命名空间才能出来
int co1::find_card_area(const Mat &mat, Rect &area) {
//    imwrite("/storage/emulated/0/1.jpg", mat);

    //    1. 首先降噪（高斯模糊）
    Mat blur;
    GaussianBlur(mat, blur, Size(5, 5), BORDER_DEFAULT, BORDER_DEFAULT);
//    imwrite("/storage/emulated/0/2.jpg", blur);

//    2. 边缘梯度增强(保存图片）x,y增强
    Mat gard_x, gard_y;
    Scharr(blur, gard_x, CV_32F, 1, 0);
    Scharr(blur, gard_y, CV_32F, 0, 1);
//    增强后有可能变成负数，取绝对值
    Mat abs_gard_x, abs_gard_y;
    convertScaleAbs(gard_x, abs_gard_x);
    convertScaleAbs(gard_y, abs_gard_y);

//    imwrite("/storage/emulated/0/3.jpg", abs_gard_x);
//    imwrite("/storage/emulated/0/4.jpg", abs_gard_y);
//    合并x，y
    Mat gard;
    addWeighted(abs_gard_x, 0.5, abs_gard_y, 0.5, 0, gard);
//    写到内存卡
//直接写报错，颜色通道不支持，转一下
//E/cv::error(): OpenCV(4.10.0) Error: Assertion failed (image.channels() == 1 || image.channels() == 3 || image.channels() == 4) in imwrite_
//    Mat temp;
//    cvtColor(gard, temp, COLOR_BGR5652BGRA);
//    imwrite("/storage/emulated/0/5.jpg", gard);

//二值化，筛选轮廓
    Mat gray;
    cvtColor(gard, gray, COLOR_BGRA2GRAY);
//    imwrite("/storage/emulated/0/gray.png", gray);
    Mat binary;
    threshold(gray, binary, 40, 255, THRESH_BINARY);
//    imwrite("/storage/emulated/0/binary.jpg", binary);

    vector<vector<Point>> contours;
    //获取轮廓
    findContours(binary, contours, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); ++i) {
        Rect rect = boundingRect(contours[i]);
        //过滤轮廓
        if (rect.width > mat.cols / 2 && rect.width != mat.cols && rect.height > mat.rows / 2) {
            //银行卡区域的宽高必须大于图片的一半

            area = rect;
            break;
        }
    }

    //处理返回值
    if (area.width == 0) {
        return 1;
    }

    //释放资源 有没有动态开辟内存，有没有new对象
    //Mat数据类提供了释放函数，一般要调用
    blur.release();
    gard_x.release();
    gard_y.release();
    abs_gard_x.release();
    abs_gard_y.release();
    gard.release();
    gray.release();
    binary.release();


    return 0;
}

int co1::find_card_number_area(const Mat &mat, Rect &area) {
//    两种方式，一种是精确截取，找到右下角银联区域通过大小比例精确的截取
//粗略的截图，截取高度1/2~3/4，宽度1/12~11/12
//万一找不到，可以手动输入和修改
    area.x=mat.cols/12;
    area.y=mat.rows/2;
    area.width = mat.cols * 5 / 6;
    area.height=mat.rows/4;

    return 0;
}

int co1::find_card_numbers(const Mat &mat, std::vector<Mat> &numbers) {
    //转灰度图 彩色图信息量太大，处理起来很麻烦
    Mat gray;
    cvtColor(mat, gray, COLOR_BGRA2GRAY);

    //二值化
    //非常关键
    Mat binary;
    threshold(gray, binary, 39, 255, THRESH_BINARY);
    imwrite("/storage/emulated/0/binary.jpg", binary);

    //去掉干扰，找数字就是轮廓查询
    //查找轮廓 白色轮廓才能找到，需要把图片取反（黑色背景，白色轮廓）
    //取反 白黑->黑白
    Mat binary_not = binary.clone();
    bitwise_not(binary_not, binary_not);
    imwrite("/storage/emulated/0/binary_not.jpg", binary_not);

    vector<vector<Point>> contours;
    //获取轮廓
    findContours(binary, contours, RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    for (int i = 0; i < contours.size(); ++i) {
        Rect rect = boundingRect(contours[i]);
        //过滤轮廓
        if (rect.width > mat.cols / 2 && rect.width != mat.cols && rect.height > mat.rows / 2) {
            //银行卡区域的宽高必须大于图片的一半

            break;
        }
    }


    gray.release();
    binary.release();
    binary_not.release();
    return 0;
}

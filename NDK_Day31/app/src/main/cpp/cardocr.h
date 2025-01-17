//
// Created by linzs on 2025-01-15.
//

#ifndef NDK_DAY31_CARDOCR_H
#define NDK_DAY31_CARDOCR_H

#include <vector>
#include "opencv2/opencv.hpp"

using namespace cv;

//这里不用class
//对不同的场景做不同的处理

namespace co1 {
    /*
     * 找到银行卡区域
     * @return 是否成功 0成功，其他失败
     */
    int find_card_area(const Mat &mat, Rect &area);

    /*
     * 通过银行卡区域截取卡号区域
     * @param mat 银行卡mat
     * @param area 存放卡号区域
     * @return 0成功 其他失败
     */
    int find_card_number_area(const Mat &mat, Rect &area);


    int find_card_numbers(const Mat &mat,std::vector<Mat> &numbers);
}

/*
 * 备选方案
 */
namespace co2 {}


#endif //NDK_DAY31_CARDOCR_H

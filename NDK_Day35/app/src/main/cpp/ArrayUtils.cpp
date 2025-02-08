#include <random>
#include <iostream>
#include <stdlib.h>

using namespace std;

//
// Created by linzs on 2025-02-07.
//
//使用namespace写工具类
namespace ArrayUtil {

    //这是个指针函数，返回值是一个地址
    int *generateRandArray(int len, int low, int high) {
        int *arr = new int[len];

        //创建一个随机种子
        random_device rd;
        //使用Mersenne Twister 算法初始化一个随机数生成器
        mt19937 gen(rd());
        //创建一个在low到high中建的证书的均匀分布
        uniform_int_distribution<> dis(low, high);


        for (int i = 0; i < len; ++i) {
            arr[i] = dis(gen);
        }

        return arr;

    }

    int *createRandomArray(int len, int low, int high) {
        int *arr = new int[len];
        for (int i = 0; i < len; ++i) {
            arr[i] = rand() % (high - low) + low;
        }
        return arr;
    }
}
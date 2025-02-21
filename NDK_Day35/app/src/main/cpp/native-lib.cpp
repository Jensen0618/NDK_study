#include <jni.h>
#include <string>

#include <android/log.h>

#define TAG "Bubble"
//... 可变参数 实参需要用__VA_ARGS__表示
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__)

//直接引入cpp是不是不太好
#include "ArrayUtils.cpp"

using namespace std;

void printArray(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
        LOGD("%d", arr[i]);
    }
}


//定义函数指针
//void (*sort)(int *arr, int len);
//↑↓这两种定义方式都可以
typedef void (*sort)(int *arr, int len);

void testSortTime(char *name, void (*sort)(int *, int), int *arr, int len) {
    clock_t start = clock();
    sort(arr, len);
    clock_t end = clock();
    double t = (double) (end - start) / CLOCKS_PER_SEC;
    LOGD("%s方法耗时：%lf", name, t);

}


/*
 * 冒泡排序，复杂度n²
 * 9，5，3，2        5，3，2，9        3，2，5，9
 * 第一次循环，i=0   第二次循环，i=1    第三次循环，i=2

 * 5，9，3，2        3，5，2，9        2，3，5，9
 * 5，3，9，2        3，2，5，9
 * 5，3，2，9
 * 共用大循环3（len-1）次，4个数3次
 * 小循环次数为：
 *     3                 2                1
 * len-大循环i-1

 */
void bubbleSort(int *arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
//        LOGD("第%d次循环\n", i);
//        printArray(arr, len);
    }
}

/*
* 优化1（优化外层循环）：
* 若在某一趟排序中未发现气泡位置的交换，则说明待排序的无序区中所有气泡均满足轻者在上，重者在下的原则，
* 因此，冒泡排序过程可在此趟排序后终止。为此，在下面给出的算法中，引入一个标签flag，在每趟排序开始前，先将其置为0。
* 若排序过程中发生了交换，则将其置为1。各趟排序结束时检查flag，若未曾发生过交换则终止算法，不再进行下一趟排序。
*
*/
void bubbleSort1(int *arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        //每次遍历标志位都要先置为0，才能判断后面的元素是否发生了交换
        int flag = 0;
        for (int j = 0; j < len - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                //只要有发生了交换，flag就置为1
                flag = 1;
            }
        }
        //判断标志位是否为0，如果为0，说明后面的元素已经有序，就直接return
        if (flag == 0) {
            break;
        }
    }
}

/*
* 优化2：设置结束边界
* 记录上一次最后交换的位置，作为下一次循环的结束边界。
* 最后一次比较说明在那之后的元素都已经排好序，无需再比较，可以避免一些无意义的比较。
*/
void bubbleSort2(int *arr, int len) {
    //记录最后一次交换的位置
    int lastSwapIndex = 0;
    int end = len - 1;
    for (int i = 0; i < len - 1; ++i) {
        //每次遍历标志位都要先置为0，才能判断后面的元素是否发生了交换
        int flag = 0;
        for (int j = 0; j < end; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                //只要有发生了交换，flag就置为1
                flag = 1;
                lastSwapIndex = j;
            }
        }

        end = lastSwapIndex;
//        LOGD("第%d次循环\n", i);
//        printArray(arr, len);

        //判断标志位是否为0，如果为0，说明后面的元素已经有序，就直接return
        if (flag == 0) {
            break;
        }
    }
}

/*
 * 冒泡排序优化3:鸡尾酒排序
 * 左边一次，右边一次
 * 利好于大部分元素已经有序的场景
*/
void bubbleSort3(int *arr, int len) {
    int left = 0;
    int right = len - 1;
    //记录最后交换位置
    int lastSwapIndex = 0;
    while (left < right) {
        bool isSorted = true;
//        从左往右循环一次
        for (int i = left; i < right; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
                lastSwapIndex = i;
            }
        }
        if (isSorted) {
            break;
        }
        right = lastSwapIndex;
        //从右往左循环一次，把最小的移动到最左边
        isSorted = true;
        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                isSorted = false;
                lastSwapIndex = i;
            }
        }
        if (isSorted) {
            break;
        }
        left = lastSwapIndex;
    }
}

/*
 * 选择排序
 * 遍历找出数组中最小的数，放到最前边；再次遍历找出余下元素中最小的数，放到次前边；以此类推
 * 9，5，3，2
 * 
 */
void selectSort(int *arr, int len) {
    for (int i = 0; i < len - 1; ++i) {
        //最小元素的索引
        int min = i;
        //两两比较找到最小元素
        for (int j = i + 1; j < len; ++j) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        //将最小元素交换到前面
        swap(arr[i], arr[min]);
//        LOGD("第%d次循环\n", i);
//        printArray(arr, len);
    }
}

/*
 * 插入排序-基础版
 * 外层大循环遍历len-1遍，5个数遍历4遍，从第2个数开始
 * 内层循环从第arr[i]开始，依次和前一个数比较大小，若小则交换位置，否则跳出
 * 一遍循环下来，i之前的都是有序区，若不需要交换就表示这个i已经有序了
 */
void insertSort(int *arr, int len) {
    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0; --j) {
            if (arr[j] < arr[j - 1]) {
                swap(arr[j], arr[j - 1]);
            } else {
                break;
            }
        }
    }
}

/*
 * 插入排序-优化版
 * 外层大循环遍历len-1遍，5个数遍历4遍，从第2个数开始
 * 内层循环从第arr[i]开始，和前一个数比较大小，若小则交换位置，否则跳出
 * 一遍循环下来，i之前的都是有序区，若不需要交换就表示这个i已经有序了
 *
 * 插入排序的精髓，将要比较的元素存起来
 * 将序列前的元素和tmp比较，如果大于tmp则元素后移（赋值），跳出循环时，将存起来的值插到上个索引
 * 很像打牌整理手牌的情况
 */
void insertSort1(int *arr, int len) {
    int j;//将要插的位置
    //从第二个数开始，第一个数当作有序区域
    for (int i = 1; i < len; ++i) {
        int tmp = arr[i];//把要插的牌存起来
        //arr[i]<arr[i-1] 和前面的数做比较
        for (j = i; j > 0 && tmp < arr[j - 1]; --j) {
//            swap(arr[j], arr[j - 1]);//交换要用到3次赋值，不用它
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }
}

/**
 * 希尔排序
 * 1 2 3 4 5 6 7 8 9
 */
void shellSort(int *arr, int len) {
    //步长
    int delta = len / 2;
    int j;//插排位置
    while (delta >= 1) {
        //分组
        for (int k = 0; k < len; k += delta) {
            //1 6，2 7，3 8，4 9，5
            //每个小组做插入排序
            for (int i = k + delta; i < len; i += delta) {
                int tmp = arr[i];//把要插的牌存起来
                //arr[i]<arr[i-1] 和前面的数做比较
                for (j = i; j > 0 && tmp < arr[j - delta]; j -= delta) {
                    arr[j] = arr[j - delta];
                }
                arr[j] = tmp;
            }
        }
        delta = delta / 2;
    }

}


extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day35_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

//    int arr[4] = {9, 5, 3, 2};

    int len = 20000;
//    int len = 10;
    int *arr = ArrayUtil::generateRandArray(len, 20, 100);
//复制一份同样的数组
    int *arr2 = new int[len];
    int *arr3 = new int[len];
    int *arr4 = new int[len];
    int *arr5 = new int[len];
    int *arr6 = new int[len];
    int *arr7 = new int[len];
    int *arr8 = new int[len];
    memcpy(arr2, arr, len * sizeof(int));
    memcpy(arr3, arr, len * sizeof(int));
    memcpy(arr4, arr, len * sizeof(int));
    memcpy(arr5, arr, len * sizeof(int));
    memcpy(arr6, arr, len * sizeof(int));
    memcpy(arr7, arr, len * sizeof(int));
    memcpy(arr8, arr, len * sizeof(int));

//    printArray(arr, len);
//    printArray(arr2, len);
//    printArray(arr3, len);
//    printArray(arr4, len);
//    传入指针时，(sizeof arr) / sizeof(arr[0])就不能计算它的长度了！
//    bubbleSort(arr, (sizeof arr) / sizeof(arr[0]));
//    selectSort(arr, (sizeof arr) / sizeof(arr[0]));
//    printArray(arr, (sizeof arr) / sizeof(arr[0]));

//    bubbleSort(arr, len);

//    testSortTime("bubbleSort", bubbleSort, arr, len);
    testSortTime("selectSort", selectSort, arr2, len);
//    testSortTime("bubbleSort1优化外层循环", bubbleSort1, arr3, len);
//    testSortTime("bubbleSort2优化内存循环边界", bubbleSort2, arr4, len);
//    testSortTime("bubbleSort3鸡尾酒", bubbleSort3, arr5, len);
//    testSortTime("insertSort基础版", insertSort, arr6, len);
    testSortTime("insertSort1优化版", insertSort1, arr7, len);
    testSortTime("shellSort", shellSort, arr8, len);
//    int arr0[4] = {9, 5, 3, 2};
//    shellSort(arr0, 4);
//    printArray(arr0, 4);


//为什么呢？
//因为冒泡排序的每次小循环都可能会调用swap方法，swap相当于三次赋值
//而选择排序只在每次大循环的时候调用swap方法，时间就这样省出来了

//指向连续空间的指针，必须使用delete[]来释放
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;
    delete[] arr8;
    arr = NULL;
    arr2 = NULL;
    arr3 = NULL;
    arr4 = NULL;
    arr5 = NULL;
    arr6 = NULL;
    arr7 = NULL;
    arr8 = NULL;

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



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
    int lastSwapIndex=0;
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
        for (int i = right; i >left; i--) {
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

extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day35_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

//    int arr[4] = {9, 5, 3, 2};

    int len = 10000;
    int *arr = ArrayUtil::generateRandArray(len, 20, 100);
//复制一份同样的数组
    int *arr2 = new int[len];
    int *arr3 = new int[len];
    int *arr4 = new int[len];
    int *arr5 = new int[len];
    memcpy(arr2, arr, len * sizeof(int));
    memcpy(arr3, arr, len * sizeof(int));
    memcpy(arr4, arr, len * sizeof(int));
    memcpy(arr5, arr, len * sizeof(int));

//    printArray(arr, len);
//    printArray(arr2, len);
//    printArray(arr3, len);
//    printArray(arr4, len);
//    传入指针时，(sizeof arr) / sizeof(arr[0])就不能计算它的长度了！
//    bubbleSort(arr, (sizeof arr) / sizeof(arr[0]));
//    selectSort(arr, (sizeof arr) / sizeof(arr[0]));
//    printArray(arr, (sizeof arr) / sizeof(arr[0]));

//    bubbleSort(arr, len);

    testSortTime("bubbleSort", bubbleSort, arr, len);
    testSortTime("selectSort", selectSort, arr2, len);
    testSortTime("bubbleSort1优化外层循环", bubbleSort1, arr3, len);
    testSortTime("bubbleSort2优化内存循环边界", bubbleSort2, arr4, len);
    testSortTime("bubbleSort3鸡尾酒", bubbleSort3, arr5, len);

//    int arr0[4] = {9, 5, 3, 2};
//    bubbleSort2(arr0, 4);
//    printArray(arr0, 4);


//为什么呢？
//因为冒泡排序的每次小循环都可能会调用swap方法，swap相当于三次赋值
//而选择排序只在每次大循环的时候调用swap方法，时间就这样省出来了

//指向连续空间的指针，必须使用delete[]来释放
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;
    arr = NULL;
    arr2 = NULL;
    arr3 = NULL;
    arr4 = NULL;

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



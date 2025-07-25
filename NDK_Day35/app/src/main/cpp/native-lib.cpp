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
//    printArray(arr, len);
//    LOGD("-------------");
    //步长，分成几组
    int delta = len / 2;
    int group;//第几组
    int j;//插排位置
    int i;//每个小组的索引
    int tmp;
    while (delta >= 1) {//最终delta的结局一定是2/2=1.1/2=0
        //分组，
        for (group = 0; group < delta; group++) {
            //1 6，2 7，3 8，4 9，5
            //每个小组做插入排序
            for (i = group + delta; i < len; i += delta) {
                tmp = arr[i];//把要插的牌存起来
                //arr[i]<arr[i-1] 和前面的数做比较
                for (j = i; j > group && tmp < arr[j - delta]; j -= delta) {
                    arr[j] = arr[j - delta];
                }
                arr[j] = tmp;
//                LOGD("delta=%d,group=%d,i=%d,j=%d,tmp=%d", delta, group, i, j, tmp);
            }
        }
        delta = delta / 2;
//        printArray(arr, len);
//        LOGD("-----------");
    }

}

void shellSort1(int *A, int n) {
    int d, i, j, temp;//d：步长
    for (d = n / 2; d >= 1; d = d / 2) {
        for (i = d; i < n; i++) {//增量为i++，即各个子表交错处理
            if (A[i] < A[i - d]) {
                temp = A[i];
                for (j = i - d; j >= 0 && temp < A[j]; j -= d) {
                    A[j + d] = A[j];
                }
                A[j + d] = temp;
            }
        }
    }
//    printArray(A, n);
}

void ShellSort2(int *A, int n) {
    int i, j, k, d, temp;
    for (d = n / 2; d >= 1; d = d / 2) {//将数组分割为多个子表
        for (i = 0; i < d; i++) {//依次处理子表
            for (j = i + d; j < n; j = j + d) {//按间隔处理子表
                temp = A[j];
                k = j - d;
                while (k >= 0 && A[k] > temp) {
                    A[k + d] = A[k];
                    k = k - d;
                }
                A[k + d] = temp;
            }
        }
    }
//    printArray(A, n);
}

void _merge(int *arr, int left, int mid, int right) {
    //需要操作arr，复制一个临时数组，数组长度等于右减左+1
    int len = right - left + 1;
    int temp[len];

    //左边数组的索引
    int i = left;
    //右边数组索引
    int j = mid + 1;
    //临时数组索引
    int k = 0;
    //规定左边数组和右边数组的边界
    while (i <= mid && j <= right) {
        //比较左右哪边的小，小的放到临时数组里
//        if (arr[i] < arr[j]) {
//            temp[k++] = arr[i++];
//        } else {
//            temp[k++] = arr[j++];
//        }
        temp[k++] = arr[i] < arr[j] ? arr[i++] : arr[j++];
    }
    //判断左边的元素是否都被填入临时数组
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    //判断右边的元素是否都被填入临时数组
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    //将排好序的临时数组复制到原数组
    for (int m = left, n = 0; m <= right; m++, n++) {
        arr[m] = temp[n];
    }

}

/**
 * 归并排序 递归
 * 不断的分割数组直到只有两个元素，然后排序，然后不断完成分割剩下那部分的元素
 * @param arr 数组
 * @param left 数组索引左边界
 * @param right 数组索引右边界
 */
void _mergeSort(int *arr, int left, int right) {
    //跳出递归的标志
    if (left >= right) {
        return;
    }
    //算术运算符 >位运算符> 关系运算符 > 逻辑运算符（其中的逻辑非！运算级别很高，应排除在此外） >  赋值运算符 > 逗号运算符
    //    右移一位，相当于除以2
    //    int mid = (right + left) >> 1;
    //a+(b-a)/2=2*(a+(b-a)/2)/2=(2a+(b-a))/2=a+(b-a)/2
    int mid = left + ((right - left) >> 1); //使用这个替代(right + left) >> 1，避免证书溢出风险
    //递归排序左边的元素
    _mergeSort(arr, left, mid);
    //递归排序右边的元素
    _mergeSort(arr, mid + 1, right);
    //排序
    if (arr[mid] > arr[mid + 1]) {
        _merge(arr, left, mid, right);
    }
}

/**
 * 归并排序
 */
void mergeSort(int *arr, int len) {
    //因为要递归，所以单独写一个方法
    _mergeSort(arr, 0, len - 1);
}

void Merge(int a[], int left, int mid, int right) {
    int temp[right - left + 1];                   //临时数组用于存储排序时的数
    int i = left;                                 //分成两块 i指向左边的数字 j指向右边的数字
    int j = mid + 1;
    int k = 0;                                    //k用于存储数字到临时数组

    while (i <= mid && j <= right) {
        if (a[i] < a[j])                          //永远都是 i 和 j 指向的数进行比较
            temp[k++] = a[i++];                   //谁小，谁就先放到临时数组中
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)                             //如果左边还有数没放上去，就依次放上去
        temp[k++] = a[i++];
    while (j <= right)                           //如果是右边还有同上
        temp[k++] = a[j++];

    for (int m = left, n = 0; m <= right; m++, n++)//读取临时数组中的数
        a[m] = temp[n];
}

void Merge_Sort(int a[], int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    //递归拆分成较小规模子序列排序
    Merge_Sort(a, left, mid);
    Merge_Sort(a, mid + 1, right);
    if (a[mid] > a[mid + 1]) {
        Merge(a, left, mid, right);      //合并较小规模问题解
    }
}

void mergeSort1(int *arr, int len) {
    //因为要递归，所以单独写一个方法
    Merge_Sort(arr, 0, len - 1);
}


void _quickSort(int *arr, int low, int high) {
    if (low >= high) return;
    //定义两个哨兵
    int i = low, j = high;
    //基准数
    int base = arr[low];
    while (i < j) {
        //右边的哨兵先出发，如果发现右比基准数小的数，停下
        while (arr[j] >= base && j > i) {
            j--;
        }
        //左边的哨兵后出发，如果发现比基准数大的数，停下
        while (arr[i] <= base && i < j) {
            i++;
        }
        //交换哨兵发现的两个数
        swap(arr[i], arr[j]);
    }
    //交换基准数和尾哨兵
    swap(arr[low], arr[j]);
    _quickSort(arr, low, j - 1);
    _quickSort(arr, j + 1, high);


}


/**
 * 快速排序 基础班
 * @param arr
 * @param len
 */
void quickSort(int *arr, int len) {

    _quickSort(arr, 0, len - 1);
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_ndk_day35_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

//    int arr[4] = {9, 5, 3, 2};

//    int len = 20000;
    int len = 10;
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
//    testSortTime("selectSort", selectSort, arr2, len);
//    testSortTime("bubbleSort1优化外层循环", bubbleSort1, arr3, len);
//    testSortTime("bubbleSort2优化内存循环边界", bubbleSort2, arr4, len);
//    testSortTime("bubbleSort3鸡尾酒", bubbleSort3, arr5, len);
//    testSortTime("insertSort基础版", insertSort, arr6, len);
//    testSortTime("insertSort1优化版", insertSort1, arr7, len);//选择和插入一个量级
//    testSortTime("shellSort0", shellSort, arr5, len);
//    testSortTime("shellSort1", shellSort1, arr8, len);
//    testSortTime("shellSort2", ShellSort2, arr6, len);
    testSortTime("mergeSort0", mergeSort, arr3, len);//希尔和归并差不多一个量级
    testSortTime("quickSort", quickSort, arr4, len);//希尔和归并差不多一个量级
//    int arr0[4] = {9, 5, 3, 2};
//    mergeSort(arr0, 4);
//    Merge_Sort(arr0, 0, 3);
    printArray(arr4, len);


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



//
// Created by Linzs on 2025/1/6.
//

#ifndef NDK_DAY25_ARRAYLIST_HPP
#define NDK_DAY25_ARRAYLIST_HPP

//定义TAG之后，我们可以在LogCat通过TAG过滤出NDK打印的日志
#define TAG "NDK_STUDY"
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#include <android/log.h>


template<class E>
class ArrayList {
private:
    E *array = NULL;//数组指针
    int len = 0;//定义的数组长度
    int index = 0;//实际元素数量
public:
    ArrayList();

    ArrayList(int len);

    ~ArrayList();

    void add(E e);

    E remove(int index);

    E get(int index);

    int size();

private:
    void ensureCapacityInternal(int minCapacity);

    void grow(int capacity);
};

template<class E>
ArrayList<E>::ArrayList() {}

template<class E>
ArrayList<E>::ArrayList(int len) {
    LOGI("构造函数");
    if (len <= 0) {
        return;
    }

    this->len = len;
    this->array = (E *) malloc(sizeof(E) * len);
}

template<class E>
ArrayList<E>::~ArrayList<E>() {
    LOGI("析构函数");
    if (this->array) {
        free(this->array);
        this->array = NULL;
    }
}

template<class E>
void ArrayList<E>::add(E e) {
    ensureCapacityInternal(this->index + 1);//确保数组容量
    //这里用的后+，添加第一个元素时index=0，array[0]=e，赋值完index变了了1；
    //index是数组的实际长度
    this->array[this->index++] = e;
}

template<class E>
E ArrayList<E>::remove(int index) {
    if (index > this->index || index < 0) {
        return NULL;
    }
    //需要删除的元素
    E oldValue = this->array[index];
    //只要这个元素不是最后一位，那就通过循环把后面的元素往前移
    //index是索引，索引的最大值是比数组的长度小1的
    if (this->index - index > 1) {
        for (int i = index; i < this->index - 1; ++i) {
            this->array[i] = this->array[i + 1];
        }
    }
    //这里要把index也减1，保持长度正常
    this->array[--this->index] = NULL;
    return oldValue;


}

template<class E>
int ArrayList<E>::size() {
    return this->index;
}

template<class E>
E ArrayList<E>::get(int index) {
    return this->array[index];
}

template<class E>
void ArrayList<E>::ensureCapacityInternal(int minCapacity) {
    if (this->array == NULL) {//如果数组是空的，给一个默认值10
        minCapacity = 10;
    }
    //最小大小比定义的数组长度要大，说明不够装了，需要扩容
    if (minCapacity - this->len > 0)
        grow(minCapacity);

}

template<class E>
void ArrayList<E>::grow(int capacity) {
    //这里增加原数组一半的长度
    int newCapacity = len + (len >> 1);//右移一位相当于除2（不完全等同），比除法快

    //如果新的数组大小比实际所需大小要小，则已实际大小为准
    if (newCapacity - capacity < 0) {
        newCapacity = capacity;
    }

    //构建新的数组
    E *newArray = (E *) malloc(sizeof(E) * newCapacity);

    //拷贝数据
    if (this->array) {
        memcpy(newArray, this->array, sizeof(E) * index);
        free(this->array);
    }

    this->array = newArray;


}


#endif //NDK_DAY25_ARRAYLIST_HPP

//
// Created by linzs on 2025-03-18.
//

#ifndef NDK_DAY39_ARRAYQUEUE_HPP
#define NDK_DAY39_ARRAYQUEUE_HPP

template<class E>
class ArrayQueue {
private:
    //2的幂次
    int size = 0;
    //队列头索引
    int head = 0;
    //队列尾索引
    int tail = 0;
    //数组地址
    E *array = nullptr;
public:
    ArrayQueue();

    ArrayQueue(int size);

    ~ArrayQueue();

public:
    bool isEmpty();

    //移除头部元素
    E pop();

    //添加到尾部
    void push(E e);

    //获取头部元素（不移除）
    E peek();
};

template<class E>
ArrayQueue<E>::ArrayQueue(int size) {
    //size是可以乱传的，需要保证size是2的幂次；3->4 6->8 17->32
    int init_size=size;
    if (init_size >= 4) {

    }

}

template<class E>
ArrayQueue<E>::ArrayQueue() :ArrayQueue(4){

}


#endif //NDK_DAY39_ARRAYQUEUE_HPP

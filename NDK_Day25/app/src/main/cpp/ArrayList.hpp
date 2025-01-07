//
// Created by Linzs on 2025/1/6.
//

#ifndef NDK_DAY25_ARRAYLIST_H
#define NDK_DAY25_ARRAYLIST_H

template<class E>
class ArrayList {
private:
    E* array;//指针
    int len;//长度
    int index;//当前索引
public:
    ArrayList();
    ArrayList(int len);
    void add(E e);
    E remove(int index);
    E get(int index);
    ~ArrayList();

};


#endif //NDK_DAY25_ARRAYLIST_H

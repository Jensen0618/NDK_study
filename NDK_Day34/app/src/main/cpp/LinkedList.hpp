//
// Created by Linzs on 2025/1/28.
//

#ifndef NDK_DAY34_LINKEDLIST_HPP
#define NDK_DAY34_LINKEDLIST_HPP

#include <assert.h>

template<class E>
//struct Node<E> 这么写就会报错
//Explicit specialization of undeclared template struct 'Node'
struct Node {
    E value;
    Node<E> *next;

//public:

    Node(E value, Node<E> *next) {
        this->value = value;
        this->next = next;
    }
};

template<class E>
class LinkedList {
private:
//    头节点
    Node<E> *head = NULL;
//尾节点
    Node<E> *last = NULL;
//长度
    int len = 0;//必须初始化值，否则会是一个随机值

public:
    LinkedList();

    /**
     * 析构函数
     */
    ~LinkedList();

    /**
     * （尾巴）添加数据
     * @param e
     */
    void push(E e);

    /**
     * 根据索引使用遍历的方式找到元素
     * 数据量大的时候较耗时，可以认为时间复杂度为(O)n
     * @param index 索引
     */
    Node<E> *node(int index) {
        Node<E> *h = head;
        for (int i = 0; i < index; ++i) {
            h = h->next;
        }
        return h;
    }

    int size();

    E get(int index);

    void insert(int index, E e);

    void remove(int index);

};

template<class E>
void LinkedList<E>::remove(int index) {
//    将索引的前一个指针的next指向下一个指针
//    删除索引的指针
    assert(index >= 0 && index < len && len > 0);
//    需要删除的元素
    if (index == 0) {//移除头指针
        Node<E> *h = head;
        head = head->next;
        delete (h);
    } else {
        Node<E> *pre_node = node(index - 1);
        Node<E> *cur_node = pre_node->next;
        pre_node->next = cur_node->next;
        delete (cur_node);
    }
    len--;
}

template<class E>
void LinkedList<E>::insert(int index, E e) {
    assert(index <= len && index >= 0);
    Node<E> *new_node = new Node<E>(e, NULL);
    if (index == 0) {//替换头指针
//        1. 复制一份旧的头指针
        Node<E> *temp_node = head;
//        2. 插入新的头指针
        head = new_node;
//        3. 将新的头指针的next指向旧的头指针
        head->next = temp_node;
    } else {
//        1. 获取索引的前一个元素
        Node<E> *prev = node(index - 1);
        Node<E> *temp_node = prev;
        new_node->next = temp_node->next;
        prev->next = new_node;
    }
    this->len++;
}

template<class E>
E LinkedList<E>::get(int index) {
    assert(index >= 0 && index < len);
    return node(index)->value;
}

template<class E>
int LinkedList<E>::size() {
    return this->len;
}

template<class E>
LinkedList<E>::LinkedList() = default;

template<class E>
LinkedList<E>::~LinkedList() = default;

template<class E>
void LinkedList<E>::push(E e) {
    Node<E> *new_node = new Node<E>(e, NULL);
    if (head) {
        //找到尾节点，尾节点的next为NULL
//        Node<E> *h = head;
//        while (h) {
//            if (h->next == NULL) {
//                break;
//            }
//            h = h->next;
//        }
//        h->next = new_node;

//        Node<E> *last = node(len - 1);//时间复杂度高，使用尾节点优化
        last->next = new_node;
/* C++操作的是内存，
 * 每次 Node<E> *new_node = new Node<E>(e, NULL);都会开辟一个内存地址，
 * last->next = new_node;这句代码的含义是last所指向地址的next属性指向的地址赋值为new_node的地址
 * 这个地方next链已经形成。
 * 下面的last = new_node;表示将last指向new_node的地址，更新了
 */
//当前尾节点的next指向new_node
    } else {
        this->head = new_node;
    }
//    更新尾节点
    last = new_node;
    this->len++;
}


#endif //NDK_DAY34_LINKEDLIST_HPP

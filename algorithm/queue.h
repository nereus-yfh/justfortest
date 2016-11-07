#ifndef _STACK_H_
#define _STACK_H_

#define SUCC 0
#define FAIL -1

#include <cstdlib>
template <class node_type>
class Queue {
public:
    Queue(size_t n) : __head(0), __tail(0), __size(n){
        __node_buf = new node_type[__size];
    }
    ~Queue(){delete __node_buf;}

public:
    int push(const node_type node);
    int pop(node_type *node);
    int size();
    bool empty();

private:
    int __head;
    int __tail;
    int __size;
    node_type *__node_buf;
};


template <class node_type>
int Queue<node_type>::push (const node_type node) {
    if ((__head+1)%__size == __tail) {
        return FAIL;
    }
    __head = (__head+1) % __size;
    __node_buf[__head] = node;
    return SUCC;
}

template <class node_type>
int Queue<node_type>::pop (node_type *node) {
    if (__head == __tail) {
        return FAIL;
    }
    __tail = (__tail+1) % __size;
    *node = __node_buf[__tail];
    return SUCC;
}

template <class node_type>
int Queue<node_type>::size() {
    return __size;
}

template <class node_type>
bool Queue<node_type>::empty() {
    return __head == __tail;
}
#endif

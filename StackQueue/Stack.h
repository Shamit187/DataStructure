//
// Created by User on 3/24/2021.
//

#ifndef STACK_QUEUE_STACK_H
#define STACK_QUEUE_STACK_H
#include "DynamicArray.h"

template<typename T>
class Stack{

private:
    DynamicArray<T> data;

public:
    Stack()
    :data(){
    }

    void push(T& element){
        data.add(element);
    }

    T seeTop(){
        if(data.length() == 0){
            throw std::out_of_range("Out of range");
        }
        return data[data.length() - 1];
    }

    void pop(){
        if(data.length() == 0){
            throw std::out_of_range("Out of range");
        }
        unsigned index = data.length() - 1;
        data.removeAt(index);
    }

    unsigned length(){
        return data.length();
    }

    friend std::ostream& operator<<(std::ostream& os,const Stack<T>& obj){
        os << obj.data;
        return os;
    }

    bool isEmpty(){
        return (data.length() == 0);
    }
};

#endif //STACK_QUEUE_STACK_H

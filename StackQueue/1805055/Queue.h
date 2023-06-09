//
// Created by User on 3/25/2021.
//

#ifndef EXPRESSIONEVALUATION_OFFLINE3__QUEUE_H
#define EXPRESSIONEVALUATION_OFFLINE3__QUEUE_H

#include "LinkedList.h"

template<typename T>
class Queue{
private:
    LinkedList<T> data;

public:
    Queue()
    :data(){

    }

    void enqueue(T element){
        data.add(element);
    }

    void dequeue(){
        data.removeAt(0);
    }

    T seeFront(){
        return data[0];
    }

    bool isEmpty(){
        return (data.length() == 0);
    }

    friend std::ostream& operator<<(std::ostream& os,const Queue<T>& obj){
        os << obj.data;
        return os;
    }
};


#endif //EXPRESSIONEVALUATION_OFFLINE3__QUEUE_H

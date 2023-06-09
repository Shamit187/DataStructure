//
// Created by User on 3/14/2021.
//

#pragma once
#include <iostream>
#include <stdexcept>

template <typename T>
struct doubleLinkedNode{
    T value;
    doubleLinkedNode<T>* prevNode;
    doubleLinkedNode<T>* nextNode;
};

template <typename T>
class LinkedList {

private:
    doubleLinkedNode<T>* startNode;
    doubleLinkedNode<T>* endNode;
    unsigned int len;

public:

    class iterator{
    private:
        doubleLinkedNode<T>* pointer;

    public:
        //constructor
        iterator(doubleLinkedNode<T>* ptr)
            :pointer(ptr){
        }

        iterator(const iterator& obj){
            pointer = obj.pointer;
        }

        //equal
        bool operator==(const iterator& rhs) {
            return pointer == rhs.pointer;
        }

        //not equal
        bool operator!=(const iterator& rhs) {
            return pointer != rhs.pointer;
        }

        //post-increment
        iterator operator++() {
            if(pointer->nextNode == nullptr){
                throw std::out_of_range("Out of bound");
            }
            iterator i = *this;
            pointer = pointer->nextNode;
            return i;
        }

        //pre-increment
        iterator operator++(int junk) {
            if(pointer->nextNode == nullptr){
                throw std::out_of_range("Out of bound");
            }
            pointer = pointer->nextNode;
            return *this;
        }

        //post-decrement
        iterator operator--() {
            if(pointer->prevNode == nullptr){
                throw std::out_of_range("Out of bound");
            }
            iterator i = *this;
            pointer = pointer->prevNode;
            return i;
        }

        //pre-decrement
        iterator operator--(int junk) {
            if(pointer->prevNode == nullptr){
                throw std::out_of_range("Out of bound");
            }
            pointer = pointer->prevNode;
            return *this;
        }

        //return the value of the data
        T& operator*() {
            return pointer->value;
        }

        //return the address of the data
        doubleLinkedNode<T>* operator->() {
            return pointer;
        }

        //destructor
        ~iterator()= default;
    };

    //constructors
    LinkedList();
    LinkedList(const LinkedList<T>& obj);

    //destructors
    ~LinkedList();

    //getter
    unsigned int length();
    T getElement(unsigned int index);

    //adder
    bool add(T element);
    bool add(T element, unsigned int index);

    //remover
    bool remove(T element);
    bool removeAt(unsigned int index);

    iterator begin(){
        return iterator(startNode);
    }
    iterator end(){
        return iterator(endNode);
    }
    iterator at(unsigned int index){
        iterator iter = begin();
        for(int i = 0; i < index; i++){
            iter++;
        }
        return iter;
    }

    //overloads
    friend std::ostream& operator<<(std::ostream& os,const LinkedList<T>& obj){
        if(obj.len == 0){
            os << "No data available" << std::endl;
            return os;
        }
        os << " ";
        doubleLinkedNode<T>* currentNode = obj.startNode;
        while(currentNode != obj.endNode){
            os << currentNode->value << " ";
            currentNode = currentNode->nextNode;
        }
        os << currentNode->value << std::endl;
        return os;
    }
    T& operator[] (unsigned int index);
};


template<typename T>
LinkedList<T>::LinkedList()
        :len(0), startNode(nullptr), endNode(nullptr){
} //done

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& obj)
        :len(0), startNode(nullptr), endNode(nullptr){
    if(obj.len == 0){
        return;
    }
    doubleLinkedNode<T>* currentNode = obj.startNode;
    while(currentNode != obj.endNode){
        add(currentNode->value);
        currentNode = currentNode->nextNode;
    }
    add(currentNode->value);
    return;
} //done

template<typename T>
LinkedList<T>::~LinkedList() {
    if(len == 0){
        return;
    }
    doubleLinkedNode<T>* currentNode = startNode;
    doubleLinkedNode<T>* rem;
    while(currentNode != endNode){
        rem = currentNode->nextNode;
        delete currentNode;
        currentNode = rem;
    }
    delete currentNode;
} //done

template<typename T>
unsigned int LinkedList<T>::length() {
    return len;
} //done

template<typename T>
T LinkedList<T>::getElement(unsigned int index) {
    if(index >= len){
        throw std::out_of_range("Out of bound");
    }
    iterator iter = begin();
    unsigned int i = 0;
    while(i < index){
        iter++;
        i++;
    }
    return *iter;
} //done

template<typename T>
bool LinkedList<T>::add(T element) {
    doubleLinkedNode<T>* newElement;
    if((newElement = new doubleLinkedNode<T>) == nullptr){
        return false;
    }
    if(len == 0){
        startNode = newElement;
    }else{
        endNode->nextNode = newElement;
    }
    newElement->prevNode = endNode;
    newElement->nextNode = nullptr;
    newElement->value = element;
    endNode = newElement;
    len++;
    return true;
} //done

template<typename T>
bool LinkedList<T>::add(T element, unsigned int index) {
    if(index > len){
        throw std::out_of_range("Out of bound");
    }
    if(index == len || len == 0){
        return add(element);
    }
    doubleLinkedNode<T>* newElement;
    doubleLinkedNode<T>* currentNode = startNode;
    doubleLinkedNode<T>* rem;
    if((newElement = new doubleLinkedNode<T>) == nullptr){
        return false;
    }
    unsigned int i = 0;
    while(i < index){
        i++;
        currentNode = startNode->nextNode;
    }
    rem = currentNode->nextNode;
    currentNode->nextNode = newElement;
    newElement->value = element;
    newElement->prevNode = currentNode;
    newElement->nextNode = rem;
    rem->prevNode = newElement;
    len++;
    return true;
}

template<typename T>
bool LinkedList<T>::remove(T element) {
    doubleLinkedNode<T>* currentNode = startNode;
    unsigned int elementDeleted = 0;
    for(int i = 0; i < len; i++){
        if(currentNode->value == element){
            doubleLinkedNode<T>* prevNode = currentNode->prevNode;
            doubleLinkedNode<T>* nextNode = currentNode->nextNode;
            delete currentNode;
            elementDeleted++;
            if(prevNode == nullptr){
                startNode = nextNode;
            }else{
                prevNode->nextNode = nextNode;
            }
            if(nextNode == nullptr){
                endNode = prevNode;
                break;
            }
            nextNode->prevNode = prevNode;
            currentNode = nextNode;
        } else{
            currentNode = currentNode->nextNode;
        }
    }
    len -= elementDeleted;
    return true;
}

template<typename T>
bool LinkedList<T>::removeAt(unsigned int index) {
    if(index >= len){
        throw std::out_of_range("Out of bound");
    }
    if(index == 0 && len == 1){
        delete startNode;
        startNode = nullptr;
        endNode = nullptr;
        len = 0;
        return true;
    }
    if(index == len - 1){
        doubleLinkedNode<T>* remNode = endNode;
        endNode = endNode->prevNode;
        delete remNode;
        endNode->nextNode = nullptr;
        len--;
        return true;
    }
    if(index == 0){
        doubleLinkedNode<T>* currentNode = startNode;
        doubleLinkedNode<T>* nextNode = currentNode->nextNode;
        nextNode->prevNode = nullptr;
        startNode = nextNode;
        delete currentNode;
        len--;
        return true;
    }
    doubleLinkedNode<T>* currentNode = startNode;
    for(int i = 0; i < index; i++){
        currentNode = currentNode->nextNode;
    }
    doubleLinkedNode<T>* prevNode = currentNode->prevNode;
    doubleLinkedNode<T>* nextNode = currentNode->nextNode;
    delete currentNode;
    prevNode->nextNode = nextNode;
    nextNode->prevNode = prevNode;
    len--;
    return true;
}

template<typename T>
T &LinkedList<T>::operator[](unsigned int index) {
    if(index >= len){
        throw std::out_of_range("Out of bound");
    }
    iterator iter = begin();
    unsigned int i = 0;
    while(i < index){
        iter++;
        i++;
    }
    return *iter;
}

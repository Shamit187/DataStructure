//
// Created by User on 3/24/2021.
//

#ifndef STACK_QUEUE_DYNAMICARRAY_H
#define STACK_QUEUE_DYNAMICARRAY_H

#include <iostream>

template<typename T>
class DynamicArray{

private:
    T* data;
    unsigned len;
    unsigned capacity;

public:
    DynamicArray()
    :data(new T[8]), len(0), capacity(8){
    }

    DynamicArray(unsigned size)
    :data(nullptr), len(0){
        unsigned power = 1;
        while(size > power){
            power *= 2;
        }
        data = new T[power];
        len = 0;
        capacity = power;
    }

    DynamicArray(const DynamicArray<T>& obj)
    :data(new T[obj.capacity]), len(obj.len), capacity(obj.capacity){
        for(int i = 0; i < len; i++){
            data[i] = obj.data[i];
        }
    }

    ~DynamicArray(){
        delete[] data;
    }

    void add(unsigned index, T element){
        if(capacity <= len){
            T* newAllocation = new T[capacity*2];
            for(int i = 0; i <= len; i++){
                if(i == index) {
                    *(newAllocation + i) = element;
                }
                if(i < index){
                    *(newAllocation + i) = *(data + i);
                }
                else{
                    *(newAllocation + i + 1) = *(data + i);
                }
            }
            delete[] data;
            data = newAllocation;
            capacity *= 2;
            len++;
        }
        else{
            for(int i = len; i > index; i--){
                data[len] = data[len - 1];
            }
            data[index] = element;
            len++;
        }
    }

    void add(T element){
        add(len, element);
    }

    void remove(const T& element) {

        for(unsigned int i = 0; i < len; i++){
            if(*(data + i) == element){
                len--;
                for(unsigned int j = i; j <= len; j++){
                    data[j] = data[j + 1];
                }
                i--;
            }
        }

        if(capacity > len*2){
            T* newAllocation = new T[capacity/2];
            for(int i = 0; i < len; i++){
                *(newAllocation + i) = *(data + i);
            }
            delete[] data;
            data = newAllocation;
            capacity /= 2;
        }
    }

    void removeAt(unsigned index){

        len--;
        for(unsigned int j = index; j <= len; j++){
            data[j] = data[j + 1];
        }

        if(capacity > len*2){
            T* newAllocation = new T[capacity/2];
            for(int i = 0; i < len; i++){
                *(newAllocation + i) = *(data + i);
            }
            delete[] data;
            data = newAllocation;
            capacity /= 2;
        }
    }

    unsigned length(){
        return len;
    }

    unsigned getCapacity(){
        return capacity;
    }

    T& operator[](unsigned index){
        return data[index];
    }

    friend std::ostream& operator<<(std::ostream& os,const DynamicArray<T>& obj){
        os << "Data: ";
        for(int i = 0; i < obj.len; i++){
            os << obj.data[i] << " ";
        }
        return os;
    }

};

#endif //STACK_QUEUE_DYNAMICARRAY_H

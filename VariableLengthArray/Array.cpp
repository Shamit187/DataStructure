//
// Created by User on 3/9/2021.
//

#include "Array.h"

#include <utility>
#include <stdexcept>

Array::Array()
    : init_capacity(16), data(nullptr), len(0), capacity(16){

    data = new std::string[capacity];
}

Array::Array(unsigned int size)
    : init_capacity(16), data(nullptr), len(0), capacity(16) {

    unsigned int power = 1;
    while(power < size)
        power *= 2;
    data = new std::string[power];
    capacity = power;
}

Array::Array(const Array &obj)
    : init_capacity(16), data(nullptr), len(obj.len), capacity(obj.capacity) {

    data = new std::string[capacity];
    for(int i = 0; i < len; i++){
        data[i] = std::string(obj.data[i]);
    }
}

Array::Array(const std::string *array,unsigned int array_size)
    : init_capacity(16), data(nullptr), len(0), capacity(16) {

    unsigned int power = 1;
    while(power < array_size)
        power *= 2;
    data = new std::string[power];
    capacity = power;

    for(unsigned int i = 0; i < array_size; i++){
        data[i] = std::string(array[i]);
    }

    len = array_size;
}

Array::~Array() {
    delete[] data;
    len = 0;
    capacity = 0;
}

void Array::add(const std::string& element) {

    if(len >= capacity){
        auto* newDataSet = new std::string[capacity * 2];
        for(int i = 0; i < len; i++){
            *(newDataSet + i) = std::string(*(data + i));
        }
        delete[] data;
        data = newDataSet;
        capacity *= 2;
    }

    data[len++] = std::string(element);
}

void Array::add(const std::string& element, unsigned int index) {
    if(index > len){
        throw std::out_of_range("Index has to be between 0 and len of the array to add new data");
    }

    if(len >= capacity){
        auto* newDataSet = new std::string[capacity * 2];
        for(int i = 0; i < len; i++){
            *(newDataSet + i) = std::string(std::move(*(data + i)));
        }
        delete[] data;
        data = newDataSet;
        capacity *= 2;
    }

    for(unsigned int i = len++; i > index; i--){
        *(data + i) = std::string(std::move(*(data + i - 1)));
    }

    data[index] = std::string(element);
}

std::string Array::getAnElement(unsigned int index) {
    if(index >= len){
        throw std::out_of_range("Index has to be between 0 and len of the array to view data");
    }
    return data[index];
}

unsigned int Array::length() const {
    return len;
}

unsigned int Array::getCapacity() const {
    return capacity;
}

int Array::findIndex(const std::string& element) {
    for(int i = 0; i < len; i++){
        if(*(data + i) == element){
            return i;
        }
    }
    return -1;
}

Array Array::subArray(unsigned int startIndex, unsigned int endIndex) {
    if(startIndex >= endIndex || startIndex >= len || endIndex >= len){
        throw std::out_of_range("Index has to be between 0 and len of the array to get data");
    }
    Array returnValue(endIndex - startIndex + 1);
    for(unsigned int i = startIndex; i <= endIndex; i++){
        returnValue.add(data[i]);
    }
    return returnValue;
}

void Array::remove(const std::string& element) {
    for(unsigned int i = 0; i < len; i++){
        if(*(data + i) == element){
            len--;
            for(unsigned int j = i; j <= len; j++){
                data[j] = data[j + 1];
            }
            i--;
        }
    }
}

Array Array::merge(const Array& a, const Array& b) {
    unsigned int totalLen = a.len + b.len;
    Array returnValue(totalLen);
    unsigned int a_index = 0;
    unsigned int b_index = 0;
    for(unsigned int i = 0; i < totalLen; i++){
        if(a_index >= a.len){
            returnValue.add(b.data[b_index]);
            b_index++;
        }else if(b_index >= b.len || a.data[a_index].compare(b.data[b_index]) < 0){
            returnValue.add(a.data[a_index]);
            a_index++;
        }else{
            returnValue.add(b.data[b_index]);
            b_index++;
        }
    }
    return returnValue;
}

void Array::remove(unsigned int index) {
    if(index >= len){
        throw std::out_of_range("Index has to be between 0 and len of the array to delete data");
    }
    for(unsigned int j = index; j < len - 1; j++){
        data[j] = data[j+1];
    }
    len--;
}

void Array::push_back(const std::string &element) {
    add(element);
}

void Array::push_front(const std::string &element) {
    add(element,0);
}

std::string Array::pop_back() {
    std::string returnValue(data[len - 1]);
    remove(len - 1);
    return returnValue;
}

std::string Array::pop_front() {
    std::string returnValue(data[0]);
    remove(0);
    return returnValue;
}

Array Array::merge(const std::string *a, unsigned int a_len, const std::string *b, unsigned int b_len) {
    Array array_a(a, a_len);
    Array array_b(b, b_len);
    return Array(merge(array_a, array_b));
}

std::string* Array::getArray() const{
    return data;
}

bool Array::isEmpty() const {
    return (len == 0);
}


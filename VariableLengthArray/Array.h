//
// Created by User on 3/9/2021.
//
#pragma once
#include <string>

class Array {

private:

    std::string* data;
    unsigned int len;
    unsigned int capacity;
    const unsigned int init_capacity;

public:

    //constructors
    Array();
    explicit Array(unsigned int size);
    Array(const Array& obj);
    Array(const std::string* array,unsigned int array_size);

    //destructor
    ~Array();

    //adder
    void add(const std::string& element);
    void add(const std::string& element, unsigned int index); //throws exception
    void push_back(const std::string& element);
    void push_front(const std::string& element);

    //getter
    std::string* getArray() const;
    std::string getAnElement(unsigned int index); //throws exception
    unsigned int length() const;
    unsigned int getCapacity() const;
    int findIndex(const std::string& element);
    Array subArray(unsigned int startIndex, unsigned int endIndex); //throws exception
    bool isEmpty() const;

    //remover
    void remove(const std::string& element);
    void remove(unsigned int index); //safe bound mechanism
    std::string pop_back();
    std::string pop_front();

    //special
    static Array merge(const Array& a, const Array& b);
    static Array merge(const std::string* a, unsigned int a_len, const std::string* b, unsigned int b_len);
};




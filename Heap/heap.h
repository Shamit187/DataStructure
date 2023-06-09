//
// Created by User on 4/7/2021.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <string>

class Heap{
private:
    int* data;
    unsigned len;
    unsigned capacity;

    static int parent(int x){
        x++;
        x /= 2;
        x--;
        if(x < 0)
            return -1;
        return x;
    }
    static int left(int x){
        x++;
        x = 2 * x;
        x--;
        return x;
    }
    static int right(int x){
        x++;
        x = 2 * x;
        return x;
    }

    void debug(){
        for(int i = 0; i < len; i++){
            std::cout << data[i] << " " ;
        }
        std::cout << std::endl;
    }

public:
    explicit Heap(int size)
    :len(0), capacity(size), data(new int[size]){
    }

    void insert(int value){
        if(len >= capacity) throw std::out_of_range("Capacity full. Can not store more than capacity.");
        data[len++] = value;
        int present = len - 1;
        while(parent(present) != -1 && data[parent(present)] <= data[present]){
            std::swap(data[parent(present)], data[present]);
            present = parent(present);
        }
        //debug();
    }

    unsigned size() const{
        return len;
    }

    int getMax(){
        if(len == 0) return 0;
        return data[0];
    }

    void deleteKey(){
        if(len == 0) throw std::out_of_range("No more data to delete");
        data[0] = data[--len];
        int present = 0;
        while(left(present) < len && (data[left(present)] > data[present] || ( right(present) != len && data[right(present)] > data[present]))){
            if(right(present) == len){
                //int debugLeft = data[left(present)];
                //int debugData = data[present];
                std::swap(data[left(present)], data[present]);
                present = right(present);
            }else{
                //int debugLeft = data[left(present)];
                //int debugRight = data[right(present)];
                //int debugData = data[present];
                (data[left(present)] > data[right(present)]) ?
                (present = left(present), std::swap(data[parent(present)], data[present])):
                (present = right(present), std::swap(data[parent(present)], data[present]));
            }
        }
    }
};

void heapsort(std::vector<int>& dataArray){
    int size = dataArray.size();
    Heap h(size);
    for(int i = 0; i < size; i++){
        h.insert(dataArray[i]);
    }
    for(int i = 0; i < size; i++){
        dataArray[i] = h.getMax();
        h.deleteKey();
    }
}


#endif //HEAP_HEAP_H

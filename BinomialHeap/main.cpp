#include <iostream>
#include <random>
#include <string>
#include "BHeap.h"

int random(int min, int max){
    std::random_device rand;
    std::mt19937 gen(rand());

    return min + gen() % (max - min);
}

void FindMax(BHeap& Heap){
    std::cout << "FindMax returned " << -Heap.findMin() << std::endl;
}

void ExtractMax(BHeap& Heap){
    std::cout << "ExtractMax returned " << -Heap.extractMin() << std::endl;
}

void Insert(BHeap& Heap, int value){
    std::cout << "Inserted " << value << std::endl;
    Heap.insert(-value);
}

void IncreaseKey(BHeap& Heap, int prevKey, int newKey){
    std::cout << "Increased " << prevKey << ". The updated value is " << newKey << "." << std::endl;
    Heap.decreaseKey(-prevKey, -newKey);
}

void Print(BHeap& Heap){
    std::cout << "Printing Binomial Heap..." << std::endl;
    std::cout << "--------------------------" << std::endl;
    Heap.printReverse();
    std::cout << "--------------------------" << std::endl;
}

int main() {
    /*
    BHeap Heap;

    for(int i = 0; i < 100; i++){
        Heap.insert(random(1, 9999));
    }
    for(int i = 0; i < 100; i++){
        std::cout << Heap.findMin() << " " << std::endl;
        Heap.extractMin();
    }

    Heap.insert(-7);
    Heap.insert(-12);
    Heap.insert(-19);
    Heap.insert(-5);
    Heap.insert(-16);
    Heap.insert(-6);

    Heap.printReverse();

    Heap.decreaseKey(-7,-27);
    Heap.printReverse();
    */
    BHeap Heap;
    std::string command;
    int value, value2;

    while (command != "BYE"){
        std::cin >> command;
        if(command == "INS"){
            std::cin >> value;
            Insert(Heap, value);
        }else if(command == "PRI"){
            Print(Heap);
        }else if(command == "INC"){
            std::cin >> value >> value2;
            IncreaseKey(Heap, value, value2);
        }else if(command == "FIN"){
            FindMax(Heap);
        }else if(command == "EXT"){
            ExtractMax(Heap);
        }
    }
}

#include <iostream>
#include "Array.h"

int main() {
    //constructor Test
    Array test1;
    Array test2(5);
    std::string arrayOfString[] = {"A", "Big","Dancing","Group","Of","Puppets"};
    Array test3(arrayOfString,6);

    //add Feature
    test1.add("Like");
    test1.add("My");
    test1.add("New");
    test1.add("Pair");
    test1.add("Shoes");

    test2.add("As");
    test2.add("If");
    test2.add("It");
    test2.add("Nothing");
    test2.add("was",3);
    test2.add("As");
    test2.add("As");
    test2.add("If");

    //remove Feature
    test2.remove("As");
    int index = test2.length() - 2;
    std::cout << index << std::endl;
    test2.remove(index);

    //merge Feature
    Array test4(Array::merge(test1, test3));

    //subArray Feature
    Array test5(test4.subArray(2,7));

    //getter Feature
    for(int i = 0; i < test1.length(); i++){
        std::cout << test1.getAnElement(i) << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < test2.length(); i++){
        std::cout << test2.getAnElement(i) << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < test3.length(); i++){
        std::cout << test3.getAnElement(i) << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < test4.length(); i++){
        std::cout << test4.getAnElement(i) << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < test5.length(); i++){
        std::cout << test5.getAnElement(i) << " ";
    }
    std::cout << std::endl;
    std::cout << test3.getCapacity() << std::endl;
    std::cout << test2.findIndex("If") << std::endl;
    std::cout << test2.findIndex("Everything") << std::endl;
}
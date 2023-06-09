//
// Created by User on 1/24/2022.
//

#ifndef BINOMIALHEAP_BHEAP_H
#define BINOMIALHEAP_BHEAP_H

#include <queue>
#include <stack>
#include <iostream>
#define INF 999999

struct Node {
    struct Node* parent;
    int value;
    unsigned degree;
    struct Node* sibling;
    struct Node* children;
};

class BHeap {

private:
    Node* head;
    Node* head2;

    void unionHeap();
    int factorial(int n){
        return (n==1 || n==0) ? 1: n * factorial(n - 1);
    }
    int comb(int n, int r){
        return factorial(n) / (factorial(r) * factorial(n - r));
    }
    Node* reverseChain(Node* head);

public:
    BHeap();
    void insert(int value);

    int findMin();
    int extractMin();

    ~BHeap();

    void print();
    void printReverse();

    void decreaseKey(int prevKey, int newKey);
};


























#endif //BINOMIALHEAP_BHEAP_H
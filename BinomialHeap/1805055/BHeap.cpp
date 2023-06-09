//
// Created by User on 1/24/2022.
//

#include "BHeap.h"

BHeap::BHeap()
    :head(nullptr), head2(nullptr){
}

void BHeap::unionHeap() {
    Node* h1 = head;
    Node* h2 = head2;

    head = nullptr;
    if (h1 == nullptr){
        head = h2;
        h2 = h2->sibling;
    }else if (h2 == nullptr || h1->degree < h2->degree) {
        head = h1;
        h1 = h1->sibling;
    } else {
        head = h2;
        h2 = h2->sibling;
    }

    Node* currentChain = head;

    while( h1 != nullptr && h2 != nullptr ) {
        if (h1->degree < h2->degree) {
            currentChain->sibling= h1;
            currentChain = currentChain->sibling;
            h1 = h1->sibling;
        } else {
            currentChain->sibling= h2;
            currentChain = currentChain->sibling;
            h2 = h2->sibling;
        }
    }

    if(h2 == nullptr) currentChain->sibling= h1;
    else currentChain->sibling= h2;

    //merge
    currentChain = head;
    if(currentChain == nullptr) return;
    Node* parent = nullptr;
    while (currentChain->sibling != nullptr){
        if(currentChain->degree != currentChain->sibling->degree) {
            parent = currentChain;
            currentChain = currentChain->sibling;
        }
        else{
            Node* temp = currentChain->sibling->sibling;

            h1 = (currentChain->value < currentChain->sibling->value)? currentChain : currentChain->sibling;
            h2 = (currentChain->value >= currentChain->sibling->value)? currentChain : currentChain->sibling;

            h2->sibling = h1->children;
            h1->children = h2;
            h2->parent = h1;
            h1->degree ++;

            if(parent == nullptr) head = h1;
            else parent->sibling = h1;
            h1->sibling = temp;
            currentChain = h1;
        }
        //swap with the next one if degree is greater
        if(currentChain->sibling != nullptr && currentChain->degree > currentChain->sibling->degree){
            Node* rem = currentChain;
            Node* rem2 = currentChain->sibling->sibling;
            if(currentChain == head) head = currentChain->sibling;
            currentChain = currentChain->sibling;
            currentChain->sibling = rem;
            currentChain->sibling->sibling = rem2;
        }
    }
}

void BHeap::insert(int value) {
    Node* newNode = new Node;
    newNode->parent = nullptr;
    newNode->value = value;
    newNode->degree = 0;
    newNode->sibling = nullptr;
    newNode->children = nullptr;

    head2 = newNode;
    unionHeap();
    head2 = nullptr;
}

int BHeap::findMin() {
    if(head == nullptr) return 0;

    Node* current = head;
    Node* minNode = nullptr;

    int min = INF;
    while(current != nullptr){
        if(current->value < min) {
            minNode = current;
            min = current->value;
        }
        current = current->sibling;
    }

    return  min;
}

int BHeap::extractMin() {
    if(head == nullptr) return 0;
    if(head->sibling == nullptr && head->children == nullptr){
        delete head;
        head = nullptr;
        return 0;
    }

    Node* current = head;
    Node* parent = nullptr;

    Node* minNode = nullptr;
    Node* parentMin = nullptr;
    Node* siblingMin = nullptr;

    int min = INF;
    while(current != nullptr){
        if(current->value < min){

            parentMin = parent;
            minNode = current;
            min = current->value;
            siblingMin = current->sibling;

        }
        parent = current;
        current = current->sibling;
    }

    if(parentMin == nullptr){
        head = siblingMin;
        head2 = minNode->children;
    }else if(siblingMin == nullptr){
        parentMin->sibling = nullptr;
        head2 = minNode->children;
    }else{
        parentMin->sibling = siblingMin;
        head2 = minNode->children;
    }

    head2 = reverseChain(head2);
    unionHeap();
    head2 = nullptr;
    delete minNode;
    return min;
}

BHeap::~BHeap() {
    while (head != nullptr){
        extractMin();
    }
}

void BHeap::print() {
    Node* tree = head;
    int treeNumber = 1;
    while(tree != nullptr){
        std::cout << "Binomial Tree, B" << tree->degree << std::endl;
        std::queue<Node*> q;

        q.push(tree);

        int degree = tree->degree;
        for(int i = 0; i <= degree; i++){
            std::cout << "Level " << i << " : ";
            int combination = comb(degree, i);
            for(int j = 0; j < combination; j++){
                Node* current = q.front(); q.pop();
                std::cout << current->value << " ";
                current = current->children;
                while(current != nullptr){
                    q.push(current);
                    current = current->sibling;
                }
            }
            std::cout << std::endl;
        }

        treeNumber++;
        tree = tree->sibling;
    }
}

void BHeap::printReverse() {
    Node* tree = head;
    int treeNumber = 1;
    while(tree != nullptr){
        std::cout << "Binomial Tree, B" << tree->degree << std::endl;
        std::queue<Node*> q;

        q.push(tree);

        int degree = tree->degree;
        for(int i = 0; i <= degree; i++){
            std::cout << "Level " << i << " : ";
            int combination = comb(degree, i);
            for(int j = 0; j < combination; j++){
                Node* current = q.front(); q.pop();
                std::cout << - current->value << " ";
                current = current->children;
                while(current != nullptr){
                    q.push(current);
                    current = current->sibling;
                }
            }
            std::cout << std::endl;
        }

        treeNumber++;
        tree = tree->sibling;
    }
}

void BHeap::decreaseKey(int prevKey, int newKey) {
    Node* current = head;
    Node* target = nullptr;

    std::queue<Node*> q;
    while (current != nullptr) {
        q.push(current);
        current = current->sibling;
    }

    while(!q.empty()) {
        current = q.front();
        q.pop();
        if (current->value == prevKey) {
            target = current;
            break;
        }
        current = current->children;
        while (current != nullptr) {
            q.push(current);
            current = current->sibling;
        }
    }

    if(target == nullptr) return;
    target->value = newKey;
    while(target->parent != nullptr && target->value < target->parent->value){
        int rem = target->value;
        target->value = target->parent->value;
        target->parent->value = rem;
        target = target->parent;
    }
}

Node* BHeap::reverseChain(Node* h) {
    std::stack<Node*> s;
    Node* current = h;

    if(current == nullptr) return current;
    if(current->sibling == nullptr) return current;

    while(current != nullptr){
        s.push(current);
        current = current->sibling;
    }

    h = s.top(); s.pop();
    current = h;
    while(!s.empty()){
        current->sibling = s.top(); s.pop();
        current = current->sibling;
    }

    current->sibling = nullptr;

    return h;
}












































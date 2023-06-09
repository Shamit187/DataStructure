//
// Created by User on 3/31/2021.
//

#ifndef BINARYSEARCHTREE_BST_H
#define BINARYSEARCHTREE_BST_H

//
// Created by User on 3/31/2021.
//

//Except the last 5 functions, all the other functions should run in O(h) time, where h is the height
//of the binary search tree. Here “item” means an integer.
//You can assume that all the items in the tree are distinct, i.e. there is no repetition. Each node of
//the binary search tree should have two nodes- one for left child and another for right child.

#include <iostream>
#include "DynamicArray.h"
#include <algorithm>

template<typename T>
struct BSTNode{
    T value;
    BSTNode<T>* leftNode;
    BSTNode<T>* rightNode;
    BSTNode<T>* parentNode;
};

template <typename T>
class BinarySearchTree{
private:

    BSTNode<T>* rootNode;
    unsigned size;

    void inOrderTraversalRecursion(BSTNode<T>* node, DynamicArray<T>& data){
        if(node == nullptr){
            return;
        }
        inOrderTraversalRecursion(node->leftNode, data);
        data.add(node->value);
        inOrderTraversalRecursion(node->rightNode, data);
    }

    void postOrderTraversalRecursion(BSTNode<T>* node, DynamicArray<T>& data){
        if(node == nullptr){
            return;
        }
        inOrderTraversalRecursion(node->leftNode, data);
        inOrderTraversalRecursion(node->rightNode, data);
        data.add(node->value);
    }

    void preOrderTraversalRecursion(BSTNode<T>* node, DynamicArray<T>& data){
        if(node == nullptr){
            return;
        }
        data.add(node->value);
        inOrderTraversalRecursion(node->leftNode, data);
        inOrderTraversalRecursion(node->rightNode, data);
    }

    BSTNode<T>* searchNode(T element){
        BSTNode<T>* currentNode = rootNode;
        while(currentNode != nullptr)
        {

            if(element == currentNode->value)
                return currentNode;

            else if(element < currentNode->value)
                currentNode =  currentNode->leftNode;

            else
                currentNode =  currentNode->rightNode;

        }
        return nullptr;
    }

    BSTNode<T>* getMinNode(BSTNode<T>* currentNode){
        while(currentNode->leftNode != nullptr){
            currentNode = currentNode->leftNode;
        }
        return currentNode;
    }

    BSTNode<T>* getMaxNode(BSTNode<T>* currentNode){
        while(currentNode->rightNode != nullptr){
            currentNode = currentNode->rightNode;
        }
        return currentNode;
    }

    BSTNode<T>* inOrderSuccessorNode(BSTNode<T>* elementNode){
        if(elementNode == nullptr) throw std::invalid_argument("The element is not in the tree\n");

        if(elementNode->rightNode != nullptr)
            return getMinNode(elementNode->rightNode);
        else
        {
            BSTNode<T>* parent = elementNode->parentNode;
            while(parent != nullptr && elementNode == parent->rightNode){
                elementNode = parent;
                parent = parent->parentNode;
            }

            if(parent == nullptr) throw std::invalid_argument("No successor Available");
            else return parent;
        }
    }

    BSTNode<T>* inOrderPredecessorNode(BSTNode<T>* elementNode){
        if(elementNode == nullptr) throw std::invalid_argument("The element is not in the tree\n");

        if(elementNode->leftNode != nullptr)
            return getMaxNode(elementNode->leftNode);
        else
        {
            BSTNode<T>* parent = elementNode->parentNode;
            while(parent != nullptr && elementNode == parent->rightNode){
                elementNode = parent;
                parent = parent->parentNode;
            }

            if(parent == nullptr) throw std::invalid_argument("No successor Available");
            else return parent;
        }
    }

    unsigned getHeightRecursive(BSTNode<T>* currentNode){
        if(currentNode == nullptr) return 0;
        return 1 + std::max(getHeightRecursive(currentNode->leftNode), getHeightRecursive(currentNode->rightNode));
    }

    unsigned getSizeRecursive(BSTNode<T>* currentNode){
        if(currentNode == nullptr) return 0;
        return 1 + getSizeRecursive(currentNode->leftNode) + getSizeRecursive(currentNode->rightNode);
    }

public:

    BinarySearchTree() //done
            : rootNode(nullptr), size(0){
    }


    void insertItem(T element)
    {
        //This function inserts a new item in the binary search tree.
        size++;

        auto* newNode = new BSTNode<T>;
        newNode->value = element;
        newNode->leftNode = newNode->rightNode = newNode->parentNode = nullptr;

        //boundary condition ( 0 size tree)
        if(rootNode == nullptr)
        {
            rootNode = newNode;
            return;
        }

        //base logic
        BSTNode<T>* currentNode = rootNode;
        while(true)
        {
            newNode->parentNode = currentNode;
            if(element <= currentNode->value)
            {
                if(currentNode->leftNode == nullptr)
                {
                    currentNode->leftNode = newNode;
                    break;
                }
                else
                    currentNode = currentNode->leftNode;
            }
            else
            {
                if(currentNode->rightNode == nullptr)
                {
                    currentNode->rightNode = newNode;
                    break;
                }
                else
                    currentNode = currentNode->rightNode;
            }
        }
    } //done


    bool searchItem(T element)
    {
        //This function searches for an item in the binary search tree. If the item, say
        //52, is found, the function should print “52 has been found”; otherwise the function should
        //print “52 has not been found”.

        BSTNode<T>* currentNode = searchNode(element);
        if(currentNode == nullptr) return false;
        else return true;

    } //done


    T getInOrderSuccessor(T element)
    {
        //This function returns the in-order successor of an item in the binary
        //search tree. When there is no successor, return an invalid number to indicate it.

        BSTNode<T>* elementNode = searchNode(element);
        return (inOrderSuccessorNode(elementNode))->value;
    } //done


    T getInOrderPredecessor(T element)
    {
        //This function returns the in-order predecessor of an item in the
        //binary search tree. When there is no predecessor, return an invalid number to indicate it.
        BSTNode<T>* elementNode = searchNode(element);
        return (inOrderPredecessorNode(elementNode))->value;
    } //done


    void deleteItem(T element)
    {
        //The function will delete an existing item from the binary search tree. You
        //    must re-structure the tree after deletion according to the idea given in class. In case of
        //    deletion of a node where both of its children exist, you must choose the next largest node
        //    in the tree for replacement. If the item is not in the tree, do nothing.

        BSTNode<T>* nodeToDelete = searchNode(element);
        size--;

        //3 cases
        //case 1: no child node
        if(nodeToDelete->rightNode == nullptr && nodeToDelete->leftNode == nullptr){
            BSTNode<T>* parent = nodeToDelete->parentNode;

            if(parent == nullptr) {
                rootNode = nullptr;
                delete nodeToDelete;
                return;
            }


            delete nodeToDelete;
            if(element <= parent->value) parent->leftNode = nullptr;
            else parent->rightNode = nullptr;

            return;
        }

            //case 2: one child node
        else if(nodeToDelete->rightNode == nullptr || nodeToDelete->leftNode == nullptr){
            BSTNode<T>* parent = nodeToDelete->parentNode;
            BSTNode<T>* childNode = (nodeToDelete->rightNode == nullptr) ? nodeToDelete->leftNode : nodeToDelete->rightNode;

            if(parent == nullptr) {
                rootNode = childNode;
                childNode->parentNode = nullptr;
                delete nodeToDelete;
                return;
            }

            delete nodeToDelete;
            if(element <= parent->value) parent->leftNode = childNode;
            else parent->rightNode = childNode;
            childNode->parentNode = parent;

            return;
        }

            //case 3: two child
        else{
            BSTNode<T>* parent = nodeToDelete->parentNode;
            BSTNode<T>* rightChild = nodeToDelete->rightNode;
            BSTNode<T>* leftChild = nodeToDelete->leftNode;
            BSTNode<T>* rightMin = getMinNode(rightChild);

            //minimum node can have no node
            if(rightMin->rightNode == nullptr) {
                rightMin->parentNode->leftNode = nullptr;
                rightMin->leftNode = leftChild;
                rightMin->rightNode = rightChild;

                if (parent == nullptr) {
                    rootNode = rightMin;
                    rightMin->parentNode = nullptr;
                    delete nodeToDelete;
                    return;
                }

                rightMin->parentNode = parent;

                delete nodeToDelete;
                return;
            }

                //minimum node can have a right node
            else{
                BSTNode<T>* parentOfMin = rightMin->parentNode;

                //copy content
                nodeToDelete->value = rightMin->value;

                //delete and substitute
                if(parentOfMin->leftNode == rightMin)
                    parentOfMin->leftNode = rightMin->rightNode;
                else
                    parentOfMin->rightNode = rightMin->rightNode;
                rightMin->rightNode->parentNode = parentOfMin;
                delete rightMin;
                return;
            }
        }
    } //done


    unsigned getItemDepth(T element)
    {
        //This function returns the depth of an item in the binary search tree.
        //    Assume that the root has a depth of 0, the nodes at the next level have a depth of 1 and so on.
        //    If the item is not in the tree, return an invalid number to indicate it.

        unsigned int loopTurn = 0;
        BSTNode<T>* currentNode = rootNode;

        while(currentNode != nullptr)
        {

            if(element == currentNode->value)
                return loopTurn;

            else if(element < currentNode->value)
                currentNode =  currentNode->leftNode;

            else
                currentNode =  currentNode->rightNode;

            loopTurn++;

        }
        throw std::invalid_argument("Item not in tree");
    } //done


    T getMaxItem(){
        //This function finds and returns the maximum item of the binary search tree. You cannot write recursive function for this task.

        //boundary condition. null tree
        if(rootNode == nullptr){
            throw std::invalid_argument("No Item in tree");
        }


        BSTNode<T>* currentNode = rootNode;
        while(currentNode->rightNode != nullptr){
            currentNode = currentNode->rightNode;
        }
        return currentNode->value;
    } //done


    T getMinItem(){
        //This function finds and returns the minimum item of the binary search tree. You cannot write recursive function for this task.
        if(rootNode == nullptr){
            throw std::invalid_argument("No Item in tree");
        }


        BSTNode<T>* currentNode = rootNode;
        while(currentNode->leftNode != nullptr){
            currentNode = currentNode->leftNode;
        }
        return currentNode->value;
    } //done


    unsigned getHeight(){
        //This function returns the height of the binary search tree.
        return getHeightRecursive(rootNode) - 1;
    } //done


    void printInOrder(std::ostream& os){
        //This function prints the in-order traversal of the binary search tree.
        DynamicArray<T> data;
        inOrderTraversalRecursion(rootNode, data);
        os << data;
    }


    void printPreOrder(std::ostream &os){
        //This function prints the pre-order traversal of the binary search tree.
        DynamicArray<T> data;
        preOrderTraversalRecursion(rootNode, data);
        os << data;
    }


    void printPostOrder(std::ostream &os){
        //This function prints the post-order traversal of the binary search tree.
        DynamicArray<T> data;
        postOrderTraversalRecursion(rootNode, data);
        os << data;
    }


    unsigned getSize(){
        //This function returns the current size of the binary search tree. The size of a tree is the number of nodes in the tree.
        //    You should write a recursive function for this task.
        return getSizeRecursive(rootNode);

    }

};


#endif //BINARYSEARCHTREE_BST_H

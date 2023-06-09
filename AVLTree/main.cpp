#include <iostream>
#include <stack>
#include <queue>

struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
};

typedef Node* AVLNode;

class AVLTree{
private:
    AVLNode root;
    int size;

    int getHeight(AVLNode x){
        if( x == nullptr) return 0;
        return (std::max((x->left == nullptr) ? 0: x->left->height , (x->right == nullptr) ? 0: x->right->height)) + 1;
    }

    int getBalanceFactor(AVLNode x){
        if( x == nullptr) return 0;
        return getHeight(x->left) - getHeight(x->right);
    }

    AVLNode rightRotation(AVLNode y){
        AVLNode x = y->left;
        AVLNode b = x->right;

        x->right = y;
        y->left = b;

        y->height = getHeight(y);
        x->height = getHeight(x);

        return x;
    }
    AVLNode leftRotation(AVLNode x){
        AVLNode y = x->right;
        AVLNode b = y->left;

        y->left = x;
        x->right = b;

        x->height = getHeight(x);
        y->height = getHeight(y);

        return y;
    }

    void inOrderRecursion(AVLNode x){
        if(x == nullptr) return;
        if(x->right == nullptr && x->left == nullptr) std::cout << x->key;
        else{
            std::cout << x->key << " (";
            inOrderRecursion(x->left);
            std::cout << ") (";
            inOrderRecursion(x->right);
            std::cout << ") " ;
        }
    }

public:
    AVLTree() :root(nullptr), size(0){}
    void insert(int value){
       AVLNode p = root;
       AVLNode newNode = new Node{value, nullptr, nullptr, 1};
       size++;

       if(root == nullptr){
           root = newNode;
           return;
       }

       std::stack<AVLNode> nodeStack;
       while(true){
           if(p->key < value){
               if(p->right != nullptr) {
                   nodeStack.push(p);
                   p = p->right;
               }
               else{
                   nodeStack.push(p);
                   p->right = newNode;
                   break;
               }
           }else{
               if(p->left != nullptr) {
                   nodeStack.push(p);
                   p = p->left;
               }
               else{
                   nodeStack.push(p);
                   p->left = newNode;
                   break;
               }
           }
       }

       bool rotationFlag = false;
       bool inRight;
       while(!nodeStack.empty()){
           AVLNode currentNode = nodeStack.top(); nodeStack.pop();
           if(!nodeStack.empty() && nodeStack.top()->right == currentNode) inRight = true;
           else inRight = false;

           currentNode->height = getHeight(currentNode);
           int balanceFactor = getBalanceFactor(currentNode);
           if(balanceFactor > 1){
               rotationFlag = true;
               if(value < currentNode->left->key) currentNode =  rightRotation(currentNode);
               else{
                   currentNode->left = leftRotation(currentNode->left);
                   currentNode = rightRotation(currentNode);
               }
           }
           if(balanceFactor < -1){
               rotationFlag = true;
               if(value > currentNode->right->key) currentNode =  leftRotation(currentNode);
               else{
                   currentNode->right = rightRotation(currentNode->right);
                   currentNode = leftRotation(currentNode);
               }
           }

           if(nodeStack.empty()) root = currentNode;
           else{
               if(inRight) nodeStack.top()->right = currentNode;
               else nodeStack.top()->left = currentNode;
           }
       }
       if(rotationFlag){
           std::cout << "Height Invariant Violated." << std::endl;
           std::cout << "After Balancing:" << std::endl;
       }
    }
    void printTree(){
        inOrderRecursion(root);
        std::cout << std::endl;
    }

    bool remove(int value){
        AVLNode p = root;
        if(root == nullptr) {
            std::cout << "Can't find node";
            return false;
        }
        AVLNode toBeDeleted = nullptr;

        std::stack<AVLNode> nodeStack;
        std::stack<AVLNode> nodeQueue;

        //findNode
        while(true){
            if(p->key < value){
                if(p->right != nullptr) {
                    nodeStack.push(p);
                    p = p->right;
                }
                else break;
            }else if((p->key > value)){
                if(p->left != nullptr) {
                    nodeStack.push(p);
                    p = p->left;
                }
                else break;
            }else{
                toBeDeleted = p;
                break;
            }
        }

        if(toBeDeleted == nullptr) {
            std::cout << "Can't find node";
            return false;
        }
        //else std::cout << "Node to be deleted... address:" << toBeDeleted << ", value:" << toBeDeleted->key << std::endl;
        //case 1: no subtree
        if(toBeDeleted->right == nullptr && toBeDeleted->left == nullptr){
            if(toBeDeleted == root) root = nullptr;
            else if(value < nodeStack.top()->key) nodeStack.top()->left = nullptr;
            else nodeStack.top()->right = nullptr;

            delete toBeDeleted;
        }//case 2: only left subtree
        else if(toBeDeleted->right == nullptr){
            if(toBeDeleted == root) root = toBeDeleted->left;
            else if(value < nodeStack.top()->key) nodeStack.top()->left = toBeDeleted->left;
            else nodeStack.top()->right = toBeDeleted->left;

            delete toBeDeleted;
        }//case 3: only right subtree
        else if(toBeDeleted->left == nullptr){
            if(toBeDeleted == root) root = toBeDeleted->right;
            else if(value < nodeStack.top()->key) nodeStack.top()->left = toBeDeleted->right;
            else nodeStack.top()->right = toBeDeleted->right;

            delete toBeDeleted;
        }//case 4: both subtree available
        else{
            AVLNode nodeToReplace = nullptr;
            AVLNode currentNode = toBeDeleted->right;
            AVLNode parentOfDeleted = nodeStack.empty() ? nullptr : nodeStack.top();

            if(currentNode->left == nullptr){
                nodeToReplace = currentNode;
                nodeQueue.push(currentNode);
            }else{
                while(true){
                    nodeQueue.push(currentNode);
                    if(currentNode->left->left == nullptr){
                        nodeToReplace = currentNode->left;
                        currentNode->left = currentNode->left->right;
                        break;
                    }
                    currentNode = currentNode->left;
                }
            }

            nodeToReplace->left = toBeDeleted->left;
            nodeToReplace->right = toBeDeleted->right;

            if(parentOfDeleted == nullptr) root = nodeToReplace;
            else if(value < parentOfDeleted->key) parentOfDeleted->left = nodeToReplace;
            else parentOfDeleted->right = nodeToReplace;

            delete toBeDeleted;
            nodeStack.push(nodeToReplace);
        }

        while(!nodeQueue.empty()){
            nodeStack.push(nodeQueue.top()); nodeQueue.pop();
        }


        /*
        std::cout << "going through stack" << std::endl;
        while(!nodeStack.empty()){
            AVLNode currentNode = nodeStack.top(); nodeStack.pop();
            std::cout << "address:" << currentNode << ", value:" << currentNode->key << std::endl;
        }
        */
        bool rotationFlag = false;
        bool inRight;
        while(!nodeStack.empty()){
            AVLNode currentNode = nodeStack.top(); nodeStack.pop();
            if(!nodeStack.empty() && nodeStack.top()->right == currentNode) inRight = true;
            else inRight = false;

            currentNode->height = getHeight(currentNode);
            int balanceFactor = getBalanceFactor(currentNode);
            if(balanceFactor > 1){
                rotationFlag = true;
                if(getBalanceFactor(currentNode->left) >= 0) currentNode =  rightRotation(currentNode);
                else{
                    currentNode->left = leftRotation(currentNode->left);
                    currentNode = rightRotation(currentNode);
                }
            }
            if(balanceFactor < -1){
                rotationFlag = true;
                if(getBalanceFactor(currentNode->right) <= 0) currentNode =  leftRotation(currentNode);
                else{
                    currentNode->right = rightRotation(currentNode->right);
                    currentNode = leftRotation(currentNode);
                }
            }

            if(nodeStack.empty()) root = currentNode;
            else{
                if(inRight) nodeStack.top()->right = currentNode;
                else nodeStack.top()->left = currentNode;
            }
        }
        if(rotationFlag){
            std::cout << "Height Invariant Violated." << std::endl;
            std::cout << "After Balancing:" << std::endl;
        }
        size--;
        return true;
    }
    bool find(int value){
        AVLNode p = root;
        if(root == nullptr) {
            std::cout << "False" << std::endl;
            return false;
        }
        AVLNode toBeDeleted = nullptr;

        std::stack<AVLNode> nodeStack;
        std::stack<AVLNode> nodeQueue;

        //findNode
        while(true){
            if(p->key < value){
                if(p->right != nullptr) {
                    nodeStack.push(p);
                    p = p->right;
                }
                else break;
            }else if((p->key > value)){
                if(p->left != nullptr) {
                    nodeStack.push(p);
                    p = p->left;
                }
                else break;
            }else{
                toBeDeleted = p;
                break;
            }
        }

        if(toBeDeleted == nullptr) {
            std::cout << "False" << std::endl;
            return false;
        }
        else std::cout << "True" << std::endl;
    }
};

int main() {
    AVLTree tree;
    char op;
    int value;
    while(true){
        std::cin >> op >> value;
        if(op == 'I' || op == 'i'){
            tree.insert(value);
            tree.printTree();
        }else if(op == 'E'|| op == 'e'){
            break;
        }else if(op == 'D'|| op == 'd'){
            tree.remove(value);
            tree.printTree();
        }else if(op == 'F'|| op == 'f'){
            tree.find(value);
        }
    }
}

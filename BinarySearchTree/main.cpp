#include <iostream>
#include "BST.h"
#include <cstdlib>

int main() {
    BinarySearchTree<int> tree;
    /*
    srand (110);
    int random;
    for(int i = 0; i < 25; i++){
        random = rand() % 1000 + 1;
        tree.insertItem(random);
        std::cout << random << std::endl;
    }
    tree.printInOrder(std::cout);

    std::cout << std::endl;
    std::cout << tree.searchItem(199) << std::endl;
    std::cout << tree.getMaxItem() << std::endl;
    std::cout << tree.getMinItem() << std::endl;
    std::cout << tree.getHeight() << std::endl;
    std::cout << tree.getSize() << std::endl;
    std::cout << tree.getItemDepth(352) << std::endl;
    */
    while(true){
        int option;
        int value;
        std::cout << "1. Insert Item" << std::endl;
        std::cout << "2. Search Item" << std::endl;
        std::cout << "3. Get In Order Successor" << std::endl;
        std::cout << "4. Get In Order Predecessor" << std::endl;
        std::cout << "5. Delete Item" << std::endl;
        std::cout << "6. Get Item Depth" << std::endl;
        std::cout << "7. Get Max Item" << std::endl;
        std::cout << "8. Get Min Item" << std::endl;
        std::cout << "9. Get Height" << std::endl;
        std::cout << "10. Print In Order" << std::endl;
        std::cout << "11. Print Pre Order" << std::endl;
        std::cout << "12. Print Post Order" << std::endl;
        std::cout << "13. Get Size" << std::endl;
        std::cout << "14. Exit" << std::endl;
        std::cout << ">>>";
        std::cin >> option;

        if(option == 14) break;

        switch (option) {
            case 1:
                std::cout << "Type Integer to Insert: " << std::endl;
                std::cin >> value;
                tree.insertItem(value);
                std::cout << value << " inserted in tree." << std::endl;
                std::cout << "_________________________" << std::endl;
                break;

            case 2:
                std::cout << "Type Integer to Search: " << std::endl;
                std::cin >> value;
                if(tree.searchItem(value))
                    std::cout << value << " is in the tree." << std::endl;
                else
                    std::cout << value << " is not in the tree." << std::endl;
                std::cout << "_________________________" << std::endl;
                break;

            case 3:
                std::cout << "Type Integer to get Successor: " << std::endl;
                std::cin >> value;
                try {
                    std::cout << "Successor of " << value << ": " << tree.getInOrderSuccessor(value) << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            case 4:
                std::cout << "Type Integer to get Predecessor: " << std::endl;
                std::cin >> value;
                try {
                    std::cout << "Predecessor of " << value << ": " << tree.getInOrderPredecessor(value) << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            case 5:
                std::cout << "Type Integer to Delete: " << std::endl;
                std::cin >> value;
                try {
                    tree.deleteItem(value);
                    std::cout << value << " Deleted from tree" << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            case 6:
                std::cout << "Type Integer to get Depth: " << std::endl;
                std::cin >> value;
                try {
                    std::cout << "Depth of " << value << ": " << tree.getItemDepth(value) << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            case 7:
                try {
                    std::cout << "Max Item: " << tree.getMaxItem() << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            case 8:
                try {
                    std::cout << "Min Item: " << tree.getMinItem() << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            case 9:
                try {
                    std::cout << "Height of the tree: " <<  tree.getHeight() << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            case 10:
                try {
                    tree.printInOrder(std::cout);
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << std::endl;
                std::cout << "_________________________" << std::endl;
                break;

            case 11:
                try {
                    tree.printPreOrder(std::cout);
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << std::endl;
                std::cout << "_________________________" << std::endl;
                break;

            case 12:
                try {
                    tree.printPostOrder(std::cout);
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << std::endl;
                std::cout << "_________________________" << std::endl;
                break;

            case 13:
                try {
                    std::cout << "Size of the tree: " << tree.getSize() << std::endl;
                }catch (std::exception& e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "_________________________" << std::endl;
                break;

            default:
                break;
        }
    }




}

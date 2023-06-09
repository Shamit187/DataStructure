#include <iostream>
#include "marge.h"
#include "quick.h"
#include "generator.h"
#include <chrono>
#include <fstream>
#define SIZE 10000
#define RANDOM_ARRAY 0
#define DES_ARRAY 1
#define ASC_ARRAY 2


int main() {

    int option;
    std::cout << "1: Evaluation" << std::endl;
    std::cout << "2: Report" << std::endl;
    std::cin >> option;

    switch (option) {
        case 1: {
            std::cout << std::endl;
            std::cout << "Size: " << std::endl;

            int size;
            std::cin >> size;

            std::cout << std::endl;
            std::cout << "1: Random Array" << std::endl;
            std::cout << "2: Descending Array" << std::endl;
            std::cout << "3: Ascending Array" << std::endl;

            int arrayOption;
            int *generatedArray = nullptr;
            std::cin >> arrayOption;
            switch (arrayOption - 1) {
                case RANDOM_ARRAY:
                    std::cout << "Generating random array" << std::endl;
                    std::cout << "____________________________" << std::endl << std::endl;
                    generatedArray = randomGenerator(size);
                    break;
                case ASC_ARRAY:
                    std::cout << "Generating ascending array" << std::endl;
                    std::cout << "____________________________" << std::endl << std::endl;
                    generatedArray = ascendGenerator(size);
                    break;
                case DES_ARRAY:
                    std::cout << "Generating descending array" << std::endl;
                    std::cout << "____________________________" << std::endl << std::endl;
                    generatedArray = descendGenerator(size);
                    break;
                default:
                    //it wont reach here
                    break;
            }
            int *sendToMerge = nullptr;
            int *sendToQuick = nullptr;

            sendToMerge = copyArray(generatedArray, size);
            sendToQuick = copyArray(generatedArray, size);

            std::cout << "Generated Array" << std::endl;
            for (int i = 0; i < size; i++)
                std::cout << generatedArray[i] << " ";
            std::cout << std::endl;

            auto started = std::chrono::high_resolution_clock::now();
            margeSort(sendToMerge, 0, size - 1);
            auto done = std::chrono::high_resolution_clock::now();

            std::cout << "Time taken by merge sort: "
                      << std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() /
                         1000000.0
                      << "ms" << std::endl;

            started = std::chrono::high_resolution_clock::now();
            quickSort(sendToQuick, 0, size - 1);
            done = std::chrono::high_resolution_clock::now();

            std::cout << "Time taken by quick sort: "
                      << std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() /
                         1000000.0
                      << "ms" << std::endl;

            std::cout << std::endl;

            std::cout << "Merge" << "\t" << "Quick" << std::endl;
            for (int i = 0; i < size; i++)
                std::cout << sendToMerge[i] << "\t\t" << sendToQuick[i] << std::endl;
            std::cout << std::endl;

            break;
        }
        case 2: {
            std::ofstream reportOutput;
            reportOutput.open("D:\\reportFile.txt");
            double dataSet[3][6][3];
            for (int mode = 0; mode < 3; mode++) {
                int size = 1;
                switch (mode) {
                    case RANDOM_ARRAY:
                        std::cout << "Calculating for random array" << std::endl;
                        std::cout << "____________________________" << std::endl << std::endl;
                        break;
                    case ASC_ARRAY:
                        std::cout << "Calculating for ascending array" << std::endl;
                        std::cout << "____________________________" << std::endl << std::endl;
                        break;
                    case DES_ARRAY:
                        std::cout << "Calculating for descending array" << std::endl;
                        std::cout << "____________________________" << std::endl << std::endl;
                        break;
                    default:
                        //it wont reach here
                        break;
                }
                for (int i = 0; i < 6; i++) {
                    size *= 10;
                    std::cout << "Calculating for array size: " << size << std::endl;
                    auto started = std::chrono::high_resolution_clock::now();
                    int *arr_for_merge;
                    switch (mode) {
                        case RANDOM_ARRAY:
                            arr_for_merge = randomGenerator(size);
                            break;
                        case ASC_ARRAY:
                            arr_for_merge = ascendGenerator(size);
                            break;
                        case DES_ARRAY:
                            arr_for_merge = descendGenerator(size);
                            break;
                    }
                    int *arr_for_quick = copyArray(arr_for_merge, size);
                    auto done = std::chrono::high_resolution_clock::now();
                    std::cout << "Array generation Time: "
                              << std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() /
                                 1000000.0
                              << "ms" << std::endl;
                    dataSet[mode][i][0] =
                            std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() / 1000000.0;

                    started = std::chrono::high_resolution_clock::now();
                    margeSort(arr_for_merge, 0, size - 1);
                    done = std::chrono::high_resolution_clock::now();
                    std::cout << "Time taken by merge sort: "
                              << std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() /
                                 1000000.0
                              << "ms" << std::endl;
                    dataSet[mode][i][1] =
                            std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() / 1000000.0;

                    started = std::chrono::high_resolution_clock::now();
                    quickSort(arr_for_quick, 0, size - 1);
                    done = std::chrono::high_resolution_clock::now();
                    std::cout << "Time taken by quick sort: "
                              << std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() /
                                 1000000.0
                              << "ms" << std::endl;

                    dataSet[mode][i][2] =
                            std::chrono::duration_cast<std::chrono::nanoseconds>(done - started).count() / 1000000.0;
                    std::cout << std::endl;
                }
            }

            for (int i = 0; i < 3; i++) {
                switch (i) {
                    case RANDOM_ARRAY:
                        reportOutput << "Random Array" << std::endl;
                        break;
                    case ASC_ARRAY:
                        reportOutput << "Ascend Array" << std::endl;
                        break;
                    case DES_ARRAY:
                        reportOutput << "Descend Array" << std::endl;
                        break;
                    default:
                        break;
                }
                int size = 1;
                for (int j = 0; j < 6; j++) {
                    size *= 10;
                    reportOutput << "Calculating for: " << size << std::endl;
                    for (int k = 1; k < 3; k++) {
                        reportOutput << dataSet[i][j][k] << " ";
                    }
                    reportOutput << std::endl;
                }
            }
            reportOutput.close();
            break;
        }
        default:
            break;
    }


}

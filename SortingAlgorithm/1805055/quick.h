//
// Created by User on 6/7/2021.
//
#ifndef SORTCOMPARISON1_QUICK_H
#define SORTCOMPARISON1_QUICK_H

int quickSortPartition(int *arr, int low, int high){
//    int pivot = arr[(low + high)/2];
//    int i = low - 1;
//    int j = high + 1;
//
//    while(true){
//        do{
//            i++;
//        } while (arr[i] < pivot);
//        do{
//            j--;
//        } while(arr[j] > pivot);
//        if(i >= j)
//            return j;
//        std::swap(arr[i], arr[j]);
//    }

    int pivot = arr[high];
    int partitionPoint = low - 1;
    for(int i = low; i <= high; i++){
        if(*(arr + i) < pivot){
            partitionPoint++;
            std::swap(*(arr + i), *(arr + partitionPoint));
        }
    }
    std::swap(arr[high], arr[partitionPoint + 1]);
    return partitionPoint + 1;
}

void quickSort(int* arr, int low, int high){
    if(low >= high)
        return;

    int pivotPoint = quickSortPartition(arr, low, high);
    quickSort(arr, low, pivotPoint - 1);
    quickSort(arr, pivotPoint + 1, high);
}


#endif //SORTCOMPARISON1_QUICK_H

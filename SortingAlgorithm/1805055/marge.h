//
// Created by User on 6/7/2021.
//

#ifndef SORTCOMPARISON1_MARGE_H
#define SORTCOMPARISON1_MARGE_H


void marge(int* arr, int low, int middle, int high){
    int lowArrSize = middle - low + 1;
    int* lowArr = new int[lowArrSize];

    int highArrSize = high - middle;
    int* highArr = new int[highArrSize];

    for(int i = 0; i < lowArrSize; i++)
        *(lowArr + i) = *(arr + low + i);
    for(int i = 0; i < highArrSize; i++)
        *(highArr + i) = *(arr + middle + 1 + i);

    int i = 0;
    int j = 0;
    int k = low;

    while(i < lowArrSize && j < highArrSize){
        if(lowArr[i] <= highArr[j]){
            arr[k++] = lowArr[i++];
        }
        else{
            arr[k++] = highArr[j++];
        }
    }

    while(i < lowArrSize){
        arr[k++] = lowArr[i++];
    }
    while(j < highArrSize){
        arr[k++] = highArr[j++];
    }
}

void margeSort(int* arr, int low, int high){
    if(low >= high) {
        return;
    }

    int middle = (high + low) / 2;

    margeSort(arr, low, middle);
    margeSort(arr, middle + 1, high);
    marge(arr, low, middle, high);
}

#endif //SORTCOMPARISON1_MARGE_H

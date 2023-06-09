#include <iostream>
#include <vector>

int dynamicDiceProblem(std::vector<int>& diceFace, int summation){
    int** dpArray = new int*[diceFace.size()];
    for(int i = 0; i < diceFace.size(); i++){
        dpArray[i] = new int[summation];
        for(int j = 0; j < summation; j++) dpArray[i][j] = 0;
    }

    for(int i = 0; i < diceFace.size(); i++){
        if(i >= summation) break;
        dpArray[i][i] = 1;
    }

    for(int i = 0; i < diceFace[0]; i++){
        if(summation <= i) break;
        dpArray[0][i] = 1;
    }

    int limit_max = diceFace[0];
    for(int i = 1; i < diceFace.size(); i++){
        limit_max += diceFace[i];
        for(int j = i + 1; j < summation; j++){
            if( j > limit_max ) dpArray[i][j] = 0;
            else {
                dpArray[i][j] = dpArray[i - 1][j - 1] % 1000000007 + dpArray[i][j - 1] % 1000000007;
                if(j - diceFace[i]> 0) dpArray[i][j] -= dpArray[i - 1][j - diceFace[i] - 1];
                dpArray[i][j] %= 1000000007;
            }
        }
    }

    return dpArray[diceFace.size() - 1][summation - 1];
}


int main(){
    int dice, summation;
    std::cin >> dice >> summation;

    std::vector<int> diceFace;
    for(int i = 0; i < dice; i++){
        int value;
        std::cin >> value;
        diceFace.push_back(value);
    }

    std::cout << dynamicDiceProblem(diceFace, summation) << std::endl;
}
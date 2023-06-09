#include <iostream>
#include <queue>

int main() {
    int total_plants, friends;
    std::cin >> total_plants >> friends;

    std::priority_queue<int>plant_queue;
    int plant_cost;
    for(int i = 0; i < total_plants; i++){
        std::cin >> plant_cost;
        plant_queue.push(plant_cost);
    }

    int* spends = new int[friends];
    for(int i = 0; i < friends; i++) spends[i] = 0;

    plant_cost = 0;
    int i = 0;
    while(!plant_queue.empty()){
        plant_cost += (spends[i] + 1) * plant_queue.top();
        spends[i]++;
        plant_queue.pop();
        i++;
        i %= friends;
    }

    std::cout << plant_cost;
}

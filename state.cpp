#include <vector>
#include "state.hpp"
#include <string>
bool State::isFinished()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->board[i][j] != this->goal[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int State::manhatten(){
    int counter = 0;
    bool tmp;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tmp = false;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++){
                    if (this->board[k][l] == this->goal[i][j]){
                        counter += abs(i - k) + abs(j - l);
                        tmp = true;
                        break;
                    }
                }
                if (tmp) break;
            }
        }
    }
    return counter;
}



State::State(std::vector<std::vector<int>>& inputs)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->board[i][j] = inputs[i][j];
        }
    };
    this->man_cost = this->manhatten();
    this->cost = 0;
    this->t_cost = this->cost + this->man_cost;
}



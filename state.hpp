#include <vector>
#include <iostream>
class State {
public:
    std::vector<std::vector<int>> goal = { {1, 2, 3}, {4, 5, 6}, {7, 8, 0} };
    std::vector<std::vector<int>> board = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
    std::vector<std::vector<std::vector<int>>> parent_boards = {};
    int cost;
    int man_cost;
    int t_cost;
    

    State(std::vector<std::vector<int>>& inputs);

    bool isFinished();

    int manhatten();

    // friend bool operator==(const State &a, const State &b) {
    //     for (int i = 0; i < 3; i++) {
    //         for (int j = 0; j < 3; j++) {
    //             if (a.board[i][j] != b.board[i][j]) {
    //                 return false;
    //             }
    //         }
    //     }
    //     return true;
    // }

    friend bool operator<(const State &a, const State &b) {
        return a.t_cost > b.t_cost;
    }
};

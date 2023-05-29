#include <iostream>
#include <vector>
#include <queue>
#include "state.hpp"
#include <string>
#include <set>

void expand(std::priority_queue<State> &pq, std::set<std::vector<std::vector<int>>>& visited, State curr);
void path(State s);
void print(std::vector<std::vector<int>> v);

int main(int argc, char* argv[]) {
    std::vector<std::vector<int>> inputs(3, std::vector<int>(3, 0));
    
    if (argc < 10) {
        std::cout<<"Invalid input."<<std::endl;
    }

    int k = 1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            try {
                int num = atoi(argv[k++]);
                if (num > 8 || num < 0) throw num;
                inputs[i][j] = num;
            } catch (int err) {
                std::printf("Invalid input, only accepts int range [0, 8], got %d.\n", err);
                return EXIT_FAILURE;
            }
        }
    }

    State start(inputs);
    std::priority_queue<State> pq;
    std::set<std::vector<std::vector<int>>> visited;

    pq.push(start);
    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        if (curr.isFinished()) {
            std::cout<<"Found solution!"<<std::endl;
            path(curr);
            break;
        }
        else {
            // expand states;
            expand(pq, visited, curr);
        }
    }
    std::cout<<"Total number of states expanded: "<<visited.size()<<std::endl;
    return 0;
}

void expand(std::priority_queue<State> &pq, std::set<std::vector<std::vector<int>>>& visited, State curr) {
    visited.insert(curr.board);
    std::vector<std::vector<int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (curr.board[i][j] == 0) {
                for (int k = 0; k < dirs.size(); k++) {
                    int x = i + dirs[k][0];
                    int y = j + dirs[k][1];
                    if (x >= 0 && x < 3 && y >= 0 && y < 3) {
                        std::vector<std::vector<int>> tmp = curr.board;
                        std::swap(tmp[i][j], tmp[x][y]);
                        State next(tmp);
                        next.man_cost = next.manhatten();
                        next.t_cost = ++curr.cost + next.man_cost;

                        // copy parent boards for path printing.
                        for (auto& v : curr.parent_boards) {
                            next.parent_boards.push_back(v);
                        }
                        next.parent_boards.push_back(curr.board);
                        if (visited.find(next.board) == visited.end()) {
                            pq.push(next);
                        } 
                    }
                }
            }
        }
    }
}

void path(State s){
    int i = 0;
    for (; i < s.parent_boards.size(); i++) {
        std::cout<<"Step "<<i + 1<<":"<<std::endl;
        print(s.parent_boards[i]);
    }
    std::cout<<"Step "<<i + 1<<":"<<std::endl;
    print(s.board);
}

void print(std::vector<std::vector<int>> v) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3;j++) {
            std::cout<<v[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
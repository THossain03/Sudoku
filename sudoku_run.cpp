#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

bool isEmptyLocation(int grid[9][9], int &row, int &col);
bool UsedInRow(int grid[9][9], int row, int number);
bool UsedInCol(int grid[9][9], int col, int number);
bool UsedInBox(int grid[9][9], int boxBeginRow, int boxBeginCol, int number);
void printResult(int finalgrid[9][9]);
bool SolveSudoku(int grid[9][9]);

bool SolveSudoku(int grid[9][9]) {
    int row, col;
    if (!isEmptyLocation(grid, row, col))
       return true;
    for (int num = 1; num <= 9; num++) {
        if (!UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - (row % 3) , col - (col % 3), num)) {
            grid[row][col] = num;
            if (SolveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0;
        }
    }
    return false;
}

bool isEmptyLocation(int grid[9][9], int &row, int &col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool UsedInRow(int grid[9][9], int row, int number) {
    for (int col = 0; col < 9; col++)
        if (grid[row][col] == number)
            return true;
    return false;
}

bool UsedInCol(int grid[9][9], int col, int number) {
    for (int row = 0; row < 9; row++)
        if (grid[row][col] == number)
            return true;
    return false;

}

bool UsedInBox(int grid[9][9], int boxBeginRow, int boxBeginCol, int number) {
    bool tf = false;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row+boxBeginRow][col+boxBeginCol] == number) {
                tf = true;
            }
        }
    }
    return tf;
}

void printResult(int finalgrid[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout<< finalgrid[row][col]<<"  ";
        }
        cout<<endl;
    }
}

int main() {
    //default grid
    int grid[9][9] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 3, 0, 8, 5},
                      {0, 0, 1, 0, 2, 0, 0, 0, 0},
                      {0, 0, 0, 5, 0, 7, 0, 0, 0},
                      {0, 0, 4, 0, 0, 0, 1, 0, 0},
                      {0, 9, 0, 0, 0, 0, 0, 0, 0},
                      {5, 0, 0, 0, 0, 0, 0, 7, 3},
                      {0, 0, 2, 0, 1, 0, 0, 0, 0},
                      {0, 0, 0, 0, 4, 0, 0, 0, 9}};
    char default_option_YN;
    string next_line="";
    cout << "Welcome to the Sudoku Solver" << endl;
    cout << "Do you want to input own values [Type Y] or use the deafult generated sudoku [Type N]?  ";
    cin >> default_option_YN;
    if (default_option_YN == 'Y'){
        cout << "Alright let's begin! For any unknown spaces just type 0, if known type in the given digit \n";
        char valid_nums_digs[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        for (int num=0; num<9; num++) {
            cout << "Please enter Row " + to_string(num+1);
            cout << " (Seperate values with commas): \n";
            cin >> next_line;
            int count_nums_appear=0;
            for (int i=0; i<next_line.length(); i++) {
                for (int j=0; j<10; j++) {
                    if (next_line.at(i) == valid_nums_digs[j]) {
                        if (count_nums_appear<9) {
                            grid[num][count_nums_appear] = (valid_nums_digs[j] - '0');
                        }
                        count_nums_appear++;
                    }
                }
            }
            if (count_nums_appear<9) {
                for (int i=count_nums_appear; count_nums_appear<9; count_nums_appear++) {
                    grid[num][count_nums_appear] = 0;
                }
            }
            
        }
    }
    if (SolveSudoku(grid) == true) {
          printResult(grid);
    } else {
        cout<<"No solution found"<<endl;
    }
    return 0;
}
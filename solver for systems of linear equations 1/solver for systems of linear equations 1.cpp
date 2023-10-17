// solver for systems of linear equations 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <windows.h> //For GetAsyncKeyState


// Function to implement the ForwardThreeLoops operation
void ForwardThreeLoops(std::vector<std::vector<double>>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n + 1; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}

// Function to implement the ForwardTwoLoops operation
void ForwardTwoLoops(std::vector<std::vector<double>>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        std::vector<double> pivotRow = matrix[i];
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / pivotRow[i];
            for (int k = i; k < n + 1; ++k) {
                matrix[j][k] -= factor * pivotRow[k];
            }
        }
    }
}

// Function to implement the ForwardOneLoop operation
void ForwardOneLoop(std::vector<std::vector<double>>& matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n + 1; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}


// Function to print a matrix
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    // New example equations: 
    // 3x + 4y - z = 1
    // 2x + y + z = 2
    // x + 2y + 3z = 3
    std::cout << "New example equations:" << std::endl;
    std::cout << "3x + 4y - z = 1" << std::endl;
    std::cout << "2x + y + z = 2" << std::endl;
    std::cout << "x + 2y + 3z = 3" << std::endl;

    std::vector<std::vector<double>> matrix = {
        {3, 4, -1, 1},
        {2, 1, 1, 2},
        {1, 2, 3, 3}
    };

    // Call and print the ForwardThreeLoops function
    std::cout << "\nResult after ForwardThreeLoops:" << std::endl;
    ForwardThreeLoops(matrix, 3);
    printMatrix(matrix);

    // Reset matrix and call and print the ForwardTwoLoops function
    matrix = {
        {3, 4, -1, 1},
        {2, 1, 1, 2},
        {1, 2, 3, 3}
    };
    std::cout << "\nResult after ForwardTwoLoops:" << std::endl;
    ForwardTwoLoops(matrix, 3);
    printMatrix(matrix);

    // Reset matrix and call and print the ForwardOneLoop function
    matrix = {
        {3, 4, -1, 1},
        {2, 1, 1, 2},
        {1, 2, 3, 3}
    };
    std::cout << "\nResult after ForwardOneLoop:" << std::endl;
    ForwardOneLoop(matrix, 3);
    printMatrix(matrix);



    // Wait for the user to press 'Esc' to exit
    std::cout << "\nPress 'Esc' to exit the program..." << std::endl;
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
    }

    return 0;
}


#include <iostream>
#include <vector>
#include <windows.h>  // For GetAsyncKeyState
#include <chrono>  // For measuring time

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

// Function to print a matrix
void printMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Original 3x3 Example equations
    std::cout << "Original 3x3 Example equations:" << std::endl;
    std::cout << "3x + 4y - z = 1" << std::endl;
    std::cout << "2x + y + z = 2" << std::endl;
    std::cout << "x + 2y + 3z = 3" << std::endl;

    std::vector<std::vector<double>> matrix3 = {
        {3, 4, -1, 1},
        {2, 1, 1, 2},
        {1, 2, 3, 3}
    };

    // Apply ForwardOneLoop to 3x3 matrix
    ForwardTwoLoops(matrix3, 3);
    std::cout << "Result after ForwardTwoLoops for 3x3 matrix:" << std::endl;
    printMatrix(matrix3);

    // New 5x5 Example
    std::cout << "\nApplying ForwardTwoLoops to a 5x5 matrix:" << std::endl;
    std::vector<std::vector<double>> matrix5 = {
        {3, 4, -1, 6, 2, 1},
        {2, 1, 1, 3, 7, 2},
        {1, 2, 3, 4, 5, 3},
        {5, 4, 3, 2, 1, 4},
        {1, 1, 1, 1, 1, 5}
    };

    // Start timer for 5x5 matrix
    auto start5 = std::chrono::high_resolution_clock::now();

    // Apply ForwardOneLoop to 5x5 matrix
    ForwardTwoLoops(matrix5, 5);

    // Stop timer and calculate duration for 5x5 matrix
    auto stop5 = std::chrono::high_resolution_clock::now();
    auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(stop5 - start5);
    std::cout << "Time taken for 5x5 matrix: " << duration5.count() << " microseconds" << std::endl;

    std::cout << "Result after ForwardTwoLoops for 5x5 matrix:" << std::endl;
    printMatrix(matrix5);

    // Wait for user to press 'Esc' to exit
    std::cout << "\nPress 'Esc' to exit the program..." << std::endl;
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
    }
    
    return 0;
}

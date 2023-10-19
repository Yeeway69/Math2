// Math assignments two class assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

// Function to perform backtracking on an upper triangular matrix
std::vector<double> backtracking(const std::vector<std::vector<double>>& A_t, const std::vector<double>& b_t) {
    int n = A_t.size();
    std::vector<double> x(n, 0);

    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += A_t[i][j] * x[j];
        }
        x[i] = (b_t[i] - sum) / A_t[i][i];
    }

    return x;
}

#include <iostream>
#include <vector>

// Assuming the backtracking function is defined above or included from another file

int main() {
    // Test Case 1: A simple 3x3 system
    std::vector<std::vector<double>> A1 = {
        {2, 1, 1},
        {0, 2, 1},
        {0, 0, 3}
    };
    std::vector<double> b1 = { 1, 2, 3 };
    std::vector<double> x1 = backtracking(A1, b1);

    std::cout << "Solution for first system: ";
    for (double val : x1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Test Case 2: A 4x4 system as required
    std::vector<std::vector<double>> A2 = {
        {1, 2, 3, 4},
        {0, 2, 3, 4},
        {0, 0, 3, 4},
        {0, 0, 0, 4}
    };
    std::vector<double> b2 = { 10, 9, 8, 4 };
    std::vector<double> x2 = backtracking(A2, b2);

    std::cout << "Solution for second system: ";
    for (double val : x2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}

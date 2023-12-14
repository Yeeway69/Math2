#include <vector>
#include <iostream>

// Function to perform backtracking (back substitution)
std::vector<double> Backtracking(const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    int n = A.size();
    std::vector<double> x(n, 0); // Initialize the solution vector with zeros

    // Start from the last row and move upwards
    for (int i = n - 1; i >= 0; i--) {
        // Start with the right-hand side of the equation
        x[i] = b[i];

        // Subtract the known values from the right-hand side
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }

        // Divide by the coefficient of the unknown we are solving for
        x[i] /= A[i][i];
    }

    return x; // Return the solution vector
}

// Function to print a vector
void PrintVector(const std::vector<double>& vec) {
    for (double val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Example matrix A (upper triangular)
    std::vector<std::vector<double>> A = {
        {2, 1, 0, 0},
        {0, 3, -1, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 2}
    };

    // Example vector b
    std::vector<double> b = { 1, 2, 3, 4 };

    // Perform backtracking and print the solution
    std::vector<double> solution = Backtracking(A, b);
    std::cout << "Solution: ";
    PrintVector(solution);

    return 0;
}

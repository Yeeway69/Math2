#include <vector>
#include <iostream>
#include <cmath> // for std::fabs function

// Function to perform forward elimination with partial pivoting
void ForwardEliminationWithPartialPivoting(std::vector<std::vector<double>>& A, std::vector<double>& b) {
    int n = A.size();

    for (int i = 0; i < n - 1; i++) {
        // Partial pivoting
        int maxRow = i;
        double maxVal = std::fabs(A[i][i]);
        for (int k = i + 1; k < n; k++) {
            if (std::fabs(A[k][i]) > maxVal) {
                maxVal = std::fabs(A[k][i]);
                maxRow = k;
            }
        }

        // Swap the rows if a larger pivot is found
        if (i != maxRow) {
            std::swap(A[i], A[maxRow]);
            std::swap(b[i], b[maxRow]);
        }

        // Forward elimination
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= A[i][k] * factor;
            }
            b[j] -= b[i] * factor;
        }
    }
}

// Helper function to print a matrix
void PrintMatrix(const std::vector<std::vector<double>>& matrix) {
    for (const auto& row : matrix) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Example matrix A
    std::vector<std::vector<double>> A = {
        {0, 2, 1},
        {1, -2, -3},
        {-1, 1, 2}
    };

    // Example vector b
    std::vector<double> b = { 8, -11, -3 };

    // Perform forward elimination with partial pivoting
    ForwardEliminationWithPartialPivoting(A, b);

    // Output the upper triangular matrix
    std::cout << "Upper triangular matrix: " << std::endl;
    PrintMatrix(A);

    return 0;
}

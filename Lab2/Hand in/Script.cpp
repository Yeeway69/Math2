#include <vector>
#include <iostream>
#include <cmath> // for std::fabs function



// // Function to perform backtracking (back substitution)
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


// Function to solve a system of linear equations A * x = b using forward elimination with partial pivoting and backtracking
std::vector<double> SolveLinearSystem(std::vector<std::vector<double>> A, std::vector<double> b) {
    // First, apply the forward elimination with partial pivoting to transform A into an upper triangular matrix
    ForwardEliminationWithPartialPivoting(A, b);
    // Then, use backtracking to solve for the unknown vector x
    return Backtracking(A, b);
}

// Function to print a system of linear equations
void PrintSystem(const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    // Iterate through each equation in the system and print it in the form Ax = b
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            std::cout << A[i][j] << " * x" << j;
            if (j < A[i].size() - 1) std::cout << " + ";
        }
        std::cout << " = " << b[i] << std::endl;
    }
}

// Function to print a vector
void PrintVector(const std::vector<double>& vec) {
    for (double val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
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
    // Define several systems of linear equations to demonstrate the solver
    std::vector<std::vector<double>> matrices[] = {
        {
            {0, 2, 1},
            {1, -2, -3},
            {-1, 1, 2}
        },
        {
            {1, 2, 3},
            {2, 5, 3},
            {1, 0, 8}
        },
        // ... (Add more systems here, including incompatible and indeterminate ones)
    };

    std::vector<double> vectors[] = {
        {8, -11, -3},
        {14, -1, 8},
        // ... (Add corresponding vectors here)
    };

    // Process each system
    for (size_t i = 0; i < sizeof(matrices) / sizeof(matrices[0]); ++i) {
        std::cout << "Solving system " << i + 1 << ":" << std::endl;
        PrintSystem(matrices[i], vectors[i]);

        // Perform the solution process
        std::vector<double> solution = SolveLinearSystem(matrices[i], vectors[i]);

        // Check for no solution or infinite solutions
        if (!solution.empty()) {
            std::cout << "Solution:" << std::endl;
            PrintVector(solution);
        }
        else {
            std::cout << "The system does not have a unique solution." << std::endl;
        }
        std::cout << std::endl;
    }

    // Define an incompatible system(no solution)
        std::vector<std::vector<double>> incompatibleMatrix = {
            {1, 1, 1},
            {0, 1, 1},
            {0, 0, 0} // This row will have a non-zero element in vector b, making it incompatible
    };
    std::vector<double> incompatibleVector = { 1, 1, 1 }; // This makes the system incompatible

    // Define an indeterminate system (infinite solutions)
    std::vector<std::vector<double>> indeterminateMatrix = {
        {1, 2, 3},
        {0, 0, 0}, // This row of all zeros in the matrix and vector b indicates multiple solutions
        {0, 0, 0}
    };
    std::vector<double> indeterminateVector = { 1, 0, 0 }; // This is consistent with the indeterminate matrix

    // Adding the incompatible and indeterminate systems to the list of systems to process
    std::vector<std::vector<std::vector<double>>> matricesList = { matrices[0], matrices[1], incompatibleMatrix, indeterminateMatrix };
    std::vector<std::vector<double>> vectorsList = { vectors[0], vectors[1], incompatibleVector, indeterminateVector };

    // Process each system
    for (size_t i = 0; i < matricesList.size(); ++i) {
        std::cout << "Solving system " << i + 1 << ":" << std::endl;
        PrintSystem(matricesList[i], vectorsList[i]);

        // Perform the solution process
        std::vector<double> solution = SolveLinearSystem(matricesList[i], vectorsList[i]);

        // Check for no solution or infinite solutions
        if (!solution.empty()) {
            std::cout << "Solution:" << std::endl;
            PrintVector(solution);
        }
        else {
            std::cout << "The system does not have a unique solution." << std::endl;
        }
        std::cout << std::endl;
    }



    return 0;
}

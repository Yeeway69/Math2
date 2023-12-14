#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <array>


using namespace std;

// Define a type for 3x3 matrix
using Matrix3x3 = array<array<double, 3>, 3>;

// Function to create a rotation matrix from Euler axis and angle
Matrix3x3 createRotationMatrix(double axisX, double axisY, double axisZ, double angle) {
    // Normalize the axis vector
    double magnitude = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
    axisX /= magnitude;
    axisY /= magnitude;
    axisZ /= magnitude;

    // Convert angle to radians if necessary
    angle = angle * M_PI / 180.0; // Remove this line if angle is already in radians

    double cosA = cos(angle);
    double sinA = sin(angle);

    Matrix3x3 rotationMatrix = { {
        {cosA + axisX * axisX * (1 - cosA), axisX * axisY * (1 - cosA) - axisZ * sinA, axisX * axisZ * (1 - cosA) + axisY * sinA},
        {axisY * axisX * (1 - cosA) + axisZ * sinA, cosA + axisY * axisY * (1 - cosA), axisY * axisZ * (1 - cosA) - axisX * sinA},
        {axisZ * axisX * (1 - cosA) - axisY * sinA, axisZ * axisY * (1 - cosA) + axisX * sinA, cosA + axisZ * axisZ * (1 - cosA)}
    } };

    return rotationMatrix;
}

// Function to print a matrix
void printMatrix(const Matrix3x3& matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Main function
int main() {
    // Example usage
    double axisX = 1.0, axisY = 0.0, axisZ = 0.0; // Define the axis
    double angle = 90.0; // Define the rotation angle in degrees

    // Create the rotation matrix
    Matrix3x3 rotationMatrix = createRotationMatrix(axisX, axisY, axisZ, angle);

    // Print the rotation matrix
    cout << "Rotation Matrix:" << endl;
    printMatrix(rotationMatrix);

    // Perform your verifications here

    return 0;
}

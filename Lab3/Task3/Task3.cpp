#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
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

    double cosA = cos(angle);
    double sinA = sin(angle);

    Matrix3x3 rotationMatrix = { {
        {cosA + axisX * axisX * (1 - cosA), axisX * axisY * (1 - cosA) - axisZ * sinA, axisX * axisZ * (1 - cosA) + axisY * sinA},
        {axisY * axisX * (1 - cosA) + axisZ * sinA, cosA + axisY * axisY * (1 - cosA), axisY * axisZ * (1 - cosA) - axisX * sinA},
        {axisZ * axisX * (1 - cosA) - axisY * sinA, axisZ * axisY * (1 - cosA) + axisX * sinA, cosA + axisZ * axisZ * (1 - cosA)}
    } };

    return rotationMatrix;
}

// Function to calculate trace of a matrix
double trace(const Matrix3x3& matrix) {
    return matrix[0][0] + matrix[1][1] + matrix[2][2];
}

int main() {
    const int numMatrices = 100;
    const double maxAngle = 6 * M_PI;
    vector<double> angles, traces;

    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < numMatrices; ++i) {
        double angle = i * maxAngle / numMatrices;
        double axisX = static_cast<double>(rand()) / RAND_MAX;
        double axisY = static_cast<double>(rand()) / RAND_MAX;
        double axisZ = static_cast<double>(rand()) / RAND_MAX;

        Matrix3x3 rotationMatrix = createRotationMatrix(axisX, axisY, axisZ, angle);
        double matrixTrace = trace(rotationMatrix);

        angles.push_back(angle);
        traces.push_back(matrixTrace);

        // For debugging: Print each angle and corresponding trace
        cout << "Angle: " << angle << ", Trace: " << matrixTrace << endl;
    }

    // Note: You will need to export 'angles' and 'traces' to a file or another system for plotting

    return 0;
}

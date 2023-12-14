#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <array>

using namespace std;

using Matrix3x3 = array<array<double, 3>, 3>;

// Converts degrees to radians
double degToRad(double degrees) {
    return degrees * M_PI / 180.0;
}

// Converts radians to degrees
double radToDeg(double radians) {
    return radians * 180.0 / M_PI;
}

// Function to create rotation matrix from Euler angles (Z-Y-X convention)
Matrix3x3 eulerToRotationMatrix(double yaw, double pitch, double roll) {
    yaw = degToRad(yaw);
    pitch = degToRad(pitch);
    roll = degToRad(roll);

    Matrix3x3 Rx = { {
        {1, 0, 0},
        {0, cos(roll), -sin(roll)},
        {0, sin(roll), cos(roll)}
    } };

    Matrix3x3 Ry = { {
        {cos(pitch), 0, sin(pitch)},
        {0, 1, 0},
        {-sin(pitch), 0, cos(pitch)}
    } };

    Matrix3x3 Rz = { {
        {cos(yaw), -sin(yaw), 0},
        {sin(yaw), cos(yaw), 0},
        {0, 0, 1}
    } };

    // Combined rotation matrix, R = Rz * Ry * Rx
    Matrix3x3 R;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            R[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                R[i][j] += Rz[i][k] * Ry[k][j];
            }
        }
    }

    Matrix3x3 result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 3; ++k) {
                result[i][j] += R[i][k] * Rx[k][j];
            }
        }
    }

    return result;
}

// Function to extract Euler angles from a rotation matrix (Z-Y-X convention)
array<double, 3> rotationMatrixToEuler(const Matrix3x3& R) {
    double sy = sqrt(R[0][0] * R[0][0] + R[1][0] * R[1][0]);

    bool singular = sy < 1e-6; // If cos(y) (sy) is close to zero, singularity occurs

    double x, y, z;
    if (!singular) {
        x = atan2(R[2][1], R[2][2]);
        y = atan2(-R[2][0], sy);
        z = atan2(R[1][0], R[0][0]);
    }
    else {
        x = atan2(-R[1][2], R[1][1]);
        y = atan2(-R[2][0], sy);
        z = 0;
    }

    return { x, y, z }; // Returns Euler angles in radians
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

// Main function to demonstrate both conversions
int main() {
    // Example Euler angles
    double yaw = 30.0;    // Yaw in degrees
    double pitch = 45.0;  // Pitch in degrees
    double roll = 60.0;   // Roll in degrees

    // Convert Euler angles to rotation matrix
    Matrix3x3 rotationMatrix = eulerToRotationMatrix(yaw, pitch, roll);
    cout << "Rotation Matrix from Euler Angles:" << endl;
    printMatrix(rotationMatrix);

    // Convert rotation matrix back to Euler angles
    auto eulerAngles = rotationMatrixToEuler(rotationMatrix);
    cout << "\nEuler Angles from Rotation Matrix:" << endl;
    cout << "Yaw: " << radToDeg(eulerAngles[0]) << " degrees" << endl;
    cout << "Pitch: " << radToDeg(eulerAngles[1]) << " degrees" << endl;
    cout << "Roll: " << radToDeg(eulerAngles[2]) << " degrees" << endl;

    return 0;
}

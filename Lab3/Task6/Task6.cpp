#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <array>
#include <utility>

using namespace std;

using Matrix3x3 = array<array<double, 3>, 3>;
using Quaternion = array<double, 4>;
using Vector3 = array<double, 3>;

struct RotationRepresentations {
    Matrix3x3 rotationMatrix;
    array<double, 3> eulerAngles; // Yaw, Pitch, Roll
    pair<Vector3, double> axisAngle; // Axis and Angle
    Quaternion quaternion;
    Vector3 rotationVector;
};

// Converts degrees to radians
double degToRad(double degrees) {
    return degrees * M_PI / 180.0;
}

// Converts radians to degrees
double radToDeg(double radians) {
    return radians * 180.0 / M_PI;
}

// 0.Function to create rotation matrix from Euler angles (Z-Y-X convention)
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

// 1.Function to extract Euler angles from a rotation matrix (Z-Y-X convention)
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

//2. Rotation Matrix to Principal Euler Axis/Angle
pair<Vector3, double> rotationMatrixToAxisAngle(const Matrix3x3& R) {
    double angle = acos((R[0][0] + R[1][1] + R[2][2] - 1) / 2);
    double s = sqrt((R[2][1] - R[1][2]) * (R[2][1] - R[1][2])
        + (R[0][2] - R[2][0]) * (R[0][2] - R[2][0])
        + (R[1][0] - R[0][1]) * (R[1][0] - R[0][1])) / 2;
    double x = (R[2][1] - R[1][2]) / (2 * s);
    double y = (R[0][2] - R[2][0]) / (2 * s);
    double z = (R[1][0] - R[0][1]) / (2 * s);

    return { {x, y, z}, angle };
}

//3. Principal Euler Axis/Angle to Quaternion
Quaternion axisAngleToQuaternion(const Vector3& axis, double angle) {
    double halfAngle = angle / 2;
    double sinHalfAngle = sin(halfAngle);
    return { cos(halfAngle), axis[0] * sinHalfAngle, axis[1] * sinHalfAngle, axis[2] * sinHalfAngle };
}

//4. Quaternion to Principal Euler Axis/Angle
pair<Vector3, double> quaternionToAxisAngle(const Quaternion& q) {
    double angle = 2 * acos(q[0]);
    double s = sqrt(1 - q[0] * q[0]); // Assuming quaternion is normalized
    Vector3 axis = { q[1] / s, q[2] / s, q[3] / s };
    return { axis, angle };
}

//5. Principal Euler Axis/Angle to Rotation Vector
Vector3 axisAngleToRotationVector(const Vector3& axis, double angle) {
    return { axis[0] * angle, axis[1] * angle, axis[2] * angle };
}

//6. Rotation Vector to Principal Euler Axis/Angle
pair<Vector3, double> rotationVectorToAxisAngle(const Vector3& rotVec) {
    double angle = sqrt(rotVec[0] * rotVec[0] + rotVec[1] * rotVec[1] + rotVec[2] * rotVec[2]);
    Vector3 axis = { rotVec[0] / angle, rotVec[1] / angle, rotVec[2] / angle };
    return { axis, angle };
}

// 7 Function to create rotation matrix from axis and angle
Matrix3x3 createRotationMatrix(const Vector3& axis, double angle) {
    double x = axis[0], y = axis[1], z = axis[2];
    double magnitude = sqrt(x * x + y * y + z * z);
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;

    double cosA = cos(angle);
    double sinA = sin(angle);

    Matrix3x3 rotationMatrix = { {
        {cosA + x * x * (1 - cosA), x * y * (1 - cosA) - z * sinA, x * z * (1 - cosA) + y * sinA},
        {y * x * (1 - cosA) + z * sinA, cosA + y * y * (1 - cosA), y * z * (1 - cosA) - x * sinA},
        {z * x * (1 - cosA) - y * sinA, z * y * (1 - cosA) + x * sinA, cosA + z * z * (1 - cosA)}
    } };

    return rotationMatrix;
}

RotationRepresentations convertRotation(const RotationRepresentations& input, char inputType) {
    RotationRepresentations result;

    switch (inputType) {
    case 'r': // Rotation Matrix
        result.rotationMatrix = input.rotationMatrix;
        result.eulerAngles = rotationMatrixToEuler(input.rotationMatrix);
        result.axisAngle = rotationMatrixToAxisAngle(input.rotationMatrix);
        result.quaternion = axisAngleToQuaternion(result.axisAngle.first, result.axisAngle.second);
        result.rotationVector = axisAngleToRotationVector(result.axisAngle.first, result.axisAngle.second);
        break;
    case 'e': // Euler Angles
        result.rotationMatrix = eulerToRotationMatrix(input.eulerAngles[0], input.eulerAngles[1], input.eulerAngles[2]);
        result.eulerAngles = input.eulerAngles;
        result.axisAngle = rotationMatrixToAxisAngle(result.rotationMatrix);
        result.quaternion = axisAngleToQuaternion(result.axisAngle.first, result.axisAngle.second);
        result.rotationVector = axisAngleToRotationVector(result.axisAngle.first, result.axisAngle.second);
        break;
    case 'p': // Principal Euler Axis/Angle
        result.rotationMatrix = createRotationMatrix(input.axisAngle.first, input.axisAngle.second);
        result.eulerAngles = rotationMatrixToEuler(result.rotationMatrix);
        result.axisAngle = input.axisAngle;
        result.quaternion = axisAngleToQuaternion(input.axisAngle.first, input.axisAngle.second);
        result.rotationVector = axisAngleToRotationVector(input.axisAngle.first, input.axisAngle.second);
        break;
    case 'q': // Quaternion
        result.axisAngle = quaternionToAxisAngle(input.quaternion);
        result.rotationMatrix = createRotationMatrix(result.axisAngle.first, result.axisAngle.second);
        result.eulerAngles = rotationMatrixToEuler(result.rotationMatrix);
        result.quaternion = input.quaternion;
        result.rotationVector = axisAngleToRotationVector(result.axisAngle.first, result.axisAngle.second);
        break;
    case 'v': // Rotation Vector
        result.axisAngle = rotationVectorToAxisAngle(input.rotationVector);
        result.rotationMatrix = createRotationMatrix(result.axisAngle.first, result.axisAngle.second);
        result.eulerAngles = rotationMatrixToEuler(result.rotationMatrix);
        result.quaternion = axisAngleToQuaternion(result.axisAngle.first, result.axisAngle.second);
        result.rotationVector = input.rotationVector;
        break;
    }

    return result;
}




// Function to print Euler Angles
void printEulerAngles(const array<double, 3>& angles) {
    cout << "Euler Angles: Yaw = " << angles[0] << ", Pitch = " << angles[1] << ", Roll = " << angles[2] << endl;
}

// Function to print Rotation Matrix
void printRotationMatrix(const Matrix3x3& matrix) {
    cout << "Rotation Matrix:" << endl;
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Function to print Quaternion
void printQuaternion(const Quaternion& q) {
    cout << "Quaternion: (" << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3] << ")" << endl;
}

// Function to print Axis and Angle
void printAxisAngle(const pair<Vector3, double>& axisAngle) {
    cout << "Axis/Angle: Axis = (" << axisAngle.first[0] << ", "
        << axisAngle.first[1] << ", " << axisAngle.first[2]
        << "), Angle = " << axisAngle.second << endl;
}

// Function to print Rotation Vector
void printRotationVector(const Vector3& rotVec) {
    cout << "Rotation Vector: (" << rotVec[0] << ", " << rotVec[1] << ", " << rotVec[2] << ")" << endl;
}

int main() {
    // Example: Convert Euler Angles to all other representations
    RotationRepresentations input;
    input.eulerAngles = { 30.0, 45.0, 60.0 }; // Example Euler Angles

    RotationRepresentations result = convertRotation(input, 'e');

    // Print all representations
    printRotationMatrix(result.rotationMatrix);
    printEulerAngles(result.eulerAngles);
    printAxisAngle(result.axisAngle);
    printQuaternion(result.quaternion);
    printRotationVector(result.rotationVector);

    return 0;
}
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <array>

using namespace std;

using Matrix3x3 = array<array<double, 3>, 3>;
using Quaternion = array<double, 4>;
using Vector3 = array<double, 3>;

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


// Function to print a matrix
void printMatrix(const Matrix3x3& matrix) {
    for (const auto& row : matrix) {
        for (double value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}


int main() {
    // Example rotation matrix
    Matrix3x3 R = eulerToRotationMatrix(30, 45, 60);

    // Convert rotation matrix to Euler angles
    auto eulerAngles = rotationMatrixToEuler(R);
    cout << "Euler Angles: Yaw = " << radToDeg(eulerAngles[0])
        << ", Pitch = " << radToDeg(eulerAngles[1])
        << ", Roll = " << radToDeg(eulerAngles[2]) << endl;

    // Convert rotation matrix to axis/angle
    auto axisAngle = rotationMatrixToAxisAngle(R);
    cout << "Axis/Angle: Axis = (" << axisAngle.first[0] << ", "
        << axisAngle.first[1] << ", " << axisAngle.first[2]
        << "), Angle = " << radToDeg(axisAngle.second) << " degrees" << endl;

    // Convert axis/angle to quaternion
    Quaternion q = axisAngleToQuaternion(axisAngle.first, axisAngle.second);
    cout << "Quaternion: (" << q[0] << ", " << q[1] << ", "
        << q[2] << ", " << q[3] << ")" << endl;

    // Convert quaternion back to axis/angle
    auto axisAngleFromQ = quaternionToAxisAngle(q);
    cout << "Axis/Angle from Quaternion: Axis = (" << axisAngleFromQ.first[0] << ", "
        << axisAngleFromQ.first[1] << ", " << axisAngleFromQ.first[2]
        << "), Angle = " << radToDeg(axisAngleFromQ.second) << " degrees" << endl;

    // Convert axis/angle to rotation vector
    Vector3 rotVec = axisAngleToRotationVector(axisAngle.first, axisAngle.second);
    cout << "Rotation Vector: (" << rotVec[0] << ", " << rotVec[1] << ", "
        << rotVec[2] << ")" << endl;

    // Convert rotation vector back to axis/angle
    auto axisAngleFromRV = rotationVectorToAxisAngle(rotVec);
    cout << "Axis/Angle from Rotation Vector: Axis = (" << axisAngleFromRV.first[0] << ", "
        << axisAngleFromRV.first[1] << ", " << axisAngleFromRV.first[2]
        << "), Angle = " << radToDeg(axisAngleFromRV.second) << " degrees" << endl;

    return 0;
}

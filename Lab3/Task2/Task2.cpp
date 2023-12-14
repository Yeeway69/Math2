#include <iostream>
#include <array>

using namespace std;

// Define a type for quaternion
using Quaternion = array<double, 4>;

// Function for quaternion multiplication
Quaternion quaternionMultiply(const Quaternion& q1, const Quaternion& q2) {
    Quaternion result;
    result[0] = q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2] - q1[3] * q2[3]; // w
    result[1] = q1[0] * q2[1] + q1[1] * q2[0] + q1[2] * q2[3] - q1[3] * q2[2]; // x
    result[2] = q1[0] * q2[2] - q1[1] * q2[3] + q1[2] * q2[0] + q1[3] * q2[1]; // y
    result[3] = q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1] + q1[3] * q2[0]; // z
    return result;
}

// Function to rotate a vector using a quaternion
array<double, 3> rotateVectorByQuaternion(const array<double, 3>& vec, const Quaternion& quat) {
    Quaternion vecQuat = { 0, vec[0], vec[1], vec[2] };
    Quaternion quatConj = { quat[0], -quat[1], -quat[2], -quat[3] };
    Quaternion rotatedQuat = quaternionMultiply(quaternionMultiply(quat, vecQuat), quatConj);

    return { rotatedQuat[1], rotatedQuat[2], rotatedQuat[3] };
}

// Main function
int main() {
    // Example usage
    Quaternion q = { 0.70710678118, 0, 0.70710678118, 0 }; // Example quaternion (90-degree rotation about Y-axis)
    array<double, 3> v = { 1, 0, 0 }; // Example vector

    array<double, 3> rotatedVector = rotateVectorByQuaternion(v, q);

    // Print the rotated vector
    cout << "Rotated Vector: ";
    for (const auto& component : rotatedVector) {
        cout << component << " ";
    }
    cout << endl;

    return 0;
}


import math
import numpy as np

def quaternion_from_euler_angles(roll, pitch, yaw):
    cy = math.cos(yaw * 0.5)
    sy = math.sin(yaw * 0.5)
    cp = math.cos(pitch * 0.5)
    sp = math.sin(pitch * 0.5)
    cr = math.cos(roll * 0.5)
    sr = math.sin(roll * 0.5)

    qw = cr * cp * cy + sr * sp * sy
    qx = sr * cp * cy - cr * sp * sy
    qy = cr * sp * cy + sr * cp * sy
    qz = cr * cp * sy - sr * sp * cy

    return np.array([qw, qx, qy, qz])



def rotation_matrix_from_euler_angles(roll, pitch, yaw):
    R_x = np.array([[1, 0, 0],
                    [0, math.cos(roll), -math.sin(roll)],
                    [0, math.sin(roll), math.cos(roll)]])
    
    R_y = np.array([[math.cos(pitch), 0, math.sin(pitch)],
                    [0, 1, 0],
                    [-math.sin(pitch), 0, math.cos(pitch)]])
    
    R_z = np.array([[math.cos(yaw), -math.sin(yaw), 0],
                    [math.sin(yaw), math.cos(yaw), 0],
                    [0, 0, 1]])
    
    R = np.dot(R_z, np.dot(R_y, R_x))
    return R


def euler_angles_from_quaternion(q):
    # Assuming quaternion is of the form [w, x, y, z]
    qw, qx, qy, qz = q
    t0 = +2.0 * (qw * qx + qy * qz)
    t1 = +1.0 - 2.0 * (qx * qx + qy * qy)
    roll_x = math.atan2(t0, t1)
    
    t2 = +2.0 * (qw * qy - qz * qx)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    pitch_y = math.asin(t2)
    
    t3 = +2.0 * (qw * qz + qx * qy)
    t4 = +1.0 - 2.0 * (qy * qy + qz * qz)
    yaw_z = math.atan2(t3, t4)
    
    return roll_x, pitch_y, yaw_z  # in radians


def rotation_vector_from_euler_angles(roll, pitch, yaw):
    R = rotation_matrix_from_euler_angles(roll, pitch, yaw)
    theta = math.acos((np.trace(R) - 1) / 2)
    omega = np.array([(R[2, 1] - R[1, 2]),
                      (R[0, 2] - R[2, 0]),
                      (R[1, 0] - R[0, 1])]) / (2 * math.sin(theta))
    rotation_vector = theta * omega
    return rotation_vector

def principal_angle_axis_from_rotation_matrix(R):
    theta = math.acos((np.trace(R) - 1) / 2)
    sin_theta = math.sin(theta)

    if sin_theta == 0:
        return 0, (0, 0, 0)  # No rotation or undefined axis

    u_x = (R[2, 1] - R[1, 2]) / (2 * sin_theta)
    u_y = (R[0, 2] - R[2, 0]) / (2 * sin_theta)
    u_z = (R[1, 0] - R[0, 1]) / (2 * sin_theta)

    return math.degrees(theta), (u_x, u_y, u_z)

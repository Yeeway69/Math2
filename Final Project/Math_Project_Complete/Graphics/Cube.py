import pygame

import math
import numpy as np

class Cube:
    def __init__(self):
        # Cube size
        self.size = 50
        # Vertices of a cube
        self.vertices = [
            [1, -1, -1],
            [1, 1, -1],
            [-1, 1, -1],
            [-1, -1, -1],
            [1, -1, 1],
            [1, 1, 1],
            [-1, 1, 1],
            [-1, -1, 1]
        ]
        # Scale the cube size
        self.vertices = [[self.size * x, self.size * y, self.size * z] for x, y, z in self.vertices]
        # Edges between the vertices
        self.edges = [
            (0, 1), (1, 2), (2, 3), (3, 0), # Bottom vertices
            (4, 5), (5, 6), (6, 7), (7, 4), # Top vertices
            (0, 4), (1, 5), (2, 6), (3, 7)  # Side edges connecting top and bottom vertices
        ]
        # Initialize Euler angles (roll, pitch, yaw) in radians
        self.roll = 0
        self.pitch = 0
        self.yaw = 0

    def rotate_x(self, angle):
        # Rotate the cube around the X axis by the given angle
        cos_theta, sin_theta = math.cos(angle), math.sin(angle)
        for i, vertex in enumerate(self.vertices):
            x, y, z = vertex
            self.vertices[i] = [x, y * cos_theta - z * sin_theta, y * sin_theta + z * cos_theta]
        
        # Update the roll angle    
        self.roll += angle  

    def rotate_y(self, angle):
        # Rotate the cube around the Y axis by the given angle
        cos_theta, sin_theta = math.cos(angle), math.sin(angle)
        for i, vertex in enumerate(self.vertices):
            x, y, z = vertex
            self.vertices[i] = [x * cos_theta + z * sin_theta, y, -x * sin_theta + z * cos_theta]

        # Update the pitch angle
        self.pitch += angle
    def draw(self, screen):
        # Draw the cube on the screen
        width, height = screen.get_size()
        center_x, center_y = width // 4, height // 2
        scale = 2  # Adjust if the cube is too large or too small
        fov = 100  # Field of View
        viewer_distance = 5

        # Create a list to hold the depth of each edge
        edge_depths = []
        for edge in self.edges:
            # Calculate the average z value of the vertices that make up the edge
            z1 = self.vertices[edge[0]][2]
            z2 = self.vertices[edge[1]][2]
            average_z = (z1 + z2) / 2
            edge_depths.append((edge, average_z))
            
        # Sort the edges by their average z value in descending order
        edge_depths.sort(key=lambda x: x[1], reverse=True)

        

        # Draw the edges starting with the furthest away
        for edge, _ in edge_depths:
            points = []
            for vertex in edge:
                x, y, z = self.vertices[vertex]
                # Apply perspective projection to map 3D coordinates to 2D
                if z > 0:  # This ensures we're not trying to project points that are 'behind' the viewer
                    factor = fov / (fov + z)
                    x, y = x * factor, y * factor
                    # Convert the projected points to screen space (2D)
                    screen_x, screen_y = (center_x + int(x * scale), center_y - int(y * scale))
                    points.append((screen_x, screen_y))
            if len(points) > 1:
               pygame.draw.line(screen, (255, 255, 255), points[0], points[1], 1)

                
    def apply_rotation(self, rotation_matrix):
        # Apply the rotation matrix to each vertex
        for i, vertex in enumerate(self.vertices):
            # Convert the vertex list to a NumPy array for matrix multiplication
            rotated_vertex = np.dot(rotation_matrix, np.array(vertex).reshape(3, 1))
            # Update the vertex with the new rotated coordinates
            self.vertices[i] = rotated_vertex.flatten().tolist()
            
    def get_euler_angles(self):
        # Return the current Euler angles in degrees
        return math.degrees(self.roll), math.degrees(self.pitch), math.degrees(self.yaw)
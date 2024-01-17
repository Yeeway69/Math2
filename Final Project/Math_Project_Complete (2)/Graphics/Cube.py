import pygame
import math

class Cube:
    def __init__(self):
        # Vertices of a cube
        self.vertices = [
            [-1, -1, -1],
            [1, -1, -1],
            [1, 1, -1],
            [-1, 1, -1],
            [-1, -1, 1],
            [1, -1, 1],
            [1, 1, 1],
            [-1, 1, 1]
        ]

        # Edges that connect vertices
        self.edges = [
            (0, 1), (1, 2), (2, 3), (3, 0),
            (4, 5), (5, 6), (6, 7), (7, 4),
            (0, 4), (1, 5), (2, 6), (3, 7)
        ]

        # Rotation angles
        self.angle_x = 0
        self.angle_y = 0
        self.angle_z = 0

    def rotate_x(self, angle):
        # Rotate the cube around the X axis by the given angle
        cos_theta, sin_theta = math.cos(angle), math.sin(angle)
        for i, vertex in enumerate(self.vertices):
            x, y, z = vertex
            self.vertices[i] = [x, y * cos_theta - z * sin_theta, y * sin_theta + z * cos_theta]

    def rotate_y(self, angle):
        # Rotate the cube around the Y axis by the given angle
        cos_theta, sin_theta = math.cos(angle), math.sin(angle)
        for i, vertex in enumerate(self.vertices):
            x, y, z = vertex
            self.vertices[i] = [x * cos_theta + z * sin_theta, y, -x * sin_theta + z * cos_theta]

    def rotate_z(self, angle):
        # Rotate the cube around the Z axis by the given angle
        cos_theta, sin_theta = math.cos(angle), math.sin(angle)
        for i, vertex in enumerate(self.vertices):
            x, y, z = vertex
            self.vertices[i] = [x * cos_theta - y * sin_theta, x * sin_theta + y * cos_theta, z]

    def draw(self, screen):
        # Draw the cube on the screen
        width, height = screen.get_size()
        for edge in self.edges:
            points = []
            for vertex in edge:
                x, y, z = self.vertices[vertex]
                # Perspective projection
                factor = 500 / (5 + z)
                x, y = x * factor + width // 2, -y * factor + height // 2
                points.append((x, y))
            pygame.draw.line(screen, (255, 255, 255), points[0], points[1], 1)
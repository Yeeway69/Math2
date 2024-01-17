import pygame
import math

class Cube:
    def __init__(self):
        # Cube size
        self.size = 50
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
        # Scale the cube size
        self.vertices = [[self.size * x, self.size * y, self.size * z] for x, y, z in self.vertices]
        # Edges between the vertices
        self.edges = [
            (0, 1), (1, 2), (2, 3), (3, 0), # Bottom vertices
            (4, 5), (5, 6), (6, 7), (7, 4), # Top vertices
            (0, 4), (1, 5), (2, 6), (3, 7)  # Side edges connecting top and bottom vertices
        ]

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

    def draw(self, screen):
        # Draw the cube on the screen
        width, height = screen.get_size()
        center_x, center_y = width // 4, height // 2
        scale = 20  # Adjust if the cube is too large or too small
        fov = 300  # Field of View
        viewer_distance = 5

        # Sort the edges by the furthest away z value
        sorted_edges = sorted(self.edges, key=lambda edge: max(self.vertices[edge[0]][2], self.vertices[edge[1]][2]), reverse=True)

        for edge in sorted_edges:
            points = []
            for vertex in edge:
                x, y, z = self.vertices[vertex]
                # Perspective projection
                if z > -viewer_distance:
                    factor = fov / (viewer_distance + z)
                    x, y = x * factor + center_x, -y * factor + center_y
                    points.append((x, y))
            if len(points) == 2:
                pygame.draw.line(screen, (255, 255, 255), points[0], points[1], 2)
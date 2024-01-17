import pygame
import math

class Cube:
    def __init__(self):
        # Size of the cube (scale it up)
        self.size = 100

        # Vertices of a cube (scaled)
        self.vertices = [
            [self.size, -self.size, -self.size],
            [self.size, self.size, -self.size],
            [-self.size, self.size, -self.size],
            [-self.size, -self.size, -self.size],
            [self.size, -self.size, self.size],
            [self.size, self.size, self.size],
            [-self.size, -self.size, self.size],
            [-self.size, self.size, self.size]
        ]

        # Edges that connect vertices
        self.edges = [
            (0, 1), (1, 2), (2, 3), (3, 0),
            (4, 5), (5, 6), (6, 7), (7, 4),
            (0, 4), (1, 5), (2, 6), (3, 7)
        ]

    def rotate_x(self, angle):
        cos_theta, sin_theta = math.cos(angle), math.sin(angle)
        for i, vertex in enumerate(self.vertices):
            x, y, z = vertex
            self.vertices[i] = [x, y * cos_theta - z * sin_theta, y * sin_theta + z * cos_theta]

    def rotate_y(self, angle):
        cos_theta, sin_theta = math.cos(angle), math.sin(angle)
        for i, vertex in enumerate(self.vertices):
            x, y, z = vertex
            self.vertices[i] = [x * cos_theta + z * sin_theta, y, -x * sin_theta + z * cos_theta]

    def draw(self, screen):
        width, height = screen.get_size()
        center_x, center_y = width // 4, height // 2
        scale = 100
        fov = 200
        viewer_distance = 5

        for edge in self.edges:
            points = []
            for vertex in edge:
                x, y, z = [v * scale for v in self.vertices[vertex]]
                if z > -viewer_distance:
                    factor = fov / (viewer_distance + z)
                    x, y = x * factor + center_x, -y * factor + center_y
                    points.append((x, y))
                else:
                    break
            if len(points) == 2:
                pygame.draw.line(screen, (255, 255, 255), points[0], points[1], 2)

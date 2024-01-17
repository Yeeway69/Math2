import pygame

def handle_keyboard_events(event, cube):
    if event.type == pygame.KEYDOWN:
        if event.key == pygame.K_LEFT:
            cube.rotate_y(-0.1)
        elif event.key == pygame.K_RIGHT:
            cube.rotate_y(0.1)
        elif event.key == pygame.K_UP:
            cube.rotate_x(-0.1)
        elif event.key == pygame.K_DOWN:
            cube.rotate_x(0.1)
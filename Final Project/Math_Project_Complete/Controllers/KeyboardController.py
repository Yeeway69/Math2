import pygame

# Initialize a dictionary to keep track of which keys are pressed
key_state = {
    pygame.K_LEFT: False,
    pygame.K_RIGHT: False,
    pygame.K_UP: False,
    pygame.K_DOWN: False
}

def handle_keyboard_events(event, cube):
    # Update the key_state when a key is pressed down
    if event.type == pygame.KEYDOWN:
        if event.key in key_state:
            key_state[event.key] = True

    # Update the key_state when a key is released
    elif event.type == pygame.KEYUP:
        if event.key in key_state:
            key_state[event.key] = False

    # Apply rotation based on the key_state
    if key_state[pygame.K_LEFT]:
        cube.rotate_y(-0.1)
    if key_state[pygame.K_RIGHT]:
        cube.rotate_y(0.1)
    if key_state[pygame.K_UP]:
        cube.rotate_x(-0.1)
    if key_state[pygame.K_DOWN]:
        cube.rotate_x(0.1)

import pygame
import sys
from Graphics.Cube import Cube
from Controllers.KeyboardController import handle_keyboard_events
from UI.MainUI import update_ui

# Initialize Pygame
pygame.init()

# Screen dimensions
WIDTH, HEIGHT = 800, 600

# Set up the display
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('3D Cube Visualization')

# Create a Cube object
cube = Cube()

# Main loop

running = True


while running:
     
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        # Handle keyboard events
        handle_keyboard_events(event, cube)
        # Clear the screen with a background color at the start of each frame
    screen.fill((0, 0, 0))  # Fill the screen with black (or any other color that contrasts with the cube)
    # Define the left and right zones
    left_zone_width = screen.get_width() // 2
    right_zone_width = screen.get_width() - left_zone_width
     # Draw the left zone background
    left_zone_surface = pygame.Surface((left_zone_width, screen.get_height()))
    left_zone_surface.fill((50, 50, 50))  # A different shade for the cube's zone
    screen.blit(left_zone_surface, (0, 0))
    # # Draw the cube
    # cube.draw(screen)
    # Draw the cube in the left zone
    cube.draw(screen.subsurface((0, 0, left_zone_width, screen.get_height())))
    # Update UI in the right zone
    update_ui(screen.subsurface((left_zone_width, 0, right_zone_width, screen.get_height())), cube)
    # Handle keyboard events
    handle_keyboard_events(event, cube)

    # Update cube and UI
    update_ui(screen, cube)

    # Update the display
    pygame.display.flip()
    
 # Cap the frame rate
    pygame.time.Clock().tick(60)  # Cap at 60 frames per second

# Quit Pygame
pygame.quit()
sys.exit()
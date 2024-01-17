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

    # Update cube and UI
    
    update_ui(screen, cube)

    # Update the display
    pygame.display.flip()

# Quit Pygame
pygame.quit()
sys.exit()
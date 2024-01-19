
from datetime import timedelta
from msilib.schema import SelfReg
import pygame
import pygame_gui
import sys
from Graphics.Cube import Cube
from Controllers.KeyboardController import handle_keyboard_events
from UI.MainUI import create_ui_elements, update_ui, initialize_ui, MainUI
from Math.Transformations import rotation_matrix_from_euler_angles, quaternion_from_euler_angles, rotation_vector_from_euler_angles, principal_angle_axis_from_rotation_matrix
import numpy as np

# Initialize Pygame
pygame.init()

# Screen dimensions
WIDTH, HEIGHT = 800, 600

# Set up the display
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('3D Cube Visualization')

manager = pygame_gui.UIManager((WIDTH, HEIGHT))
# MainUI.initialize_ui(manager)
# Now you can create your UI elements like buttons, text entry lines, etc.
reset_button = pygame_gui.elements.UIButton(relative_rect=pygame.Rect((650, 550), (100, 50)),
                                            text='Reset',
                                            manager=manager)

# In your main file, after creating the UIManager instance

ui_elements = create_ui_elements(manager)

# Create a Cube object
cube = Cube()

# Function to get user input for Euler angles (placeholder)
def get_user_input_euler_angles():
    
    return 0, 0, 0  # Placeholder values


# Main loop

running = True

current_time = pygame.time.get_ticks()

previous_time = current_time
current_time = pygame.time.get_ticks()
timedelta = current_time - previous_time
manager.update(timedelta)
while running:
    time_delta = pygame.time.Clock().tick(60)/1000.0
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.USEREVENT:
            if event.user_type == pygame_gui.UI_BUTTON_PRESSED:
                if event.ui_element == ui_elements['button_update']:
                   # Code to handle the button press, update the cube's orientation, and other UI elements
                   pass

        manager.process_events(event)
        if event.type == pygame.QUIT:
            running = False
        # Handle pygame_gui events here
        manager.process_events(event)
        if event.type == pygame.USEREVENT:
            if event.user_type == pygame_gui.UI_BUTTON_PRESSED:
                if event.ui_element == reset_button:
                    # Reset functionality
                    cube.reset_orientation()
                    # Create an instance of MainUI
                    main_ui = MainUI(manager)
                    main_ui.reset_ui() # Call the reset method of your ui instance
                    pass
    # Handle keyboard events
    handle_keyboard_events(event, cube)   
    
    # Update cube's orientation based on user input
    
    roll, pitch, yaw = get_user_input_euler_angles()
    rotation_matrix = rotation_matrix_from_euler_angles(roll, pitch, yaw)
    cube.apply_rotation(rotation_matrix)
    
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
     # Calculate the attitude representations
    euler_angles = cube.get_euler_angles()  # Assuming this returns roll, pitch, yaw
    quaternion = quaternion_from_euler_angles(*euler_angles)
    rotation_matrix = rotation_matrix_from_euler_angles(*euler_angles)
    rotation_vector = rotation_vector_from_euler_angles(*euler_angles)
    # Calculate Principal Angle and Axis
    principal_angle, principal_axis = principal_angle_axis_from_rotation_matrix(rotation_matrix)
    # # Update UI in the right zone
    # update_ui(screen.subsurface((left_zone_width, 0, right_zone_width, screen.get_height())), cube)
    

    # Update cube and UI
    update_ui(screen,euler_angles, quaternion, rotation_matrix, rotation_vector, principal_angle, principal_axis, cube)

  
    
 # Cap the frame rate
    pygame.time.Clock().tick(60)  # Cap at 60 frames per second
    
 # Update the UIManager and draw the UI
    manager.update(time_delta)
    manager.draw_ui(screen)
      # Update the display
    pygame.display.flip()
    pygame.display.update()

# Quit Pygame
pygame.quit()
sys.exit()
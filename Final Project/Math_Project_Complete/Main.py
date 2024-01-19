import pygame
import sys
from Graphics.Cube import Cube
from Controllers.KeyboardController import handle_keyboard_events
from UI.MainUI import update_ui
from Math.Transformations import rotation_matrix_from_euler_angles, quaternion_from_euler_angles, rotation_vector_from_euler_angles, principal_angle_axis_from_rotation_matrix

# Initialize Pygame
pygame.init()

# Screen dimensions
WIDTH, HEIGHT = 800, 600

# Set up the display
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('3D Cube Visualization')

# Create a Cube object
cube = Cube()

# Function to get user input for Euler angles (placeholder)
def get_user_input_euler_angles():
    
    return 0, 0, 0  # Placeholder values


# Main loop

running = True



while running:
     
    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
    # Handle keyboard events
    handle_keyboard_events(event, cube)   
    
    # Update cube's orientation based on user input
    # TODO: Replace this with actual input handling logic
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

    # Update the display
    pygame.display.flip()
    
 # Cap the frame rate
    pygame.time.Clock().tick(60)  # Cap at 60 frames per second

# Quit Pygame
pygame.quit()
sys.exit()
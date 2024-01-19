from logging import Manager
from multiprocessing import managers


import pygame
import pygame_gui
from pygame_gui.core.interfaces import manager_interface
from pygame_gui.elements import UITextEntryLine, UIButton
from Math.Transformations import quaternion_from_euler_angles
import numpy as np

# MainUI.py

# Define the UI elements at the module level
entry_quaternion = None
entry_euler_angles = None
entry_rotation_vector = None
reset_button = None
# MainUI.py
class MainUI:
    def __init__(self, manager):
        self.manager = manager
        self.initialize_ui()
        
    def initialize_ui(self):
        # Create UI elements here
        self.entry_quaternion = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 20), (200, 50)), manager=self.manager)
        self.entry_euler_angles = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 85), (200, 30)), manager=self.manager)
        self.entry_rotation_vector = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 150), (200, 30)), manager=self.manager)
        self.entry_rotation_matrix = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 230), (200, 30)), manager=self.manager)
        self.entry_principle_Angle = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 290), (200, 30)), manager=self.manager)
        self.entry_principle_Matrix = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 350), (200, 30)), manager=self.manager)
        self.button_update = pygame_gui.elements.UIButton(relative_rect=pygame.Rect((420, 400), (100, 50)), text='Update', manager=self.manager)

        
    def reset_ui(self):
        
        self.entry_quaternion.set_text('0,0,0,1')
        self.entry_euler_angles.set_text('0,0,0')
        self.entry_rotation_vector.set_text('0,0,0')
        self.entry_rotation_matrix.set_text('1,0,0;0,1,0;0,0,1')
        self.entry_principle_Angle.set_text('0')
        self.entry_principle_Matrix.set_text('1,0,0;0,1,0;0,0,1')
        
        
        # ... reset other UI elements ...

def initialize_ui(manager):
    global entry_quaternion, entry_euler_angles, entry_rotation_vector, reset_button
    
    # Initialize the UI elements
    entry_quaternion = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 20), (200, 50)), manager=manager)
    # ... Initialize other UI elements similarly
    
    reset_button = pygame_gui.elements.UIButton(relative_rect=pygame.Rect((650, 550), (100, 50)),
                                                text='Reset',
                                                manager=manager)


def create_ui_elements(manager):
    # Create text entry lines for each editable representation
    entry_quaternion = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 40), (200, 30)), manager=manager)
    entry_euler_angles = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 85), (200, 30)), manager=manager)
    entry_rotation_vector = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 150), (200, 30)), manager=manager)
    entry_rotaion_matrix = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 230), (200, 30)), manager=manager)
    entry_principle_Angle = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 290), (200, 30)), manager=manager)
    entry_principle_Matrix = pygame_gui.elements.UITextEntryLine(relative_rect=pygame.Rect((420, 350), (200, 30)), manager=manager)
    # Create a button for updating the attitude
    button_update = pygame_gui.elements.UIButton(relative_rect=pygame.Rect((420, 400), (100, 50)), text='Update', manager=manager)

    return {
        'entry_quaternion': entry_quaternion,
        'entry_euler_angles': entry_euler_angles,
        'entry_rotation_vector': entry_rotation_vector,
        'entry_rotation_matrix': entry_rotaion_matrix,
        'entry_principle_Angle': entry_principle_Angle,
        'entry_principle_Matrix': entry_principle_Matrix,
        'button_update': button_update
    }

def draw_text(screen, text, position, font_size=20, color=(255, 255, 255)):
    font = pygame.font.Font(None, font_size)
    text_surface = font.render(text, True, color)
    screen.blit(text_surface, position)

def update_ui(screen, euler_angles, quaternion, rotation_matrix, rotation_vector, principal_angle, principal_axis, cube):
    # Placeholder for UI components
    # Displaying attitude representation placeholders
# Display Euler angles
    draw_text(screen, f'Euler Angles: Roll: {euler_angles[0]:.2f}, Pitch: {euler_angles[1]:.2f}, Yaw: {euler_angles[2]:.2f}', (420, 70))
     # Convert numpy arrays to string for display

    
    
    quaternion_str = np.array2string(quaternion, precision=2, separator=', ')
    rotation_matrix_str = np.array2string(rotation_matrix, precision=2, separator=', ')
    rotation_vector_str = np.array2string(rotation_vector, precision=2, separator=', ')
    # Display Principal Angle and Axis
    principal_axis_str = f"({principal_axis[0]:.2f}, {principal_axis[1]:.2f}, {principal_axis[2]:.2f})"
    draw_text(screen, f'Principal Angle: {principal_angle:.2f} degrees', (420, 260))
    draw_text(screen, f'Principal Axis: {principal_axis_str}', (420, 320))
     # Display Quaternion
    draw_text(screen, f'Quaternion: {quaternion_str}', (420, 20))
    
    # Display Rotation Vector
    draw_text(screen, f'Rotation Vector: {rotation_vector_str}', (420, 140))

    # Display Rotation Matrix
    draw_text(screen, f'Rotation Matrix: {rotation_matrix_str}', (420, 180))
    
    # # Update the pygame_gui elements
    # time_delta = pygame.time.Clock().tick(60)/1000.0
    # manager.update(time_delta)
    # manager.draw_ui(screen)
    

    # draw_text(screen, 'Attitude Representation', (20, 20), font_size=30)
    # draw_text(screen, 'Euler Principal Angle & Axis: TBD', (420, 60))
    # draw_text(screen, 'Euler Angles: TBD', (420, 100))
    # draw_text(screen, 'Rotation Vector: TBD', (420, 140))
    # draw_text(screen, 'Rotation Matrix: TBD', (420, 180))
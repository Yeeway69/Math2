
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QHBoxLayout, QVBoxLayout, QLabel, QLineEdit, QPushButton
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QOpenGLWidget
from OpenGL.GL import *
from OpenGL.GLU import *

class CubeWidget(QOpenGLWidget):
    def __init__(self, parent=None):
        super(CubeWidget, self).__init__(parent)
        self.setFocusPolicy(Qt.StrongFocus)  # Set focus policy

    def initializeGL(self):
        glClearColor(0, 0, 0, 1)
        glEnable(GL_DEPTH_TEST)

    def resizeGL(self, w, h):
        glViewport(0, 0, w, h)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(45, float(w)/h, 0.1, 50.0)
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def paintGL(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        glTranslatef(0, 0, -5)
        self.drawCube()

    def drawCube(self):
        glBegin(GL_QUADS)

        # Front face (red)
        glColor3f(1, 0, 0)
        glVertex3f(-1, -1, 1)
        glVertex3f(1, -1, 1)
        glVertex3f(1, 1, 1)
        glVertex3f(-1, 1, 1)

        # Back face (green)
        glColor3f(0, 1, 0)
        glVertex3f(-1, -1, -1)
        glVertex3f(-1, 1, -1)
        glVertex3f(1, 1, -1)
        glVertex3f(1, -1, -1)

        # Top face (blue)
        glColor3f(0, 0, 1)
        glVertex3f(-1, 1, -1)
        glVertex3f(-1, 1, 1)
        glVertex3f(1, 1, 1)
        glVertex3f(1, 1, -1)

        # Bottom face (yellow)
        glColor3f(1, 1, 0)
        glVertex3f(-1, -1, -1)
        glVertex3f(1, -1, -1)
        glVertex3f(1, -1, 1)
        glVertex3f(-1, -1, 1)

        # Right face (purple)
        glColor3f(1, 0, 1)
        glVertex3f(1, -1, -1)
        glVertex3f(1, 1, -1)
        glVertex3f(1, 1, 1)
        glVertex3f(1, -1, 1)

        # Left face (cyan)
        glColor3f(0, 1, 1)
        glVertex3f(-1, -1, -1)
        glVertex3f(-1, -1, 1)
        glVertex3f(-1, 1, 1)
        glVertex3f(-1, 1, -1)

        glEnd()
        
        error = glGetError()
        if error != GL_NO_ERROR:
            print('OpenGL error:', gluErrorString(error))

    def keyPressEvent(self, event):
        if event.key() == Qt.Key_Left:
            glRotatef(5, 0, 1, 0)
        elif event.key() == Qt.Key_Right:
            glRotatef(-5, 0, 1, 0)
        elif event.key() == Qt.Key_Up:
            glRotatef(5, 1, 0, 0)
        elif event.key() == Qt.Key_Down:
            glRotatef(-5, 1, 0, 0)
        self.update()

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("3D Cube Rotation and Attitude Representation")
        self.setGeometry(100, 100, 800, 600)
        self.initUI()

    def initUI(self):
        central_widget = QWidget(self)
        self.setCentralWidget(central_widget)
        layout = QHBoxLayout(central_widget)
        self.left_zone = CubeWidget()
        self.right_zone = QWidget()
        layout.addWidget(self.left_zone)
        layout.addWidget(self.right_zone)
        self.initRightZone()

    def initRightZone(self):
        right_layout = QVBoxLayout(self.right_zone)
        # Attitude representation panels
        self.quaternion_panel = QLineEdit("Quaternion")
        self.euler_angle_panel = QLineEdit("Euler Angle")
        self.rotation_vector_panel = QLineEdit("Rotation Vector")
        self.rotation_matrix_panel = QLabel("Rotation Matrix")
        right_layout.addWidget(self.quaternion_panel)
        right_layout.addWidget(self.euler_angle_panel)
        right_layout.addWidget(self.rotation_vector_panel)
        right_layout.addWidget(self.rotation_matrix_panel)
        # Reset button
        self.reset_button = QPushButton("Reset")
        right_layout.addWidget(self.reset_button)
        self.reset_button.clicked.connect(self.resetCubeAndPanels)
        self.right_zone.setLayout(right_layout)

    def resetCubeAndPanels(self):
        # Reset rotation to initial state
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()
        glTranslatef(0, 0, -5)
        self.left_zone.update()
        
        # Reset text fields
        self.quaternion_panel.setText("Quaternion")
        self.euler_angle_panel.setText("Euler Angle")
        self.rotation_vector_panel.setText("Rotation Vector")
        self.rotation_matrix_panel.setText("Rotation Matrix")
    

def main():
    app = QApplication(sys.argv)
    main_window = MainWindow()
    main_window.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    main()

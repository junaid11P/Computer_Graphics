// testopenGLwindow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>

void drawTriangle(float x, float y, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    
    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    glVertex2f(0.0f,  0.2f);    // Top
    glVertex2f(-0.2f, -0.2f);   // Bottom left
    glVertex2f(0.2f, -0.2f);    // Bottom right
    glEnd();
    
    glPopMatrix();
}

int main(void) {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Two Triangles", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Single frame render
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw yellow triangle on the left
    drawTriangle(-0.5f, 0.0f, 1.0f, 1.0f, 0.0f);
    
    // Draw green triangle on the right
    drawTriangle(0.5f, 0.0f, 0.0f, 1.0f, 0.0f);

    glfwSwapBuffers(window);

    // Wait for window close
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
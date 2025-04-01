// testopenGLwindow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

struct Triangle {
    float x;
    float y;
    float speedX;
    float speedY;
    float angle;
    float color[3];
};

void drawTriangle(float angle, float x, float y, float color[3]) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    
    glBegin(GL_TRIANGLES);
    glColor3f(color[0], color[1], color[2]);
    glVertex2f(0.0f,  0.2f);      // Top
    glVertex2f(-0.2f, -0.2f);     // Bottom left
    glVertex2f(0.2f, -0.2f);      // Bottom right
    glEnd();
    
    glPopMatrix();
}

void updateTriangle(Triangle& tri) {
    // Update position
    tri.x += tri.speedX;
    tri.y += tri.speedY;
    
    // Bounce off edges
    if (tri.x > 0.8f || tri.x < -0.8f) {
        tri.speedX = -tri.speedX;
    }
    if (tri.y > 0.8f || tri.y < -0.8f) {
        tri.speedY = -tri.speedY;
    }
    
    // Update rotation
    tri.angle += 1.0f;
    if (tri.angle > 360.0f) {
        tri.angle -= 360.0f;
    }
}

int main(void) {
    /* Initialize GLFW */
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    /* Create window */
    GLFWwindow* window = glfwCreateWindow(800, 680, "Bouncing Triangles", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize triangles
    Triangle tri1 = {
        -0.4f,                     // x
        0.0f,                      // y
        0.01f,                     // speedX
        0.005f,                    // speedY
        0.0f,                      // angle
        {1.0f, 1.0f, 0.0f}        // yellow color
    };

    Triangle tri2 = {
        0.4f,                      // x
        0.0f,                      // y
        -0.01f,                    // speedX
        -0.005f,                   // speedY
        0.0f,                      // angle
        {0.0f, 1.0f, 0.0f}        // green color
    };

    /* Render loop */
    while (!glfwWindowShouldClose(window)) {
        /* Clear the screen */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Update and draw triangles */
        updateTriangle(tri1);
        updateTriangle(tri2);
        
        drawTriangle(tri1.angle, tri1.x, tri1.y, tri1.color);
        drawTriangle(tri2.angle, tri2.x, tri2.y, tri2.color);

        /* Swap buffers and poll events */
        glfwSwapBuffers(window);
        glfwPollEvents();

        /* Control animation speed */
        glfwWaitEventsTimeout(1.0/60.0);  // Cap at ~60 FPS
    }

    glfwTerminate();
    return 0;
}
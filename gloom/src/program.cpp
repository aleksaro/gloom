// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"


void runProgram(GLFWwindow* mWindow)
{
    // Set GLFW callback mechanism(s)
    glfwSetKeyCallback(mWindow, keyboardCallback);

    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings 
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc)

    // Rendering Loop
    while (!glfwWindowShouldClose(mWindow))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handle other events
        glfwPollEvents();

        // Draw your scene here

        // Flip buffers
        glfwSwapBuffers(mWindow);
    }
}


void keyboardCallback(GLFWwindow* window, int key, int scancode,
                      int action, int mods)
{
    // Use escape key for terminating the GLFW window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

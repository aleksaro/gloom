#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#pragma once

// System headers
#include <GLFW/glfw3.h>


// Main OpenGL program
void runProgram(GLFWwindow* mWindow);

// GLFW callback mechanisms
void keyboardCallback(GLFWwindow* window, int key, int scancode,
                      int action, int mods);

#endif

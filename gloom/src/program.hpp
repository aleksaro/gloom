#ifndef PROGRAM_HPP
#define PROGRAM_HPP
#pragma once


// System headers
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>


inline void printGLError() {
    int errorID = glGetError();

    if(errorID != GL_NO_ERROR) {
        std::string errorString;

        switch(errorID) {
<<<<<<< HEAD
            case GL_INVALID_ENUM:                   errorString = "GL_INVALID_ENUM"; break;
            case GL_INVALID_OPERATION:              errorString = "GL_INVALID_OPERATION"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  errorString = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                  errorString = "GL_OUT_OF_MEMORY"; break;
            case GL_STACK_UNDERFLOW:                errorString = "GL_STACK_UNDERFLOW"; break;
            case GL_STACK_OVERFLOW:                 errorString = "GL_STACK_OVERFLOW"; break;
            default:                                errorString = "[Unknown error ID]"; break;
        }

        fprintf(stderr, "An OpenGL error occurred (%i): %s.\n", errorID, errorString.c_str());
=======
            case GL_INVALID_ENUM:
                errorString = "GL_INVALID_ENUM"; 
                break;
            case GL_INVALID_OPERATION:
                errorString = "GL_INVALID_OPERATION"; 
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorString = "GL_INVALID_FRAMEBUFFER_OPERATION"; 
                break;
            case GL_OUT_OF_MEMORY:
                errorString = "GL_OUT_OF_MEMORY"; 
                break;
            case GL_STACK_UNDERFLOW:
                errorString = "GL_STACK_UNDERFLOW"; 
                break;
            case GL_STACK_OVERFLOW:
                errorString = "GL_STACK_OVERFLOW"; 
                break;
            default:
                errorString = "[Unknown error ID]"; 
                break;
        }

        fprintf(stderr, "An OpenGL error occurred (%i): %s.\n", 
            errorID, errorString.c_str());
>>>>>>> 0d6759b... Various alterations in preparation of Graphics Labs
    }
}


// Main OpenGL program
void runProgram(GLFWwindow* mWindow);


// GLFW callback mechanisms
void keyboardCallback(GLFWwindow* window, int key, int scancode,
                      int action, int mods);

#endif

#ifndef CAMERA_HPP
#define CAMERA_HPP
#pragma once

// System headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>


namespace Gloom
{
    class Camera
    {
    public:
        Camera(glm::vec3 position         = glm::vec3(0.0f, 0.0f, 2.0f),
               GLfloat   movementSpeed    = 5.0f,
               GLfloat   mouseSensitivity = 0.005f)
        {
            cPosition         = position;
            cMovementSpeed    = movementSpeed;
            cMouseSensitivity = mouseSensitivity;

            // Set up the initial view matrix
            updateViewMatrix();
        }

        // Public member functions

        /* Getter for the view matrix */
        glm::mat4 getViewMatrix() { return matView; }


        /* Handle keyboard inputs from a callback mechanism */
        void handleKeyboardInputs(int key, int action)
        {
            // Keep track of pressed/released buttons
            if (key >= 0 && key < 512)
            {
                if (action == GLFW_PRESS)
                {
                    keysInUse[key] = true;
                }
                else if (action == GLFW_RELEASE)
                {
                    keysInUse[key] = false;
                }
            }
        }


        /* Handle mouse button inputs from a callback mechanism */
        void handleMouseButtonInputs(int button, int action)
        {
            // Ensure that the camera only rotates when the left mouse button is
            // pressed
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            {
                isMousePressed = true;
            }
            else
            {
                isMousePressed = false;
                resetMouse = true;
            }
        }


        /* Handle cursor position from a callback mechanism */
        void handleCursorPosInput(double xpos, double ypos)
        {
            // Do nothing if the left mouse button is not pressed
            if (isMousePressed == false)
                return;

            // There should be no movement when the mouse button is released
            if (resetMouse)
            {
                lastXPos = xpos;
                lastYPos = ypos;
                resetMouse = false;
            }

            // Keep track of pitch and yaw for the current frame
            fYaw   = xpos - lastXPos;
            fPitch = ypos - lastYPos;

            // Update last known cursor position
            lastXPos = xpos;
            lastYPos = ypos;
        }


        /* Update the camera position and view matrix
           `deltaTime` is the time between the current and last frame */
        void updateCamera(GLfloat deltaTime)
        {
            // Extract movement information from the view matrix
            glm::vec3 dirX(matView[0][0], matView[1][0], matView[2][0]);
            glm::vec3 dirY(matView[0][1], matView[1][1], matView[2][1]);
            glm::vec3 dirZ(matView[0][2], matView[1][2], matView[2][2]);

            // Alter position in the appropriate direction
            glm::vec3 fMovement(0.0f, 0.0f, 0.0f);

            if (keysInUse[GLFW_KEY_W])  // forward
                fMovement -= dirZ;

            if (keysInUse[GLFW_KEY_S])  // backward
                fMovement += dirZ;

            if (keysInUse[GLFW_KEY_A])  // left
                fMovement -= dirX;

            if (keysInUse[GLFW_KEY_D])  // right
                fMovement += dirX;

            if (keysInUse[GLFW_KEY_E])  // vertical up
                fMovement += dirY;

            if (keysInUse[GLFW_KEY_Q])  // vertical down
                fMovement -= dirY;

            // Trick to balance PC speed with movement
            GLfloat velocity = cMovementSpeed * deltaTime;

            // Update camera position using the appropriate velocity
            cPosition += fMovement * velocity;

            // Update the view matrix based on the new information
            updateViewMatrix();
        }

    private:
        // Disable copying and assignment
        Camera(Camera const &) = delete;
        Camera & operator =(Camera const &) = delete;

        // Private member function

        /* Update the view matrix based on the current information */
        void updateViewMatrix()
        {
            // Adjust cursor movement using the specified sensitivity
            fPitch *= cMouseSensitivity;
            fYaw   *= cMouseSensitivity;

            // Create quaternions given the current pitch and yaw
            glm::quat qPitch = glm::quat(glm::vec3(fPitch, 0.0f, 0.0f));
            glm::quat qYaw   = glm::quat(glm::vec3(0.0f, fYaw, 0.0f));

            // Reset pitch and yaw values for the current rotation
            fPitch = 0.0f;
            fYaw   = 0.0f;

            // Update camera quaternion and normalise
            cQuaternion = qYaw * qPitch * cQuaternion;
            cQuaternion = glm::normalize(cQuaternion);

            // Build rotation matrix using the camera quaternion
            glm::mat4 matRotation = glm::mat4_cast(cQuaternion);

            // Build translation matrix
            glm::mat4 matTranslate = glm::translate(glm::mat4(1.0f), -cPosition);

            // Update view matrix
            matView = matRotation * matTranslate;
        }

        // Private member variables

        // Camera quaternion and frame pitch and yaw
        glm::quat cQuaternion;
        GLfloat fPitch = 0.0f;
        GLfloat fYaw   = 0.0f;

        // Camera position
        glm::vec3 cPosition;

        // Variables used for bookkeeping
        GLboolean resetMouse     = true;
        GLboolean isMousePressed = false;
        GLboolean keysInUse[512];

        // Last cursor position
        GLfloat lastXPos = 0.0f;
        GLfloat lastYPos = 0.0f;

        // Camera settings
        GLfloat cMovementSpeed;
        GLfloat cMouseSensitivity;

        // View matrix
        glm::mat4 matView;
    };
}

#endif

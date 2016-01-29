#ifndef CAMERA_HPP
#define CAMERA_HPP
#pragma once

// System headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace Gloom
{
    enum CameraDirection {
        FORWARD, BACKWARD, LEFT, RIGHT
    };


    class Camera
    {
    public:
        Camera(GLfloat aspect,  // aspect = mWidth / mHeight
               GLfloat fov              = 45.0f,
               GLfloat nearClip         = 0.1f,
               GLfloat farClip          = 1000.0f,
               glm::vec3 position       = glm::vec3(0.0f, 0.0f, 2.0f),
               glm::vec3 up             = glm::vec3(0.0f, 1.0f, 0.0f),
               glm::vec3 front          = glm::vec3(0.0f, 0.0f, -1.0f),
               GLfloat yaw              = -90.0f,
               GLfloat pitch            = 0.0f,
               GLfloat movementSpeed    = 3.0f,
               GLfloat mouseSensitivity = 0.15f)
        {
            cAspect           = aspect;
            cFov              = fov;
            cNearClip         = nearClip;
            cFarClip          = farClip;
            cPosition         = position;
            cWorldUp          = up;
            cFront            = front;
            cYaw              = yaw;
            cPitch            = pitch;
            cMovementSpeed    = movementSpeed;
            cMouseSensitivity = mouseSensitivity;
            update();
        }

        // Public member functions

        /* Getter for the model, view, projection matrices */
        void getMVP(glm::mat4 &proj, glm::mat4 &view, glm::mat4 &model)
        {
            proj  = getProjectionMatrix();
            view  = getViewMatrix();
            model = glm::mat4(1.0f);
        }


        /* Getter for the projection matrix */
        glm::mat4 getProjectionMatrix()
        {
            return glm::perspective(cFov, cAspect, cNearClip, cFarClip);
        }


        /* Getter for the view matrix */
        glm::mat4 getViewMatrix()
        {
            return glm::lookAt(cPosition, cPosition + cFront, cUp);
        }


        /* Process keyboard inputs
           `deltaTime` is the time between the current and last frame */
        void processKeyboard(Gloom::CameraDirection dir,
                             GLfloat deltaTime)
        {
            // Trick to balance PC speed with movement
            GLfloat velocity = cMovementSpeed * deltaTime;

            // Alter position in the appropriate direction
            if (dir == Gloom::FORWARD)
            {
                cPosition += cFront *  velocity;
            }
            if (dir == Gloom::BACKWARD)
            {
                cPosition -= cFront * velocity;
            }
            if (dir == Gloom::LEFT)
            {
                cPosition -= cRight * velocity;
            }
            if (dir == Gloom::RIGHT)
            {
                cPosition += cRight * velocity;
            }
        }


        /* Process mouse movements */
        void processMouse(GLfloat xoffset, GLfloat yoffset)
        {
            // Smoothing
            xoffset *= cMouseSensitivity;
            yoffset *= cMouseSensitivity;

            // Update Euler angles
            cYaw   += xoffset;
            cPitch += yoffset;

            // Constrain pitch so the screen doesn't flip
            if (cPitch > 89.0f)
            {
                cPitch = 89.0f;
            }
            if (cPitch < -89.0f)
            {
                cPitch = -89.0f;
            }

            // Update cFront, cRight, and cUp using the new yaw and pitch
            update();
        }

    private:
        // Disable copying and assignment
        Camera(Camera const &) = delete;
        Camera & operator =(Camera const &) = delete;

        // Private member function

        /* Computes the cFront, cRight, and cUp vector given updated
           Euler angles */
        void update()
        {
            // Calculate cFront
            glm::vec3 front;
            front.x = cos(glm::radians(cYaw)) * cos(glm::radians(cPitch));
            front.y = sin(glm::radians(cPitch));
            front.z = sin(glm::radians(cYaw)) * cos(glm::radians(cPitch));
            cFront = glm::normalize(front);

            // Re-calculate cRight and cUp
            cRight = glm::normalize(glm::cross(cFront, cWorldUp));
            cUp = glm::normalize(glm::cross(cRight, cFront));
        }

        // Private member variables

        // Camera variables
        glm::vec3 cPosition;
        glm::vec3 cFront;
        glm::vec3 cUp;
        glm::vec3 cRight;
        glm::vec3 cWorldUp;

        // Euler angles
        GLfloat cYaw;
        GLfloat cPitch;

        // Camera settings
        GLfloat cMovementSpeed;
        GLfloat cMouseSensitivity;
        GLfloat cFov;
        GLfloat cAspect;
        GLfloat cNearClip;
        GLfloat cFarClip;
    };
}

#endif

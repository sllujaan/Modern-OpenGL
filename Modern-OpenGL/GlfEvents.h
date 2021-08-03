#pragma once
#include"pch.h"
#include"Globals.h"

namespace GLF_EVENTS {
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        const float cameraSpeed = 0.05f; // adjust accordingly
        static int frameCount = 0;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            std::cout << "---------W--" << std::endl;
            cam.cameraPos += cameraSpeed * cam.cameraFront;

        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            std::cout << "---------S--" << std::endl;
            cam.cameraPos -= (cameraSpeed * cam.cameraFront);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            std::cout << "---------A--" << std::endl;
            cam.cameraPos -= glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            std::cout << "---------D--" << std::endl;
            cam.cameraPos += glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
        }


        mvp.view = glm::lookAt(
            cam.cameraPos,
            cam.cameraPos + cam.cameraFront,
            cam.cameraUp
        );

    }
}
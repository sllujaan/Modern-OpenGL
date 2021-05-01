#pragma once

#include"pch.h"

#include"ApplicationGlobals.h"
#include"Util.h"




NAMESPACE_GLFWINDOW

#define GLFW_WINDOW_WIDTH 640
#define GLFW_WINDOW_HEIGHT 480

GLFWwindow* window;


HANDLE_WINDOW

    /* Initialize the library */
    if (!glfwInit())
    return -1;

    glfwWindowHint(GLFW_SAMPLES, 4);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(GLFW_WINDOW_WIDTH, GLFW_WINDOW_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    return 0;

FUN_END     //HANDLE_WINDOW

//HANDLE_GLF_LOOP
HANDLE_GLF_LOOP
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        glEnable(GL_PROGRAM_POINT_SIZE);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glDrawArrays(GL_POINTS, 0, 3);

        /* Poll for and process events */
        glfwPollEvents();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /*slow down the loop*/
        util::handleloopCount(50, false);
    }

FUN_END    //HANDLE_GLF_LOOP





NAMESPACE_END   //FILE_NAMESPACE_BEGIN
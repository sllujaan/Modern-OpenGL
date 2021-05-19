#include "pch.h"
#include "GLFWindow.h"

W::GLF::~GLF()
{
    glfwTerminate();
}

void W::GLF::handleCreateWindow()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* _window = glfwCreateWindow(this->width, this->height, "LearnOpenGL", NULL, NULL);
    if (_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        __debugbreak();
        return;
    }
    glfwMakeContextCurrent(_window);
    this->window = _window;

    if (int err = glewInit() != GLEW_OK) {
        std::cout << glewGetErrorString(err) << std::endl;
        __debugbreak();
        return;
    }

}

GLFWwindow* W::GLF::getWindow()
{
    return this->window;
}

void W::GLF::handleLoop()
{
    while (!glfwWindowShouldClose(this->window))
    {


        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT);



        glDrawArrays(GL_TRIANGLES, 0, 3);	// this call should output an orange triangle

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

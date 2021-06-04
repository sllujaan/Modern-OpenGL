#include "pch.h"
#include "GLFWindow.h"

//#ifdef INDEXED_BUFFER
//#undef INDEXED_BUFFER
//#endif // INDEXED_BUFFER


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
    Color _color;



    while (!glfwWindowShouldClose(this->window))
    {

        
        // render
        // ------
        /*Color c = _color.getRandomColor();
        glClearColor(c.R, c.G, c.B, 1.0f);*/

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


#ifdef INDEXED_BUFFER
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
#else
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
#endif
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(this->window);
        glfwPollEvents();

        util::handleloopCount(5, true);

    }
}

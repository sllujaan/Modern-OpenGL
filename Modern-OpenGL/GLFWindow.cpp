#include "pch.h"
#include "GLFWindow.h"

//#ifdef INDEXED_BUFFER
//#undef INDEXED_BUFFER
//#endif // INDEXED_BUFFER



glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}



W::GLF::~GLF()
{
    glfwTerminate();
}

W::GLF::GLF()
{
    mvp.model = camera(0.5f, glm::vec2(0.0f, 0.0f));
}

void W::GLF::handleCreateWindow()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    

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

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    this->handleInputs();

}

GLFWwindow* W::GLF::getWindow()
{
    return this->window;
}

void W::GLF::handleLoop(size_t _program)
{
    program = _program;
    Color _color;
    Color _color2;
    const float radius = 1.0f;
    float angle = 0.001f;

    int vlModel = glGetUniformLocation(program, "model");
    int vlView = glGetUniformLocation(program, "view");
    int vlProjection = glGetUniformLocation(program, "projection");
    int vertexCoordLocation = glGetUniformLocation(program, "_mat4");
    int vertexColorLocation = glGetUniformLocation(program, "_color");
    //glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(model));

    mvp.view = glm::lookAt(
        cam.cameraPos,
        cam.cameraFront,
        cam.cameraUp
    );

    mvp.model *= mvp.view;

    glUniformMatrix4fv(vertexCoordLocation, 1, GL_FALSE, glm::value_ptr(mvp.model));

    size_t delay = 0;
    Color _c = _color.getRandomColor();

    while (!glfwWindowShouldClose(this->window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //update model view projection
        glUniformMatrix4fv(vlModel, 1, GL_FALSE, glm::value_ptr(mvp.model));
        glUniformMatrix4fv(vlView, 1, GL_FALSE, glm::value_ptr(mvp.view));
        glUniformMatrix4fv(vlProjection, 1, GL_FALSE, glm::value_ptr(mvp.projection));
      



#ifdef INDEXED_BUFFER
        glDrawElements(GL_TRIANGLES, 6 * 6, GL_UNSIGNED_INT, nullptr);
#else
        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);
#endif
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(this->window);
        glfwPollEvents();

        util::handleloopCount(20, true);

    }
}

void W::GLF::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float cameraSpeed = 0.05f; // adjust accordingly


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        std::cout << "---------W" << std::endl;
       cam.cameraPos += cameraSpeed * cam.cameraFront;
       
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        std::cout << "---------S" << std::endl;
        cam.cameraPos -= (cameraSpeed * cam.cameraFront);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "---------A" << std::endl;
        cam.cameraPos -= glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        std::cout << "---------D" << std::endl;
        cam.cameraPos += glm::normalize(glm::cross(cam.cameraFront, cam.cameraUp)) * cameraSpeed;
    }


    mvp.view = glm::lookAt(
        cam.cameraPos,
        cam.cameraPos + cam.cameraFront,
        cam.cameraUp
    );
    
}


void W::GLF::handleInputs()
{
    glfwSetKeyCallback(this->window, key_callback);
}



size_t W::GLF::program;
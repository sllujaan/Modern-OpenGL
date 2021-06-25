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
    this->model = glm::mat4(1.0f);
    this->model = camera(1.0f, glm::vec2(0.0f, 0.0f));
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

    int vertexCoordLocation = glGetUniformLocation(program, "_mat4");
    int vertexColorLocation = glGetUniformLocation(program, "_color");
    //glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(model));
    glm::mat4 view = glm::mat4(1.0f);

    view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    this->model = model * view;

    glUniformMatrix4fv(vertexCoordLocation, 1, GL_FALSE, glm::value_ptr(model));

    size_t delay = 0;
    Color _c = _color.getRandomColor();

    while (!glfwWindowShouldClose(this->window))
    {

        // render
        // ------
        Color c = _color.getRandomColor();
        glClearColor(c.R, c.G, c.B, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        delay++;
        if (delay > 50) {
            Color _c = _color2.getRandomColor();
            glUniform3f(vertexColorLocation, _c.R, _c.G, _c.B);
        }
        

        //transformation--------
        angle += 0.009f;
        //if (angle > 0.70f) angle = 0.60f;
        //std::cout << angle << std::endl;
        //trans = glm::rotate(trans, angle, glm::vec3(0.5f, 1.0f, 0.5f));
        glm::mat4 trans = camera(1.3f, glm::vec2(angle, angle));
        glUniformMatrix4fv(vertexCoordLocation, 1, GL_FALSE, glm::value_ptr(trans));
        //-------------------


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
    std::cout << "key: " << key << std::endl;
    glm::mat4 _model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    _model = camera(1.0f, glm::vec2(0.0f, 0.0f));

    const float radius = 2.0f;
    static float camX = 0.0f;
    static float camZ = 0.0f;
    static float camY = 0.0f;

    if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
        float camX = sin(glfwGetTime()) * glm::radians(radius);
        float camZ = cos(glfwGetTime()) * glm::radians(radius);

        view = glm::lookAt(
            glm::vec3(camX, camY, camZ),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }

    if (key == GLFW_KEY_W && action == GLFW_REPEAT) {
        float camX = sin(glfwGetTime()) * glm::radians(radius);
        float camY = cos(glfwGetTime()) * glm::radians(radius);
        std::cout << "----camY:== " << camY << std::endl;

        view = glm::lookAt(
            glm::vec3(camX, camY, camZ),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
    }

    _model = _model * view;

    int vertexCoordLocation = glGetUniformLocation(program, "_mat4");
    glUniformMatrix4fv(vertexCoordLocation, 1, GL_FALSE, glm::value_ptr(_model));

    
}

void W::GLF::handleInputs()
{
    glfwSetKeyCallback(this->window, key_callback);
}



glm::mat4 W::GLF::model = glm::mat4(1.0f);
size_t W::GLF::program;
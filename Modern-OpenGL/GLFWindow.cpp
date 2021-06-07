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

}

GLFWwindow* W::GLF::getWindow()
{
    return this->window;
}

void W::GLF::handleLoop(size_t program)
{
    Color _color;
    Color _color2;
    glm::mat4 model(1.0f);
    const float radius = 1.0f;

    model = camera(1.0f, glm::vec2(0.0f, 0.0f));

    int vertexCoordLocation = glGetUniformLocation(program, "_mat4");
    int vertexColorLocation = glGetUniformLocation(program, "_color");
    //glUniformMatrix4fv(vertexColorLocation, 1, GL_FALSE, glm::value_ptr(model));
    glm::mat4 view = glm::mat4(1.0f);

    view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    //rotate the view
    view = glm::rotate(view, 45.0f, glm::vec3(1.0f, 1.0f, 0.0f));

    model = model * view;
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
        

        
        /*float camX = sin(1) * glm::radians(radius);
        float camZ = cos(1) * glm::radians(radius);
        view = glm::lookAt(
            glm::vec3(camX, 0.0f, camZ),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );
        model = model * view;
        glUniformMatrix4fv(vertexCoordLocation, 1, GL_FALSE, glm::value_ptr(model));*/


#ifdef INDEXED_BUFFER
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
#else
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
#endif
        
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(this->window);
        glfwPollEvents();

        util::handleloopCount(20, true);

    }
}

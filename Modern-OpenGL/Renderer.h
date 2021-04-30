#pragma once
#include"pch.h"


#define ASSERT(x) if(x) __debugbreak()
#define GlCall(x) GlClearErrors();\
    x;\
    ASSERT(GlLogError(#x, __FILE__, __LINE__));

void GlClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GlLogError(const char* functionName, const char* file, unsigned int line) {
    if (GLenum error = glGetError()) {
        std::cout << "GL_ERROR::" << error << " => " << functionName << " : " << file << " : " << line << std::endl;
        return true;
    }
    return false;
}


#define NAME_TO_STRING(X) #X

int SHADER_GLOBAL = NULL;
int MOUSE_LEFT_REPEAT = 0;
float CURR_TRANSLATE_X = 0.0f;
float CURR_TRANSLATE_Y = 0.0f;
float CURR_TRANSLATE_Z = 0.0f;

glm::mat4 PROJECTION = glm::mat4(0.0f);
glm::mat4 VIEW = glm::mat4(0.0f);
glm::mat4 MODEL = glm::mat4(0.0f);
float FOV = 25.0f;
int ANIMATE_TRASLATE_ONKEY_W_S_A_D = false;

#define GLFW_WINDOW_WIDTH 640
#define GLFW_WINDOW_HEIGHT 480



glm::vec3 CAMERA_POS = glm::vec3(0.0f, 0.0f, -6.0f);
glm::vec3 CAMERA_FRONT = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);


enum Zoom
{
    In,
    Out
};

typedef enum transDirection
{
    left,
    right,
    up,
    down
} rotateDir;


struct APP_THREAD_INFO
{
    int MAIN_THREAD_SOULD_CLOSE = 0;
    int ALL_CHILD_THREADS_SOULD_CLOSE = 0;
};

APP_THREAD_INFO _appThreadInfo;



GLFWwindow* GLF_WINDOW;

void handle_key(GLFWwindow* window, int key, int scancode, int action, int mods);


glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}


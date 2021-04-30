#include"pch.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>



#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include"Util.h"
#include"File/File.h"
#include"Renderer.h"
#include "VertexBuffer.h"




void animateShaderThread() {
    
    while (!_appThreadInfo.ALL_CHILD_THREADS_SOULD_CLOSE)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "animateShaderThread: " << _threadid << std::endl;

        if (ANIMATE_TRASLATE_ONKEY_W_S_A_D) {
            /*for (size_t i = 0; i < 20; i++)
            {*/
                //handle_key(GLF_WINDOW, 0, 0, 0, 0);
                glm::mat4 trans = glm::mat4(1.0f);
                VIEW = glm::lookAt(CAMERA_POS, CAMERA_FRONT, CAMERA_UP);
                trans = PROJECTION * VIEW * MODEL;
                GLint vbLocation = glGetUniformLocation(SHADER_GLOBAL, "trans");
                //glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            //}
            ANIMATE_TRASLATE_ONKEY_W_S_A_D = 0;
        }
        
    }
    return;
}



void translateShader(transDirection dir) {
    float translateX = 0.0f;
    float translateY = 0.0f;

    switch (dir)
    {
    case left:
        translateX -= 0.1f;
        break;
    case right:
        translateX += 0.1f;
        break;
    case up:
        translateY += 0.1f;
        break;
    case down:
        translateY -= 0.1f;
        break;
    default:
        break;
    }

    //pass trans camera to the shader
    GLint vbLocation = glGetUniformLocation(SHADER_GLOBAL, "trans");
    glm::mat4 trans(1.0f);
    glm::mat4 view(1.0f);
    float angle = 0.0f;
    //trans = camera(translate, glm::vec2(angle, angle));
    
    view = glm::translate(VIEW, glm::vec3(-translateX, -translateY, 0.0f));
    VIEW = view;
    trans = PROJECTION * MODEL * VIEW;
    glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));
}


void rotateScene(rotateDir dir) {
    float rotateX = 0.0f;
    float rotateY = 0.0f;

    switch (dir)
    {
    case left:
        rotateX -= 0.1f;
        break;
    case right:
        rotateX += 0.1f;
        break;
    case up:
        rotateY += 0.1f;
        break;
    case down:
        rotateY -= 0.1f;
        break;
    default:
        break;
    }

    //pass trans camera to the shader
    GLint vbLocation = glGetUniformLocation(SHADER_GLOBAL, "trans");
    glm::mat4 View(1.0f);
    float angle = 0.0f;
    //View = camera(1.0f, glm::vec2(rotateX, rotateY));
    //View = glm::rotate(View, rotateX, glm::vec3(0.0f, 0.0f, 0.0f));
    //View = glm::rotate(View, rotateY, glm::vec3(0.0f, 0.0f, 0.0f));
    //View = VIEW * View;
    View = glm::rotate(VIEW, -rotateX, glm::vec3(1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, -rotateY, glm::vec3(0.0f, 1.0f, 0.0f));
    VIEW = View;
    View = PROJECTION * MODEL * VIEW;
    glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(View));
}



void translateShaderCamera() {
    static float rotateX = 0.0f;
    static float rotateY = 0.0f;

    rotateX += 0.1f;
    rotateY += 0.1f;

    //pass view camera to the shader
    GLint vbLocation = glGetUniformLocation(SHADER_GLOBAL, "trans");
    glm::mat4 view(1.0f);
    view = camera(2, glm::vec2(rotateX, rotateY));
    glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(view));
}



void zoomInOutCamera(Zoom zoom) {
    GLint vbLocation = glGetUniformLocation(SHADER_GLOBAL, "trans");
    glm::mat4 trans(1.0f);

    glm::mat4 Projection = glm::perspective(glm::radians(FOV), 800.0f / 600.0f, 0.1f, 100.0f);
    PROJECTION = Projection;
    trans = PROJECTION * MODEL * VIEW; 
    glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));
}


bool firstMouse = true;
float lastX = GLFW_WINDOW_WIDTH, lastY = GLFW_WINDOW_HEIGHT;
float yaw = -90.0f;
float pitch = 45.0f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {


    std::cout << std::this_thread::get_id() << std::endl;

    //std::cout << "mouse_callback" << std::endl;
    GLint vbLocation = glGetUniformLocation(SHADER_GLOBAL, "trans");


    if (MOUSE_LEFT_REPEAT) {
        std::cout << "mouse_callback translate the scene" << std::endl;
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;


        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw));// * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(yaw));
        direction.z = sin(glm::radians(pitch));// *cos(glm::radians(pitch));
        CAMERA_FRONT = glm::normalize(direction);


        VIEW = glm::lookAt(CAMERA_POS, CAMERA_POS + CAMERA_FRONT, CAMERA_UP);
        glm::mat4 trans = PROJECTION * VIEW * MODEL;
        glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //std::cout << _threadid << std::endl;
    float sensitivity = 2.0f;
    FOV -= (float)yoffset * sensitivity;
    if (FOV < 1.0f)
        FOV = 1.0f;
    if (FOV > 100.0f)
        FOV = 100.0f;

    std::cout << xoffset << std::endl;
    
    std::cout << yoffset << std::endl;
    if (yoffset > 0) {
        //mouse scroll up
        zoomInOutCamera(Zoom::In);
    }
    else {
        //mouse scroll up
        zoomInOutCamera(Zoom::Out);
    }

}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "mouse left click" << std::endl;
        MOUSE_LEFT_REPEAT = 1;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        std::cout << "mouse left click release" << std::endl;
        MOUSE_LEFT_REPEAT = 0;
    }

}

void handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float cameraSpeed = 0.05f;
    static size_t countPerKey = 0;


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        CAMERA_POS.y += cameraSpeed;
        CAMERA_FRONT.y += cameraSpeed;
        CAMERA_UP.y += CAMERA_FRONT.y;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        CAMERA_POS.y -= cameraSpeed;
        CAMERA_FRONT.y -= cameraSpeed;
        CAMERA_UP.y -= CAMERA_FRONT.y;

    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        CAMERA_POS.x += cameraSpeed;
        CAMERA_FRONT.x += cameraSpeed;
        //CAMERA_UP.x -= cameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        CAMERA_POS.x -= cameraSpeed;
        CAMERA_FRONT.x -= cameraSpeed;
        //CAMERA_UP.x -= cameraSpeed;
    }


}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    const float cameraSpeed = 0.5f; // adjust accordingly
    if (key == GLFW_KEY_UP) {
        CAMERA_FRONT.y += 0.01f;
        goto KEYS_2;
    }
    if (key == GLFW_KEY_DOWN) {
        CAMERA_FRONT.y -= 0.01f;
        goto KEYS_2;
    }
    if (key == GLFW_KEY_LEFT) {
        CAMERA_FRONT.x -= 0.01f;
        goto KEYS_2;
    }
    if (key == GLFW_KEY_RIGHT) {
        CAMERA_FRONT.x += 0.01f;
        goto KEYS_2;
    }
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        CAMERA_POS += cameraSpeed * CAMERA_UP;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        CAMERA_POS -= cameraSpeed * CAMERA_UP;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm::vec3 abc = glm::normalize(glm::cross(CAMERA_FRONT, CAMERA_UP)) * cameraSpeed;
        CAMERA_POS -= glm::normalize(glm::cross(CAMERA_FRONT, CAMERA_UP)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        CAMERA_POS += glm::normalize(glm::cross(CAMERA_FRONT, CAMERA_UP)) * cameraSpeed;

KEYS_2:



    VIEW = glm::lookAt(CAMERA_POS, CAMERA_POS + CAMERA_FRONT, CAMERA_UP);
KEYS_3:
    glm::mat4 trans = PROJECTION * VIEW * MODEL;
    GLint vbLocation = glGetUniformLocation(SHADER_GLOBAL, "trans");
    glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));

}



errno_t generateCirclePoints(std::vector<glm::vec3>& vbPoints) {
    float angle = 0.0f;
    const float ANGLE_INCREMENT = 90.0f;
    const float RADIUS = 0.5f;
    while (angle <= 360)
    {
        float x = RADIUS * cos(angle);
        float y = RADIUS * sin(angle);
        x;
        y;
        vbPoints.push_back(glm::vec3(x, y, 0));
        angle += ANGLE_INCREMENT;
    }

    return 0;
}



enum _Openmode1 { // constants for file opening options
    _Openmask1 = 0xff
};

static constexpr _Openmode1 in = static_cast<_Openmode1>(0x01);


template<template<class,class> class T>
void fn() {

}

template<class T>
struct Top {

};

template<template<class T> class U, class V = int>
void funBottom() {
    std::cout << "funBottom" << std::endl;
}




template<class T = float>
void fa(int a) {
    std::cout << "fa Top" << std::endl;
}

template<>
void fa<float>(int a) {
    std::cout << "fa float" << std::endl;
}

template<size_t size>
void arr(const float (&a)[size]) {
    std::cout << a[0] << std::endl;
    std::cout << a[1] << std::endl;
    std::cout << a[2] << std::endl;
}

class A {

};

using B = A;


int main(void) {
    
    B b;

    //F::FILE _file;
    ////std::string _data = _file.readFile("C:\\Users\\SALMAN-ALTAF\\Desktop\\final-backuped\\how to.txt");
    //std::string _data = _file.readShaderFile(F::FRAGMENT);
    ///*_data = _file.readShaderFile(F::VERTEX);
    //_data = _file.readShaderFile(F::GEOMETRY);*/
    //std::cout << _data << std::endl;

    fa(10);

    GLFWwindow* window;

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

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    std::cout << "_threadid main: " <<_threadid << std::endl;
    //thread
    //std::thread th1(animateShaderThread);

    std::cout << std::this_thread::get_id() << std::endl;

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW_ERROR" << std::endl;



    float vbo[] = {
        // top-right        // normal
         0.5f,  0.5f,        0.0f,  0.5f,
         0.2f,  0.2f,        0.0f,  0.2f,
         0.4f,  0.4f,        0.0f,  0.4f,
    };

    //arr(vbo);

    /*
      // positions            //color                //normals
        -0.9f, -0.9f,  1.0f,     1.0f, 0.5f, 1.0f,     -0.9f, -0.5f, -1.0f,   //left bottom
        -0.9f,  0.9f,  1.0f,     1.0f, 0.5f, 1.0f,     -0.5f,  0.5f, -1.0f,   //left top
         0.9f,  0.9f,  1.0f,     1.0f, 0.5f, 1.0f,      0.5f,  0.5f, -1.0f,   //right top
         0.9f, -0.9f,  1.0f,     1.0f, 0.5f, 1.0f,      0.5f, -0.5f, -1.0f,   //right bottom

         // positions            //color                //normals
        -0.2f, -0.2f,  0.0f,      1.0f, 1.0f, 0.0f,     -0.5f, -0.5f, -1.0f,   //left bottom
        -0.2f,  0.2f,  0.0f,      1.0f, 1.0f, 0.0f,     -0.5f,  0.5f, -1.0f,   //left top
         0.2f,  0.2f,  0.0f,      1.0f, 1.0f, 0.0f,      0.5f,  0.5f, -1.0f,   //right top
         0.2f, -0.2f,  0.0f,      1.0f, 1.0f, 0.0f,      0.5f, -0.5f, -1.0f,   //right bottom

    */


  

    int bufferSize = (sizeof(vbo) / sizeof(vbo[0])) * sizeof(float);


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);

    /*triangle 1 ----------------*/
    //give buffer data to opengl
    GLuint points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, vbo, GL_STATIC_DRAW);
    
    //points buffer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //points normal vector
    GlCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(2 * sizeof(float))));
    glEnableVertexAttribArray(1);

    //GlLogError();

    ////quad buffer
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);

    ////color buffer
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    ////normals binding.
    //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);




    //---------------------------------------Texture------------------------------------

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // load and generate the texture
    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("C:\\Users\\SALMAN-ALTAF\\Downloads\\container2.png", &width, &height, &nrChannels, 0);

    if (data)
    {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //texture coordinates.
    /*glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);*/

    //---------------------------------------------------------------------------

    //normals binding.
    /*glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);*/

    Shader _shader;
    std::string vertexShader = _shader.readVertextShaderFile();
    std::string geometryShader = _shader.readGeometryShaderFile();
    std::string fragmentShader = _shader.readFragmentShaderFile();
    std::string empty = "";
    unsigned int shader = _shader.createShader(vertexShader, fragmentShader, geometryShader);
    /*F::FILE _file;
    std::string vertexShader = _file.readShaderFile(F::VERTEX);
    std::string geometryShader = _file.readShaderFile(F::GEOMETRY);
    std::string fragmentShader = _file.readShaderFile(F::FRAGMENT);
    std::string empty = "";

    unsigned int shader = createShader(vertexShader, fragmentShader, geometryShader);*/

    glUseProgram(shader);
    SHADER_GLOBAL = shader;

    //pass trans camera to the shader
    GLint vbLocation = glGetUniformLocation(shader, "trans");
    GLint vbOffsets = glGetUniformLocation(shader, "offsets");
    glm::mat4 trans(1.0f);
    float angle = 0.0f;
    //trans = camera(3.0f, glm::vec2(angle, angle));

    //trans = camera(10.0f, glm::vec2(1.0f, 0.0f));
    float const Translate = 10.0f;
    //glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 Projection = glm::perspective(glm::radians(FOV), 800.0f / 600.0f, 0.1f, 100.0f);
    //float near_plane = 1.0f, far_plane = 100.0f;
    //glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    
    
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, glm::pi<float>() * 0.25f, glm::vec3(1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, glm::pi<float>() * 0.25f, glm::vec3(0.0f, 1.0f, 0.0f));
    View = glm::rotate(View, glm::pi<float>() * 0.25f, glm::vec3(0.0f, 0.0f, 1.0f));
    
    //View = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
    //std::cout << glm::to_string(Model) << std::endl;
    View = glm::lookAt(CAMERA_POS, CAMERA_POS + CAMERA_FRONT, CAMERA_UP);
    MODEL = Model;
    VIEW = View;
    PROJECTION = Projection;
    trans = Projection * View * Model;
    glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));
    
    


    /*-----------------------shadow texture-------------------------------*/
    //---------------------------------------------------------------------


    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(0.5f,  0.5f, -1.0f),
        glm::vec3(-0.5f, -0.5f, -1.0f),
        glm::vec3(-0.5f,  0.5f, -1.0f),
        glm::vec3(0.5f, -0.5f, -1.0f),

        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
    };

    glm::vec2 offsets[2] = { glm::vec2(0.5f,  0.5f), glm::vec2(-0.5f,  0.5f) };

    const size_t cubePositionsSize = sizeof(cubePositions) / sizeof(cubePositions[0]);

    //camera view----------------------
    const float radius = 1.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    //glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(view));
    // `T` is not limited by any constraints.
    
    //--------------------------------

    //instancing
    //glUniformMatrix2fv(vbOffsets, 1, GL_FALSE, glm::value_ptr(offsets[0]));


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_LESS);
        glEnable(GL_PROGRAM_POINT_SIZE);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //transformation--------
        //angle += 0.01f;
        ////if (angle > 0.70f) angle = 0.60f;
        //std::cout << angle << std::endl;
        ////trans = glm::rotate(trans, angle, glm::vec3(0.5f, 1.0f, 0.5f));
        //trans = camera(2.0f, glm::vec2(angle, angle));
        //glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));
        //-------------------

        // draw points 0-4 from the currently bound VAO with current in-use shader
        //glDrawArrays(GL_QUADS, 0, 3 * 4);

        //glDrawArraysInstanced(GL_QUADS, 0, 4, 2);
        
        //camera loot at---------------------
        //const float radius = 10.0f;
        //float camX = sin(glfwGetTime()) * radius;
        //float camZ = cos(glfwGetTime()) * radius;
        //glm::mat4 view;
        //View = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        ////View = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        //VIEW = View;
        //trans = PROJECTION * VIEW * MODEL;
        //glUniformMatrix4fv(vbLocation, 1, GL_FALSE, glm::value_ptr(trans));
        //-------------------------------

        glDrawArrays(GL_POINTS, 0, 3);

        /* Poll for and process events */
        glfwPollEvents();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /*slow down the loop*/
        util::handleloopCount(50, false);

    }


    //close all child thread
    _appThreadInfo.ALL_CHILD_THREADS_SOULD_CLOSE = 1;
    //th1.join();
    glfwTerminate();
    return 0;

}
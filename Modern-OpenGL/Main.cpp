#include"pch.h"

#include"GLFWindow.h"
#include"VertexBuffer.h"
#include"Shader.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int main()
{
    W::GLF _glf;
    _glf.handleCreateWindow();
    GLFWwindow* window = _glf.getWindow();


    /*VertexBuffer _vertextBuffer;
    _vertextBuffer.bind();
    size_t* VBOs = _vertextBuffer.getVBOs();
    size_t* VAOs = _vertextBuffer.getVAOs();*/


    float firstTriangle[] = {
        //front rect            //texture
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,       // left bottom 0
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,       // left top 1
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,       // right top 2

         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,       // left bottom 0
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,         // right bottom 3
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,       // right top 2

        // //back rect            //texture
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,         // left bottom 4
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,         // left top 5
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,         // right top 6

        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,       // left bottom 0
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f,         // right bottom 3
         0.5f,  0.5f, 0.5f,   1.0f, 1.0f,       // right top 2

         //left rect
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,     // left bottom 0
        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f,    // left top 1
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f,     // left bottom 4

        -0.5f,  0.5f, -0.5f,    0.0f, 0.0f,     // left top 1
        -0.5f, -0.5f,  0.5f,    1.0f, 1.0f,     // left bottom 4
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     // left top 5


        //  right rect
        0.5f,  0.5f, -0.5f,   0.0f, 0.0f,       // right top 2
        0.5f, -0.5f, -0.5f,   0.0f, 1.0f,       // right bottom 3
        0.5f, -0.5f,  0.5f,   1.0f, 1.0f,       // right bottom top 7

        0.5f, -0.5f,  0.5f,   1.0f, 1.0f,       // right bottom top 7
        0.5f,  0.5f,  0.5f,   0.0f, 1.0f,       // right top 6
        0.5f,  0.5f, -0.5f,   0.0f, 0.0f,       // right top 2


        // top rect
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f,     // left top 1
         0.5f,  0.5f, -0.5f,    0.0f, 0.0f,     // right top 2
         0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     // right top 6

         0.5f,  0.5f,  0.5f,    0.0f, 1.0f,     // right top 6
        -0.5f,  0.5f,  0.5f,    1.0f, 1.0f,     // left top 5
        -0.5f,  0.5f, -0.5f,    1.0f, 0.0f,     // left top 1


        // bottom rect
        -0.5f,  -0.5f, -0.5f,    1.0f, 0.0f,     // left top 1
         0.5f,  -0.5f, -0.5f,    0.0f, 0.0f,     // right top 2
         0.5f,  -0.5f,  0.5f,    0.0f, 1.0f,     // right top 6

         0.5f,  -0.5f,  0.5f,    0.0f, 1.0f,     // right top 6
        -0.5f,  -0.5f,  0.5f,    1.0f, 1.0f,     // left top 5
        -0.5f,  -0.5f, -0.5f,    1.0f, 0.0f,     // left top 1


         //left rect
        //-0.5f, -0.5f, -0.5f,  // left bottom 0
        //-0.5f,  0.5f, -0.5f,  // left top 1
        //-0.5f, -0.5f,  0.5f,  // left bottom 4

        //-0.5f,  0.5f, -0.5f,  // left top 1
        //-0.5f, -0.5f,  0.5f,  // left bottom 4
        //-0.5f,  0.5f,  0.5f,  // left top 5


        //  right rect
        //0.5f,  0.5f, -0.5f,  // right top 2
        //0.5f, -0.5f, -0.5f,  // right bottom 3
        //0.5f, -0.5f,  0.5f,  // right bottom top 7

        //0.5f, -0.5f,  0.5f,  // right bottom top 7
        //0.5f,  0.5f,  0.5f,  // right top 6
        //0.5f,  0.5f, -0.5f,  // right top 2


        // top rect
         -0.5f,  0.5f, -0.5f,  // left top 1
         0.5f,  0.5f, -0.5f,  // right top 2
         0.5f,  0.5f,  0.5f,  // right top 6

         0.5f,  0.5f,  0.5f,  // right top 6
         -0.5f,  0.5f,  0.5f,  // left top 5
         -0.5f,  0.5f, -0.5f,  // left top 1

         // bottom rect
         -0.5f,  0.5f, -0.5f,  // left top 1
         0.5f,  0.5f, -0.5f,  // right top 2
         0.5f,  0.5f,  0.5f,  // right top 6

         0.5f,  0.5f,  0.5f,  // right top 6
         -0.5f,  0.5f,  0.5f,  // left top 5
         -0.5f,  0.5f, -0.5f,  // left top 1

    };


    size_t VAOs[2] = { 0 };
    size_t VBOs[2] = { 0 };
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle) * 40, firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);

    //texture coordinates--------------------------
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (5 * sizeof(float)), (void*)(3 * sizeof(float)));	// Vertex attributes stay the same
    glEnableVertexAttribArray(1);
    //-------------------------------------


    //setup texture----------------------------------------------
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
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("C:\\Users\\SALMAN-ALTAF\\Desktop\\wall.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //----------------------------------------------------


    /*const size_t indices[30] = { 
        0, 1, 2, 0, 3, 2,
        4, 5, 6, 4, 7, 6,
        0, 1, 4, 1, 4, 5,
        2, 3, 7, 7, 6, 2,
        1, 2, 6, 6, 5, 1,
    };
    size_t ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 30 * sizeof(size_t), indices, GL_STATIC_DRAW);*/

    Shader _shader;
    _shader.attach(VAOs[0]);
    size_t program = _shader.getProgram();
    

    // render loop
    _glf.handleLoop(program);

    return 0;
}

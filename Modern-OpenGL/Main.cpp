#include"pch.h"

#include"GLFWindow.h"
#include"VertexBuffer.h"
#include"Shader.h"



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
        //front rect
        -0.5f, -0.5f, -0.5f,  // left bottom 0
        -0.5f,  0.5f, -0.5f,  // left top 1
         0.5f,  0.5f, -0.5f,  // right top 2

         //-0.5f, -0.5f, -0.5f,  // left bottom 0
         0.5f, -0.5f, -0.5f,  // left top 3
         //0.5f,  0.5f, -0.5f,  // right top 2

         //back rect
        -0.5f, -0.5f,  0.5f,  // left bottom 4
        -0.5f,  0.5f,  0.5f,  // left top 5
         0.5f,  0.5f,  0.5f,  // right top 6

         //-0.5f, -0.5f, -0.5f,  // left bottom 4
         0.5f, -0.5f,  0.5f,  // left top 7
         //0.5f,  0.5f, -0.5f,  // right top 6
    };


    size_t VAOs[2] = { 0 };
    size_t VBOs[2] = { 0 };
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle) * 30, firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);


    const size_t indices[12] = { 
        0, 1, 2, 0, 3, 2,
        4, 5, 6, 4, 7, 6,
    };
    size_t ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(size_t), indices, GL_STATIC_DRAW);

    Shader _shader;
    _shader.attach(ibo);
    size_t program = _shader.getProgram();
    

    // render loop
    _glf.handleLoop(program);

    return 0;
}

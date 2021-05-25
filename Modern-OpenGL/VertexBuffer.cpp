#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
}

errno_t VertexBuffer::bind()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //float firstTriangle[] = {
    //    -0.9f, -0.5f, 0.0f,  // left 
    //    -0.0f, -0.5f, 0.0f,  // right
    //    -0.45f, 0.5f, 0.0f,  // top 
    //};

    float* _triangle = this->_triangle.vbo;
    size_t _triangleSize = this->_triangle.size;
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

    //GlCall();

    GlCall(glGenVertexArrays(2, VAOs)); // we can also generate multiple VAOs or buffers at the same time
    GlCall(glGenBuffers(2, VBOs));
    // first triangle setup
    // --------------------
    GlCall(glBindVertexArray(VAOs[0]));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]));
    GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(_triangle) * _triangleSize, _triangle, GL_STATIC_DRAW));
    GlCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));	// Vertex attributes stay the same
    GlCall(glEnableVertexAttribArray(0));
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // not really necessary as well, but beware of calls that could affect VAOs while this one is bound (like binding element buffer objects, or enabling/disabling vertex attributes)



    return TASK_SUCCESS;
}

size_t* VertexBuffer::getVBOs()
{
    return this->VBOs;
}

size_t* VertexBuffer::getVAOs()
{
    return this->VAOs;
}

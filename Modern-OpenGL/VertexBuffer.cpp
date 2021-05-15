#include "pch.h"
#include "VertexBuffer.h"

errno_t VertexBuffer::bind()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    
    int bufferSize = this->getBufferSize();
    
    glGenBuffers(1, &this->points_vbo);
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, this->points_vbo));
    GlCall(glBufferData(GL_ARRAY_BUFFER, bufferSize, this->vbo, GL_STATIC_DRAW));
    
    //points buffer
    GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    GlCall(glEnableVertexAttribArray(0));
    
    //points normal vector
    GlCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(2 * sizeof(float))));
    
    return TASK_SUCCESS;
}

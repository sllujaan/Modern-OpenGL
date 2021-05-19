#include"pch.h"
#include"GLFWindow.h"
#include"VertexBuffer.h"
#include"Shader.h"

int main()
{
    W::GLF _glf;
    _glf.handleCreateWindow();
    GLFWwindow* window = _glf.getWindow();


    VertexBuffer _vertextBuffer;
    _vertextBuffer.bind();
    size_t* VBOs = _vertextBuffer.getVBOs();
    size_t* VAOs = _vertextBuffer.getVAOs();

    Shader _shader;
    _shader.attach(VAOs[0]);

    // render loop
    _glf.handleLoop();

    return 0;
}

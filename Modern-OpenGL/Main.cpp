#include"pch.h"
#include"GLFWindow.h"
#include"VertexBuffer.h"
#include"Shader.h"

int main() {

    GLF_WINDOW::HandleWindow();

    VertexBuffer vb;
    vb.bind();

    Shader _shader;
    _shader.attach();

    GLF_WINDOW::HandleLoop();

	return 0;
}

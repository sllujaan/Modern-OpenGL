#include"pch.h"
#include"GLFWindow.h"
#include"VertexBuffer.h"

int main() {

    GLF_WINDOW::HandleWindow();

    /*VertexBuffer vb;
    vb.bind();*/

    GLF_WINDOW::HandleLoop();

	return 0;
}

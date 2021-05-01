#include"pch.h"

#include"GLFWindow.h"
#include"VertexBuffer.h"




int main() {

	GLF_WINDOW::HandleWindow();

	VertexBuffer::HandleBufferData();

	GLF_WINDOW::HandleLoop();

	return 0;
}

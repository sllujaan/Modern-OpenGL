#pragma once

#include"pch.h"

#include"ApplicationGlobals.h"
#include"VertexBuffer.h"


namespace W {

	struct Screen
	{
		size_t width = 800;
		size_t height = 600;
	};

	class GLF : Screen {
	private:
		GLFWwindow* window;
	public:
		void handleCreateWindow();
		GLFWwindow* getWindow();
	};
}

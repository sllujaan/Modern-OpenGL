#pragma once

#include"pch.h"

#include"ApplicationGlobals.h"
#include"VertexBuffer.h"
#include"Util.h"

#define INDEXED_BUFFER 1




namespace W {

	struct Screen
	{
		size_t width = 800;
		size_t height = 600;
	};
	struct Color
	{
		float R = 0.0f;
		float G = 0.0f;
		float B = 0.0f;
		bool shouldIncR = true;
		bool shouldIncG = true;
		bool shouldIncB = true;

		Color getRandomColor() {
			
			if (this->R > 1.0f) this->shouldIncR = false;
			if (this->R < 0.01f) this->shouldIncR = true;

			if (this->G > 1.0f) this->shouldIncG = false;
			if (this->G < 0.001f) this->shouldIncG = true;

			if (this->B > 1.0f) this->shouldIncB = false;
			if (this->B < 0.0001f) this->shouldIncB = true;
			
			if (this->shouldIncR) { this->R += 0.01f; }
			else { this->R -= 0.01f; }

			if (this->shouldIncG) { this->G += 0.01f; }
			else { this->G -= 0.001f; }

			if (this->shouldIncB) { this->B += 0.0001f; }
			else { this->B -= 0.0001f; }

			return *(this);
		}
	};

	class GLF : Screen, Color {
	private:
		GLFWwindow* window;
	public:
		~GLF();
		void handleCreateWindow();
		GLFWwindow* getWindow();
		void handleLoop(size_t program);
		
	};
}

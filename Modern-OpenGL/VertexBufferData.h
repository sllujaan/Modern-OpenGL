#pragma once

#include"pch.h"

namespace MODEL {
	struct cube
	{
		static const size_t size = 13;
		float vbo[size] = {
			-0.5f, -0.5f, -0.5f,  // left bottom
			-0.5f,  0.5f, -0.5f,  // left top
			 0.5f,  0.5f, -0.5f,  // right top
			 0.5f, -0.5f, -0.5f,  // right bottom
		};
	};

	struct triangle
	{
		static const size_t size = 18;
		float vbo[size] = {
			-0.5f, -0.5f, -0.5f,  // left bottom 0
			-0.5f,  0.5f, -0.5f,  // left top 1
			 0.5f,  0.5f, -0.5f,  // right top 2

			//-0.5f, -0.5f, -0.5f,  // left bottom 0
			 0.5f, -0.5f, -0.5f,  // left top 3
			 //0.5f,  0.5f, -0.5f,  // right top 2

		};

		const size_t indices[6] = {0, 1, 2, 0, 3, 2};
		
		
	};
}


class VertexBufferData {
private:
    static const size_t size = 15;
public:
    float vbo[size] = {
		-0.5f,  0.5f, // top-left
		 0.5f,  0.5f, // top-right
		 0.5f, -0.5f, // bottom-right
		-0.5f, -0.5f  // bottom-left
	};

    const size_t getBufferSize();
	const size_t getLength();

public:
	MODEL::cube _cube;
	MODEL::triangle _triangle;
};


#pragma once
#include"pch.h"


class VertexBuffer {
private:
	float vertexBuffer[];
public:
	VertexBuffer() : vertexBuffer{ 1, 2, 3, 4 } { }
	template<size_t size>
	void vertexData(float* vb) {
		std::cout << vb[0] << std::endl;
		std::cout << vb[1] << std::endl;
		std::cout << vb[2] << std::endl;
		std::cout << vb[3] << std::endl;
	}
	void setBufferLayout();
	void bind();
};

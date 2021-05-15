#pragma once


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
};
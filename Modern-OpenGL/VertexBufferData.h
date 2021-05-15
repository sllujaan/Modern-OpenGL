#pragma once


class VertexBufferData {
private:
    static const size_t size = 15;
public:
    float vbo[size] = {
        // top-right        // normal
         0.5f,  0.5f,        0.0f,  0.5f,
         0.2f,  0.2f,        0.0f,  0.2f,
         0.4f,  0.4f,        0.0f,  0.4f,
    };

    const size_t getBufferSize();
};
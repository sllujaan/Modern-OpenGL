#include "pch.h"
#include "VertexBufferData.h"

const size_t VertexBufferData::getBufferSize()
{
    const size_t bufferSize = ((sizeof(vbo) / sizeof(vbo[0])) * sizeof(float));
    return bufferSize;
}

const size_t VertexBufferData::getLength()
{
    return this->size;
}

#pragma once

#include"pch.h"

#include"ApplicationGlobals.h"
#include"Renderer.h"
#include"VertexBufferData.h"



class VertexBuffer : VertexBufferData {
private:
    GLuint points_vbo;
public:
    errno_t bind();
};
#pragma once

#include"pch.h"

#include"ApplicationGlobals.h"
#include"Renderer.h"
#include"VertexBufferData.h"



class VertexBuffer : VertexBufferData {
private:
    size_t VBOs[3], VAOs[3];
public:
    ~VertexBuffer();
    errno_t bind();
    size_t* getVBOs();
    size_t* getVAOs();
};
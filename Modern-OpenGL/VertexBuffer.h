#pragma once

#include"pch.h"

#include"ApplicationGlobals.h"
#include"Renderer.h"
#include"VertexBufferData.h"



class VertexBuffer : VertexBufferData {
private:
    size_t VBOs[2], VAOs[2];
public:
    errno_t bind();
    size_t* getVBOs();
    size_t* getVAOs();
};
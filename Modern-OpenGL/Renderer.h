#pragma once
#include"pch.h"


#define ASSERT(x) if(x) __debugbreak()
#define GlCall(x) GlClearErrors();\
    x;\
    ASSERT(GlLogError(#x, __FILE__, __LINE__));

static void GlClearErrors() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GlLogError(const char* functionName, const char* file, unsigned int line) {
    if (GLenum error = glGetError()) {
        std::cout << "GL_ERROR::" << error << " => " << functionName << " : " << file << " : " << line << std::endl;
        return true;
    }
    return false;
}
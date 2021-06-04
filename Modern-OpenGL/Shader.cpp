#include "pch.h"
#include "Shader.h"

Shader::~Shader()
{
    /*glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);*/
}

errno_t Shader::attach(size_t bufferID)
{
    std::string vShaderStr = this->readShaderFile(F::VERTEX);
    std::string fShaderStr = this->readShaderFile(F::FRAGMENT);
    std::string gShaderStr = "";
    this->program = this->createShader(vShaderStr, fShaderStr, gShaderStr );

    // now when we draw the triangle we first use the vertex and orange fragment shader from the first program
    glUseProgram(this->program);
    // draw the first triangle using the data from our first VAO
    glBindVertexArray(bufferID);

    return TASK_SUCCESS;
}

errno_t Shader::compileShader(unsigned int type, std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char) * length);
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "geometry")) << " shader" <<
            std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        __debugbreak();
        return 0;
    }

    return id;
}

size_t Shader::createShader(std::string& vertexShader, std::string& fragmentShader, std::string& geometryShader)
{
    const bool isGeometryShader = (geometryShader != "");

    unsigned int program = glCreateProgram();
    unsigned int vs = this->compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = this->compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    unsigned int gs = NULL;
    if (isGeometryShader) gs = this->compileShader(GL_GEOMETRY_SHADER, geometryShader);

    glAttachShader(program, vs);
    if (isGeometryShader) glAttachShader(program, gs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDetachShader(program, vs);
    if (isGeometryShader) glDetachShader(program, gs);
    glDetachShader(program, fs);

    return program;
}

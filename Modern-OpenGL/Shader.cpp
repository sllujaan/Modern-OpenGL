#include "pch.h"
#include "Shader.h"

errno_t Shader::attach()
{
    // build and compile our shader program
    // ------------------------------------
    // we skipped compile log checks this time for readability (if you do encounter issues, add the compile-checks! see previous code samples)
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // the second fragment shader that outputs the color yellow
    unsigned int shaderProgramOrange = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram(); // the second shader program
    glShaderSource(vertexShader, 1, (const char* const*)this->readShaderFile(F::VERTEX).c_str(), NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShaderOrange, 1, (const char* const*)this->readShaderFile(F::FRAGMENT).c_str(), NULL);
    glCompileShader(fragmentShaderOrange);
    glShaderSource(fragmentShaderYellow, 1, (const char* const*)this->readShaderFile(F::FRAGMENT).c_str(), NULL);
    glCompileShader(fragmentShaderYellow);
    // link the first program object
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    // then link the second program object using a different fragment shader (but same vertex shader)
    // this is perfectly allowed since the inputs and outputs of both the vertex and fragment shaders are equally matched.
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);
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

errno_t Shader::createShader(std::string vertexShader, std::string fragmentShader, std::string geometryShader)
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

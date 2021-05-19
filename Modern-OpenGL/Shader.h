#pragma once

#include"pch.h"
#include"File/File.h"
#include"ApplicationGlobals.h"

static const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
static const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
static const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


class Shader : public F::FILE {
private:
	F::FILE _file;

public:
	Shader() { }
	~Shader();
    errno_t attach(size_t bufferID);

	std::string readVertextShaderFile() {
		return this->_file.readShaderFile(F::VERTEX);
	}
	std::string readGeometryShaderFile() {
		return this->_file.readShaderFile(F::GEOMETRY);
	}
	std::string readFragmentShaderFile() {
		return this->_file.readShaderFile(F::FRAGMENT);
	}

    errno_t compileShader(unsigned int type, std::string& source);

	size_t createShader(std::string& vertexShader, std::string& fragmentShader, std::string& geometryShader);
};

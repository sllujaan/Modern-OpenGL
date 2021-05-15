#pragma once

#include"pch.h"
#include"File/File.h"
#include"ApplicationGlobals.h"

class Shader : public F::FILE {
private:
	F::FILE _file;

public:
	Shader() { }
    errno_t attach();

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

	errno_t createShader(std::string vertexShader, std::string fragmentShader, std::string geometryShader);
};

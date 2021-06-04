#pragma once

#include"pch.h"
#include"File/File.h"
#include"ApplicationGlobals.h"



class Shader : public F::FILE {
private:
	F::FILE _file;
	size_t program;

public:
	Shader() { }
	~Shader();
    errno_t attach(size_t bufferID);
	
	
	size_t getProgram() {
		return this->program;
	}
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

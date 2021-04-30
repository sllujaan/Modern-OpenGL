#pragma once
#include <string>
#include<fstream>
#include <iostream>

#define FILE_NAMESPACE_BEGIN namespace F {
#define FILE_NAMESPACE_END }


FILE_NAMESPACE_BEGIN


enum SHADER_FILE_TYPE {
	VERTEX,
	FRAGMENT,
	GEOMETRY
};


class FILE {
private:
	std::fstream _fstream;
	std::string data;

public:
	FILE() { }
	std::string& readFile(const std::string& filePath) {
		this->_fstream.open(filePath, std::ios::in);
		//this->_fstream >> this->data;
		//reset the data
		this->data = "";
		std::string line;
		while (std::getline(this->_fstream, line))
		{
			this->data += line;
			if (!this->_fstream.eof()) this->data += "\r\n";
		}
		this->_fstream.close();
		return this->data;
	}

	std::string readShaderFile(SHADER_FILE_TYPE _shaderType) {
		std::string filePath = "";
		switch (_shaderType)
		{
		case F::VERTEX:
			filePath = "Shaders/vertexShader.vert";
			break;
		case F::FRAGMENT:
			filePath = "Shaders/fragmentShader.frag";
			break;
		case F::GEOMETRY:
			filePath = "Shaders/geometryShader.geom";
			break;
		default:
			filePath = "";
			break;
		}

		return this->readFile(filePath);
	}


};


FILE_NAMESPACE_END
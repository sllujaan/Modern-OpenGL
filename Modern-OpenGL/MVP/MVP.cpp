#include "pch.h"
#include "MVP.h"



void MVP::setModel(glm::mat4 _model)
{
	this->model = _model;
}

void MVP::setView(glm::mat4 _view)
{
	this->view = _view;
}

void MVP::setProjection(glm::mat4 _projection)
{
	this->projection = _projection;
}

glm::mat4 MVP::getModel()
{
	return this->model;
}

glm::mat4 MVP::getView()
{
	return this->view;
}

glm::mat4 MVP::getProjection()
{
	return this->projection;
}

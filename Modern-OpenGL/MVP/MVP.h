#pragma once

#include"../pch.h"

struct Mvp {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
};

class MVP {

public:
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

public:
	void setModel(glm::mat4 model);
	void setView(glm::mat4 view);
	void setProjection(glm::mat4 projection);
	glm::mat4 getModel();
	glm::mat4 getView();
	glm::mat4 getProjection();

};
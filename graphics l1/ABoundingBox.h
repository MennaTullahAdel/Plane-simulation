#pragma once
#include "../middleware/includes/gl/glew.h"
#include "../middleware/includes/gl/glfw3.h"
#include"../middleware/includes/glm/glm.hpp"
#include"../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

class ABoundingBox
{
	glm::vec3 Center;
	glm::vec3 Size;
	glm::vec3 halfSize;

public:
	ABoundingBox(glm::vec3 center, glm::vec3 size);
	ABoundingBox(void);
	~ABoundingBox(void);

	void SetCenter(glm::vec3 center);
	void SetSize(glm::vec3 size);

	inline glm::vec3 GetCenter() { return Center; }
	inline glm::vec3 GetSize() { return Size; }
	inline glm::vec3 GetHalfSize() { return halfSize; }
	
	bool isIntersecting(ABoundingBox obj);

	void Translate(glm::vec3 transVec);
	void Translate(float transX, float transY, float transZ);
	void Scale(glm::vec3 scaleVec);
	void Scale(float scaleX, float scaleY, float scaleZ);
	
};


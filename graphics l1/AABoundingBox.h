#ifndef AABoundingBox_h__
#define AABoundingBox_h__

#pragma once
#include "../middleware/includes/glm/glm.hpp"
#include "../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

class AABoundingBox
{
	glm::vec3 Center;
	glm::vec3 Size;
	glm::vec3 halfSize;
public:
	AABoundingBox();
	AABoundingBox(glm::vec3 center, glm::vec3 size);
	~AABoundingBox();

	void SetCenter(glm::vec3 center);
	void SetSize(glm::vec3 size);

	inline glm::vec3 GetCenter() { return Center; }
	inline glm::vec3 GetSize() { return Size; }
	inline glm::vec3 GetHalfSize() { return halfSize; }
	
	bool isIntersecting(AABoundingBox obj);

	void Translate(glm::vec3 transVec);
	void Translate(float transX, float transY, float transZ);
	void Scale(glm::vec3 scaleVec);
	void Scale(float scaleX, float scaleY, float scaleZ);
	/*void Rotate(glm::mat4 rotationMat);
	void Rotate(float Angle, float rotateX, float rotateY, float rotateZ);*/
};

#endif // !AABoundingBox_h__
#include "ABoundingBox.h"


ABoundingBox::ABoundingBox(void)
{
	Size = glm::vec3(0);
	Center = glm::vec3(0);
}


ABoundingBox::~ABoundingBox(void)
{
}


ABoundingBox::ABoundingBox(glm::vec3 center, glm::vec3 size)
{
	SetCenter(center);
	SetSize(size);
}

void ABoundingBox::SetCenter(glm::vec3 center)
{
	Center = center;
}

void ABoundingBox::SetSize(glm::vec3 size)
{
	Size = size;
	halfSize = size / 2.0f;
}

void ABoundingBox::Translate(float transX, float transY, float transZ)
{
	glm::vec3 translation = glm::vec3(transX, transY, transZ);
	Translate(translation);
}

void ABoundingBox::Translate(glm::vec3 transVec)
{
	glm::vec3 newCenter = this->Center + transVec;
	SetCenter(newCenter);
}

void ABoundingBox::Scale(float scaleX, float scaleY, float scaleZ)
{
	glm::vec3 scaleVec = glm::vec3(scaleX, scaleY, scaleZ);
	Scale(scaleVec);
}

void ABoundingBox::Scale(glm::vec3 scaleVec)
{
	glm::vec3 newSize = this->Size * scaleVec;
	glm::vec3 newCenter = this->Center * scaleVec;
	SetSize(newSize);
	SetCenter(newCenter);
}

bool ABoundingBox::isIntersecting(ABoundingBox obj)
{
	glm::vec3 distance = glm::abs(this->Center - obj.GetCenter());
	glm::vec3 totalDistance = this->halfSize + obj.GetHalfSize();

	if ((distance.x <= totalDistance.x)
		&& (distance.y <= totalDistance.y)
		&& (distance.z <= totalDistance.z)
		)
	{
		return true;
	}
	return false;
}

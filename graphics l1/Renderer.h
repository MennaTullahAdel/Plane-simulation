#ifndef Renderer_h__
#define Renderer_h__

#include "../middleware/includes/gl/glew.h"
#include "../middleware/includes/gl/glfw3.h"

#include "Shaders/shader.hpp"
#include "Model.h"
#include <memory>
#include "FirstPersonCamera.h"
#include "ShaderProgram.h"
#include "Model3D.h"
#include <string>
#include <string.h>
#include <iostream>

using namespace std ;
using namespace glm ;

class Renderer
{
	GLuint programID;
	GLuint VPID;
	GLuint ModelMatrixID;

	std::unique_ptr<Model> mySquare;
	std::unique_ptr<FirstPersonCamera> myCamera;
	Model3D * my_plane;
	Model3D * controlTower[2];
	Model3D * skybox;
	Model3D * rings[5] ;
	Model3D * radar[4];
	Model3D * radiostation[3];
	Model3D * planes[6];
	Model3D * hanger [6];
	Model3D * bus [2];
	
	Texture * Ground ;
	Texture *airstrip ;
	ShaderProgram shader ;
	glm::mat4 VP;
	float movementSpeed;
	float rotationAngle;
	float speedValue;
	float rotationValue;
	float redundancy;
	bool FPC_check;
	bool automatic;
	bool outOfBoundry;
	glm::mat4 floorM;
	glm::vec3 tpcPos;
	glm::vec3 fpcPos;
	glm::vec3 camPos;
	GLuint  LightPositionID  ,AmbientLightID ,EyePositionID;
	vec3 lightPosition ,ambientLight ;

	void objectCollider();

public:
	Renderer();
	~Renderer();

	void Initialize();
	void Draw();
	void HandleKeyboardInput(int key, int action);
	void HandleMouse(double deltaX, double deltaY);
	void Update(double deltaTime);
	void Cleanup();
	void initPointLight() ;
	Model3D *load_object(string path,Model3D *my_model);
	void draw_object(Model3D  *my_model);
};

#endif 

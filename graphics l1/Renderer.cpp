#include"../middleware/includes/glm/glm.hpp"
#include"../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Application Manager\ApplicationManager.h"



Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::Initialize()
{
	//since the triangle is not connected to anything else, so the normal is constant on all the vertices.
	//drawing a square.
#pragma region Make_square
	mySquare = std::unique_ptr<Model>(new Model());
	mySquare->VertexData.push_back(glm::vec3(-1.0f, -1.0f, +0.0f));
	mySquare->VertexData.push_back(glm::vec3(+1.0f, -1.0f, +0.0f));
	mySquare->VertexData.push_back(glm::vec3(+1.0f, +1.0f, +0.0f));
	mySquare->VertexData.push_back(glm::vec3(-1.0f, +1.0f, +0.0f));
	mySquare->UVData.push_back(vec2(0,1));
	mySquare->UVData.push_back(vec2(1,0));
	mySquare->UVData.push_back(vec2(0,0));
	mySquare->UVData.push_back(vec2(1,1));
	//first triangle.
	mySquare->IndicesData.push_back(0);
	mySquare->IndicesData.push_back(1);
	mySquare->IndicesData.push_back(3);
	//second triangle.
	mySquare->IndicesData.push_back(1);
	mySquare->IndicesData.push_back(2);
	mySquare->IndicesData.push_back(3);
	glm::vec3 squareNormal = glm::vec3(0.0, 0.0, 1.0);
	mySquare->NormalsData.push_back(squareNormal);
	mySquare->NormalsData.push_back(squareNormal);
	mySquare->NormalsData.push_back(squareNormal);
	mySquare->NormalsData.push_back(squareNormal);
	mySquare->Initialize();
#pragma endregion Make_square


#pragma  region  loading_models

	my_plane = load_object("data/models/Lancaster/Airplane LancasterMkII N010312.3ds",my_plane);
	///
	skybox = load_object("data/models/skybox/skybox.obj",skybox);
	skybox->ModelMatrix=scale(vec3(100.0f,100.0f,100.0f));
	//
	for(int i=0 ; i< 2 ; i++)
	{
		controlTower[i]=load_object("data/models/Airbase Control Tower/tower.obj",controlTower[i]);
		bus[i]=load_object("data/models/ElBuss340/Elbuss340.obj" , bus[i]) ;
	}
	controlTower[0]->ModelMatrix = translate (vec3(126,-480,377)) ;
	controlTower[1]->ModelMatrix = translate(vec3(53 , -480 ,-44));
	bus[0]->ModelMatrix =translate(vec3(-32 , -480 , 263));
	bus[1]->ModelMatrix =translate(vec3(-21 , -480 , 274)) ;
	///
	
	for (int i = 0; i < 4; i++)
	{
		radar[i] = load_object("data/models/Radar/Radar.obj",radar[i]) ;
	}
	radar[0]->ModelMatrix= translate (vec3(53 , -480 , -173));
	radar[1]->ModelMatrix=translate(vec3(124 , -480 , -173)) ;
	radar[2]->ModelMatrix=translate(vec3(-27 , -480 , -173)) ;
	radar[3]->ModelMatrix=translate(vec3(52 , -480 , 233)) ;
	//
	for (int i = 0; i < 3; i++)
	{
		radiostation[i]= load_object("data/models/radiostation/3ds file.3ds",radiostation[i]) ;
	}
	radiostation[0] ->ModelMatrix = translate(vec3(50 , -480 , 50));
	radiostation[1]	->ModelMatrix = translate(vec3 (131 ,-480 , 181) ) ;
	radiostation[2] ->ModelMatrix = translate(vec3(-23 , -480 ,233)) ;
		//
	for (int i = 0; i < 6; i++)
	{
		planes[i]= load_object("data/models/Spitfire/spit.obj",planes[i]) ;
		hanger[i] = load_object("data/models/Workshop_Building/3ds file.3ds" , hanger[i]) ;
		//hanger[i] ->ModelMatrix *= scale(0.2f ,0.2f ,0.2f ) ;
	}
	hanger[0]->ModelMatrix  *= translate(vec3( -25,-480, -20)) * scale(0.1f,0.1f,0.1f)  *rotate ( -90.0f , vec3(0,1,0));
	hanger[1]->ModelMatrix  *= translate(vec3( -25,-480, 60)) * scale(0.1f,0.1f,0.1f)  *rotate ( -90.0f , vec3(0,1,0));
	hanger[2]->ModelMatrix  *= translate(vec3( -25,-480, 120)) * scale(0.1f,0.1f,0.1f)  *rotate ( -90.0f , vec3(0,1,0));
	hanger[3]->ModelMatrix  *= translate(vec3( 130,-480, -20)) * scale(0.1f,0.1f,0.1f)  *rotate ( -90.0f , vec3(0,1,0));
	hanger[4]->ModelMatrix  *= translate(vec3( 130,-480, 60)) * scale(0.1f,0.1f,0.1f)  *rotate ( -90.0f , vec3(0,1,0));
	hanger[5]->ModelMatrix  *= translate(vec3( 130,-480, 120)) * scale(0.1f,0.1f,0.1f)  *rotate ( -90.0f , vec3(0,1,0));
	planes[0]-> ModelMatrix *= translate(vec3(-20 , -480 , -40)) * rotate (-45.0f , vec3 (0,1,0));
	planes[1]-> ModelMatrix *= translate(vec3(-20 , -480 , 82)) * rotate (-60.0f , vec3 (0,1,0));
	planes[2]-> ModelMatrix *= translate(vec3(-20 , -480 , 15)) * rotate (-80.0f , vec3 (0,1,0));
	planes[3]-> ModelMatrix *= translate(vec3(-20 , -480 ,  28)) * rotate (20.0f , vec3 (0,1,0));
	planes[4]-> ModelMatrix *= translate(vec3( 140 , -480 , 100)) * rotate (-60.0f , vec3 (0,1,0));
	planes[5]-> ModelMatrix *= translate(vec3( 140 , -480 , -3)) * rotate (-60.0f , vec3 (0,1,0));

	//
	/*
	air_port->ModelMatrix= translate(vec3(20.0f,-240.0f,200.0f)) ;
	for(int i=0 ;i<5;i++)
	{
		rings[i]=load_object("data/models/moataz/ring.obj",rings[i]) ;
	}
	rings[0]->ModelMatrix = translate(vec3(0.0f,0.0f,0.0f));
	rings[1]->ModelMatrix = translate(vec3(0.0f,50.0f,-40.0f));
	rings[2]->ModelMatrix = translate(vec3(50.0f,0.0f,-80.0f));
	rings[3]->ModelMatrix = translate(vec3(0.0f,-50.0f,-120.0f));
	rings[4]->ModelMatrix = translate(vec3(-50.0f,0.0f,-160.0f));
	radiost = load_object("data/models/radiostation/3ds file.3ds",radiost);
	radiost->ModelMatrix =scale(vec3(20.0f,20.0f,20.0f))* translate(vec3(2.0f,-240.0f,100.0f));
	spitfire = load_object("data/models/Spitfire/spit.3ds",spitfire);
	spitfire->ModelMatrix = translate(vec3(33.0f,-235.0f,100.0f));
	radar = load_object("data/models/Radar/Radar.obj",radar);
	radar->ModelMatrix = translate(vec3(10.0f,-240.0f,100.0f));
	controlTower = load_object("data/models/Airbase Control Tower/tower.obj",controlTower);
	controlTower->ModelMatrix = translate(vec3(35.0f,-240.0f,150.0f));
	*/

#pragma endregion  loading_models

#pragma region system
	
	programID = LoadShaders("model.vertexshader", "model.fragmentshader");
	shader.LoadProgram();
	VPID = glGetUniformLocation(programID, "VP");
	ModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	glUseProgram(programID);
#pragma endregion system
	Ground =new Texture("photos-2015-09-18-fst_419idkjsucr.jpg",0);
	airstrip =new Texture("road_base_asphalt_0001_01.jpg" ,1) ;
	// Use our shader
	initPointLight() ;
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// FirstPersonCamera
	myCamera = std::unique_ptr<FirstPersonCamera>(new FirstPersonCamera());
	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f, (float)ApplicationManager::WindowSizeWidth / (float)ApplicationManager::WindowSizeHeight, 0.1f, 5000.0f);
	// View matrix : 
	myCamera->Reset(
		+0.0f, -472.5f, +490.0f,// Camera Position  0,5,20
		+0.0f, -477.0f, +470.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
	//////////////////////////////////////////////////////////////////////////
	FPC_check = false;
	automatic = false;
	outOfBoundry = false;
	speedValue = 1.0f;
	rotationValue = 1.0f;
	movementSpeed = 1.0f;
	rotationAngle = 1.0f;
	my_plane->initPos.x = 0.0f;
	my_plane->initPos.y = -477.5f;
	my_plane->initPos.z = 470.0f;
	fpcPos = vec3(0.0f,0.0f,-10.0f);
	tpcPos = vec3(0.0f,5.0f,20.0f);
	camPos = tpcPos;
	my_plane->ModelMatrix = glm::translate(my_plane->initPos);
	my_plane->UpdatePosition();
	VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
}

void Renderer::Draw()
{
	glUniformMatrix4fv(VPID, 1, GL_FALSE, &VP[0][0]);
	VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	shader.BindVPMatrix(&VP[0][0]);
	for (int i = 0; i < 6; i++)
	{
		draw_object(hanger[i]);
		draw_object(planes[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		draw_object(radar[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		draw_object(radiostation[i]) ;
	}
	for (int i = 0; i < 2; i++)
	{
		draw_object(controlTower[i]);
		draw_object(bus[i]) ;
	}
	draw_object(skybox) ;
	draw_object(my_plane) ;
	draw_object(radar[0]);
	draw_object(radar[1]);
	draw_object(radiostation[0]);

	Ground->Bind() ;
	floorM = translate(glm::vec3(0.0f,-480.5f,-1.0f))*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f))*glm::scale(glm::vec3(600, 600, 4));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);
	mySquare->Draw();
	// ground 
#pragma region airstrip
	airstrip->Bind();
	floorM = translate(glm::vec3(5.0f,-480.0f,-1.0f))*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f))*glm::scale(glm::vec3(10, 600, 2));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);
	mySquare->Draw(); 
	//road_1
	airstrip->Bind();
	floorM = translate(glm::vec3(25.0f,-480.0f,-1.0f))*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f))*glm::scale(glm::vec3(10, 600, 2));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);
	mySquare->Draw();
	// road_2
	airstrip->Bind() ;
	floorM = translate(glm::vec3(50.0f,-480.0f,-25.0f))*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f)) * rotate(90.0f , vec3(0,0,1)) *glm::scale(glm::vec3(15, 20, 35));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);
	mySquare->Draw();
	// side road
	airstrip->Bind();
	floorM = translate(glm::vec3(80.0f,-480.0f,-1.0f))*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f))*glm::scale(glm::vec3(10, 600, 2));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);
	mySquare->Draw();
	//
	airstrip->Bind();
	floorM = translate(glm::vec3(100.0f,-480.0f,-1.0f))*glm::rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f))*glm::scale(glm::vec3(10, 600, 2));
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &floorM[0][0]);
	mySquare->Draw();
#pragma endregion

	if(!FPC_check)
			draw_object(my_plane);
}

void Renderer::Cleanup()
{
	glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{

	if(automatic)
	{
		my_plane->ModelMatrix *= glm::translate(0.0f, 0.0f, -movementSpeed*30*(float)deltaTime);

		if(FPC_check)
		{
			// Place FPC behind the plane
			my_plane->ModelMatrix *= glm::translate(-camPos);
			my_plane->UpdatePosition();
			myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
			my_plane->ModelMatrix *= glm::translate(camPos);
			my_plane->UpdatePosition();
			
			// Make the Camera look at the plane
			myCamera->setmDirection(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);

			// Place FPC in front of the plane
			my_plane->ModelMatrix *= glm::translate(camPos);
			my_plane->UpdatePosition();
			myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
			my_plane->ModelMatrix *= glm::translate(-camPos);
			my_plane->UpdatePosition();	
		}
		else
		{
			my_plane->ModelMatrix *= glm::translate(camPos);
			my_plane->UpdatePosition();
			myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
			my_plane->ModelMatrix *= glm::translate(-camPos);
			my_plane->UpdatePosition();
		
			myCamera->setmDirection(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
		}
		myCamera->UpdateViewMatrix();
		objectCollider();
	}
}

void Renderer::HandleKeyboardInput(int key, int action)
{
	
	movementSpeed = speedValue;
	rotationAngle = rotationValue;
	

	if(FPC_check == true)
	{
		switch (key)
		{		
	
		case GLFW_KEY_V:
			FPC_check = false;
			break;

		case GLFW_KEY_Z:
			automatic = true;
			break;

		case GLFW_KEY_X:
			automatic = false;
			break;
		
		//Moving forward
		case GLFW_KEY_UP:
		case GLFW_KEY_W:
			//myCamera->Walk(1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, 0.0f, -movementSpeed);
			break;

		//Moving backword
		case GLFW_KEY_DOWN:
		case GLFW_KEY_S:
			//myCamera->Walk(-1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, 0.0f, movementSpeed);
			break;

		// Moving right
		case GLFW_KEY_RIGHT:
		case GLFW_KEY_D:
			//myCamera->Strafe(1.0);
			my_plane->ModelMatrix *= glm::translate(movementSpeed, 0.0f, 0.0f);
			break;

		// Moving left
		case GLFW_KEY_LEFT:
		case GLFW_KEY_A:
			//myCamera->Strafe(-1.0);
			my_plane->ModelMatrix *= glm::translate(-movementSpeed, 0.0f, 0.0f);
			break;

		// Moving up
		case GLFW_KEY_SPACE:
		case GLFW_KEY_R:
			//myCamera->Fly(1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, movementSpeed, 0.0f);
			break;

		// Moving down
		case GLFW_KEY_LEFT_CONTROL:
		case GLFW_KEY_F:
			//myCamera->Fly(-1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, -movementSpeed, 0.0f);
			break;

		case GLFW_KEY_I:
			my_plane->ModelMatrix *= glm::rotate(rotationAngle, glm::vec3(1, 0, 0));
			myCamera->Pitch(rotationAngle);
			break;

		case GLFW_KEY_K:
			my_plane->ModelMatrix *= glm::rotate(-rotationAngle, glm::vec3(1, 0, 0));
			myCamera->Pitch(-rotationAngle);
			break;

		case GLFW_KEY_L:
			my_plane->ModelMatrix *= glm::rotate(-rotationAngle, glm::vec3(0, 1, 0));
			myCamera->Yaw(-rotationAngle);
			break;

		case GLFW_KEY_J:
			my_plane->ModelMatrix *= glm::rotate(rotationAngle, glm::vec3(0, 1, 0));
			myCamera->Yaw(rotationAngle);
			break;

		case GLFW_KEY_O:
			my_plane->ModelMatrix *= glm::rotate(-rotationAngle, glm::vec3(0, 0, 1));
			myCamera->Roll(-rotationAngle);
			break;

		case GLFW_KEY_U:
			my_plane->ModelMatrix *= glm::rotate(rotationAngle, glm::vec3(0, 0, 1));
			myCamera->Roll(rotationAngle);
			break;

		default:
			break;
		}
		
		camPos = fpcPos;

		my_plane->ModelMatrix *= glm::translate(-camPos);
		my_plane->UpdatePosition();
		myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
		my_plane->ModelMatrix *= glm::translate(camPos);
		my_plane->UpdatePosition();
		
		myCamera->setmDirection(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);

		my_plane->ModelMatrix *= glm::translate(camPos);
		my_plane->UpdatePosition();
		myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
		my_plane->ModelMatrix *= glm::translate(-camPos);
		my_plane->UpdatePosition();
		
	}
	else
	{
		switch (key)
		{
		/*case GLFW_KEY_0 :
			cout<<my_plane->xPosition << " " << my_plane->yPosition << " "<< my_plane->zPosition << endl ;
			break ;*/
		case GLFW_KEY_B:
			FPC_check = true;
			break;

		case GLFW_KEY_Z:
			automatic = true;
			break;

		case GLFW_KEY_X:
			automatic = false;
			break;

		//Moving forward
		case GLFW_KEY_UP:
		case GLFW_KEY_W:
			//myCamera->Walk(1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, 0.0f, -movementSpeed);
			break;

		//Moving backword
		case GLFW_KEY_DOWN:
		case GLFW_KEY_S:
			//myCamera->Walk(-1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, 0.0f, movementSpeed);
			break;

		// Moving right
		case GLFW_KEY_RIGHT:
		case GLFW_KEY_D:
			//myCamera->Strafe(1.0);
			my_plane->ModelMatrix *= glm::translate(movementSpeed, 0.0f, 0.0f);
			break;

		// Moving left
		case GLFW_KEY_LEFT:
		case GLFW_KEY_A:
			//myCamera->Strafe(-1.0);
			my_plane->ModelMatrix *= glm::translate(-movementSpeed, 0.0f, 0.0f);
			break;

		// Moving up
		case GLFW_KEY_SPACE:
		case GLFW_KEY_R:
			//myCamera->Fly(1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, movementSpeed, 0.0f);
			break;

		// Moving down
		case GLFW_KEY_LEFT_CONTROL:
		case GLFW_KEY_F:
			//myCamera->Fly(-1.0);
			my_plane->ModelMatrix *= glm::translate(0.0f, -movementSpeed, 0.0f);
			break;

		case GLFW_KEY_I:
			my_plane->ModelMatrix *= glm::rotate(rotationAngle, glm::vec3(1, 0, 0));
			myCamera->Pitch(rotationAngle);
			break;

		case GLFW_KEY_K:
			my_plane->ModelMatrix *= glm::rotate(-rotationAngle, glm::vec3(1, 0, 0));
			myCamera->Pitch(-rotationAngle);
			break;

		case GLFW_KEY_L:
			my_plane->ModelMatrix *= glm::rotate(-rotationAngle, glm::vec3(0, 1, 0));
			myCamera->Yaw(-rotationAngle);
			break;

		case GLFW_KEY_J:
			my_plane->ModelMatrix *= glm::rotate(rotationAngle, glm::vec3(0, 1, 0));
			myCamera->Yaw(rotationAngle);
			break;

		case GLFW_KEY_O:
			my_plane->ModelMatrix *= glm::rotate(-rotationAngle, glm::vec3(0, 0, 1));
			myCamera->Roll(-rotationAngle);
			break;

		case GLFW_KEY_U:
			my_plane->ModelMatrix *= glm::rotate(rotationAngle, glm::vec3(0, 0, 1));
			myCamera->Roll(rotationAngle);
			break;

		default:
			break;
		}
		
		camPos = tpcPos;

		my_plane->ModelMatrix *= glm::translate(camPos);
		my_plane->UpdatePosition();
		myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
		my_plane->ModelMatrix *= glm::translate(-camPos);
		my_plane->UpdatePosition();
		
		myCamera->setmDirection(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);

	}

	myCamera->UpdateViewMatrix();
	objectCollider();
}

void Renderer::HandleMouse(double deltaX, double deltaY)
{
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();
}
Model3D* Renderer::load_object(string path ,Model3D  *my_model)
{
	 my_model = new Model3D();
	 my_model->LoadFromFile(path,false);
     my_model->Initialize();
	 return my_model;
     
}
void Renderer::draw_object(Model3D * my_model )
{
	my_model->Render(&shader,my_model->ModelMatrix);
}

void Renderer::objectCollider()
{
	
	outOfBoundry = false;

	if(	my_plane->yPosition < -477.5f)
	{
		my_plane->ModelMatrix[3][1] = -477.5f;
		my_plane->UpdatePosition();
		myCamera->Reset(
		camPos.x, camPos.y, camPos.z,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		outOfBoundry = true;
	}
	if(my_plane->xPosition > 490.0f)
	{
		//redundancy = 240.0f - my_plane->xPosition;
		my_plane->ModelMatrix = glm::translate(my_plane->initPos);
		myCamera->Reset(
		camPos.x, camPos.y, camPos.z,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		outOfBoundry = true;
	}
	else if(my_plane->xPosition < -490.0f)
	{
		//redundancy = my_plane->xPosition + 240.0f;
		//my_plane->ModelMatrix *= glm::translate(-redundancy, 0.0f, 0.0f);
		my_plane->ModelMatrix = glm::translate(my_plane->initPos);
		myCamera->Reset(
		camPos.x, camPos.y, camPos.z,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		outOfBoundry = true;
	}
	else if(my_plane->yPosition > 490.0f)
	{
		//redundancy = 240.0f - my_plane->yPosition;
		//my_plane->ModelMatrix *= glm::translate(0.0f, redundancy, 0.0f);
		my_plane->ModelMatrix = glm::translate(my_plane->initPos);
		myCamera->Reset(
		camPos.x, camPos.y, camPos.z,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		outOfBoundry = true;
	}
	else if(my_plane->yPosition < -490.0f)
	{
		//redundancy = my_plane->yPosition + 240.0f;
		//my_plane->ModelMatrix *= glm::translate(0.0f, -redundancy, 0.0f);
		my_plane->ModelMatrix = glm::translate(my_plane->initPos);
		myCamera->Reset(
		camPos.x, camPos.y, camPos.z,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		outOfBoundry = true;
	}
	else if(my_plane->zPosition > 490.0f)
	{
		//redundancy = 240.0f - my_plane->zPosition;
		//my_plane->ModelMatrix *= glm::translate(0.0f, 0.0f, redundancy);
		my_plane->ModelMatrix = glm::translate(my_plane->initPos);
		myCamera->Reset(
		camPos.x, camPos.y, camPos.z,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		outOfBoundry = true;
	}
	else if(my_plane->zPosition < -490.0f)
	{
		//redundancy = my_plane->zPosition + 240.0f;
		//my_plane->ModelMatrix *= glm::translate(0.0f, 0.0f, -redundancy);
		my_plane->ModelMatrix = glm::translate(my_plane->initPos);
		myCamera->Reset(
		camPos.x, camPos.y, camPos.z,// Camera Position
		+0.0f, +0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		outOfBoundry = true;
	}

	if(outOfBoundry)
	{
		if(FPC_check)
		{
			my_plane->ModelMatrix *= glm::translate(-camPos);
			my_plane->UpdatePosition();
			myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
			my_plane->ModelMatrix *= glm::translate(camPos);
			my_plane->UpdatePosition();
		
			myCamera->setmDirection(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);

			my_plane->ModelMatrix *= glm::translate(camPos);
			my_plane->UpdatePosition();
			myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
			my_plane->ModelMatrix *= glm::translate(-camPos);
			my_plane->UpdatePosition();
		}
		else
		{
			my_plane->ModelMatrix *= glm::translate(camPos);
			my_plane->UpdatePosition();
			myCamera->setmPosition(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
			my_plane->ModelMatrix *= glm::translate(-camPos);
			my_plane->UpdatePosition();
		
			myCamera->setmDirection(my_plane->xPosition, my_plane->yPosition, my_plane->zPosition);
		}
		myCamera->UpdateViewMatrix();
		
	}

}
void Renderer::initPointLight()
{
	// Configure the light.

	//setup the light position.
	LightPositionID = glGetUniformLocation(shader.programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(my_plane->xPosition,my_plane->yPosition,my_plane->zPosition);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);

	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(shader.programID,"ambientLight");
	ambientLight = glm::vec3(0.1,0.1,0.1);//(0.1,0.1,0.1);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);

	//setup the eye position.
	EyePositionID = glGetUniformLocation(shader.programID,"EyePosition_worldspace");
}

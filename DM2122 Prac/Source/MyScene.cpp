#include <iostream>
#include <iomanip>
#include <sstream>
#include "MyScene.h"
#include "GL\glew.h"
#include "Application.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "SceneManager.h"

extern double elapsedTime;

void MyScene::InitLight(){
	//Get a handle for each uniform
	m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE_ENABLED)] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE)] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_ENABLED)] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_COLOR)] = glGetUniformLocation(m_programID, "textColor");
	m_parameters[unsigned int(UNIFORM_TYPE::U_NUMLIGHTS)] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[unsigned int(UNIFORM_TYPE::U_MVP)] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[unsigned int(UNIFORM_TYPE::U_MODELVIEW)] = glGetUniformLocation(m_programID, "MV");
	m_parameters[unsigned int(UNIFORM_TYPE::U_MODELVIEW_INVERSE_TRANSPOSE)] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_AMBIENT)] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_DIFFUSE)] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_SPECULAR)] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_SHININESS)] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHTENABLED)] = glGetUniformLocation(m_programID, "lightEnabled");

	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_TYPE)] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_SPOTDIRECTION)] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_COSCUTOFF)] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_COSINNER)] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_EXPONENT)] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POSITION)] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_COLOR)] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POWER)] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_KC)] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_KL)] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_KQ)] = glGetUniformLocation(m_programID, "lights[0].kQ");
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_TYPE)], GLint(light[0].type));
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_COLOR)], 1, &light[0].color.R);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POWER)], light[0].power);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_KC)], light[0].kC);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_KL)], light[0].kL);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_KQ)], light[0].kQ);
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_SPOTDIRECTION)], 1, &light[0].spotDirection.x);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_COSCUTOFF)], light[0].cosCutoff);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_COSINNER)], light[0].cosInner);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_EXPONENT)], light[0].exponent);

	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_TYPE)] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_SPOTDIRECTION)] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_COSCUTOFF)] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_COSINNER)] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_EXPONENT)] = glGetUniformLocation(m_programID, "lights[1].exponent");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_POSITION)] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_COLOR)] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_POWER)] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_KC)] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_KL)] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_KQ)] = glGetUniformLocation(m_programID, "lights[1].kQ");
	light[1].power = 0.f;
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_TYPE)], GLint(light[1].type));
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_COLOR)], 1, &light[1].color.R);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_POWER)], light[1].power);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_KC)], light[1].kC);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_KL)], light[1].kL);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_KQ)], light[1].kQ);
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_SPOTDIRECTION)], 1, &light[1].spotDirection.x);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_COSCUTOFF)], light[1].cosCutoff);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_COSINNER)], light[1].cosInner);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_EXPONENT)], light[1].exponent);

	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_TYPE)] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_SPOTDIRECTION)] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_COSCUTOFF)] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_COSINNER)] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_EXPONENT)] = glGetUniformLocation(m_programID, "lights[2].exponent");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_POSITION)] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_COLOR)] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_POWER)] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_KC)] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_KL)] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_KQ)] = glGetUniformLocation(m_programID, "lights[2].kQ");
	light[2].power = 0.f;
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_TYPE)], GLint(light[2].type));
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_COLOR)], 1, &light[2].color.R);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_POWER)], light[2].power);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_KC)], light[2].kC);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_KL)], light[2].kL);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_KQ)], light[2].kQ);
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_SPOTDIRECTION)], 1, &light[2].spotDirection.x);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_COSCUTOFF)], light[2].cosCutoff);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_COSINNER)], light[2].cosInner);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_EXPONENT)], light[2].exponent);

	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_TYPE)] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_SPOTDIRECTION)] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_COSCUTOFF)] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_COSINNER)] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_EXPONENT)] = glGetUniformLocation(m_programID, "lights[3].exponent");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_POSITION)] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_COLOR)] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_POWER)] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_KC)] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_KL)] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_KQ)] = glGetUniformLocation(m_programID, "lights[3].kQ");
	light[3].type = Light::LIGHT_TYPE::DIRECTIONAL;
	light[3].power = 1.4f;
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_TYPE)], GLint(light[3].type));
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_COLOR)], 1, &light[3].color.R);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_POWER)], light[3].power);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_KC)], light[3].kC);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_KL)], light[3].kL);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_KQ)], light[3].kQ);
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_SPOTDIRECTION)], 1, &light[3].spotDirection.x);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_COSCUTOFF)], light[3].cosCutoff);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_COSINNER)], light[3].cosInner);
	glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_EXPONENT)], light[3].exponent);

	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_NUMLIGHTS)], 4);
}

void MyScene::InitMeshes(){
	//Init Skybox meshes
	meshList[unsigned int(MESH::LEFT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::LEFT)]->textureID = LoadTGA("image//Skyboxes/Day/DayLeft.tga");
	meshList[unsigned int(MESH::RIGHT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::RIGHT)]->textureID = LoadTGA("image//Skyboxes/Day/DayRight.tga");
	meshList[unsigned int(MESH::TOP)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::TOP)]->textureID = LoadTGA("image//Skyboxes/Day/DayTop.tga");
	meshList[unsigned int(MESH::FRONT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::FRONT)]->textureID = LoadTGA("image//Skyboxes/Day/DayFront.tga");
	meshList[unsigned int(MESH::BACK)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::BACK)]->textureID = LoadTGA("image//Skyboxes/Day/DayBack.tga");

	//Init Boss meshes
	meshList[unsigned int(MESH::BOSS_BODY)] = MeshBuilder::GenerateOBJ("OBJ//BossCharacter/BossBody.obj");
	meshList[unsigned int(MESH::BOSS_ARM_L)] = MeshBuilder::GenerateOBJ("OBJ//BossCharacter/BossArm_L.obj");
	meshList[unsigned int(MESH::BOSS_ARM_R)] = MeshBuilder::GenerateOBJ("OBJ//BossCharacter/BossArm_R.obj");
	meshList[unsigned int(MESH::BOSS_LEG_LF)] = MeshBuilder::GenerateOBJ("OBJ//BossCharacter/BossLeg_LF.obj");
	meshList[unsigned int(MESH::BOSS_LEG_RF)] = MeshBuilder::GenerateOBJ("OBJ//BossCharacter/BossLeg_RF.obj");
	meshList[unsigned int(MESH::BOSS_LEG_LB)] = MeshBuilder::GenerateOBJ("OBJ//BossCharacter/BossLeg_LB.obj");
	meshList[unsigned int(MESH::BOSS_LEG_RB)] = MeshBuilder::GenerateOBJ("OBJ//BossCharacter/BossLeg_RB.obj");
	for(unsigned int i = unsigned int(MESH::BOSS_BODY); i <= unsigned int(MESH::BOSS_LEG_RB); ++i){
		meshList[i]->textureID = LoadTGA("image//Boss.tga");
	}

	//Init generic obj meshes
	meshList[unsigned int(MESH::BASEBALL_BAT)] = MeshBuilder::GenerateOBJ("OBJ//BaseballBat.obj");
	meshList[unsigned int(MESH::BASEBALL_BAT)]->textureID = LoadTGA("image//BaseballBat.tga");
	meshList[unsigned int(MESH::BENCH)] = MeshBuilder::GenerateOBJ("OBJ//Bench.obj");
	meshList[unsigned int(MESH::BENCH)]->textureID = LoadTGA("image//Bench.tga");
	meshList[unsigned int(MESH::POT)] = MeshBuilder::GenerateOBJ("OBJ//Pot.obj");
	meshList[unsigned int(MESH::POT)]->textureID = LoadTGA("image//Pot.tga");
	meshList[unsigned int(MESH::RECYCLING_BIN)] = MeshBuilder::GenerateOBJ("OBJ//RecyclingBin.obj");
	meshList[unsigned int(MESH::RECYCLING_BIN)]->textureID = LoadTGA("image//RecyclingBin.tga");
	meshList[unsigned int(MESH::TRASH)] = MeshBuilder::GenerateOBJ("OBJ//Trash.obj");
	meshList[unsigned int(MESH::TRASH)]->textureID = LoadTGA("image//Trash.tga");

	//Init Car meshes
	meshList[unsigned int(MESH::CAR_BODY)] = MeshBuilder::GenerateOBJ("OBJ//CarCharacter/CarBody.obj");
	meshList[unsigned int(MESH::CAR_WHEEL_LF)] = MeshBuilder::GenerateOBJ("OBJ//CarCharacter/CarWheel_LF.obj");
	meshList[unsigned int(MESH::CAR_WHEEL_RF)] = MeshBuilder::GenerateOBJ("OBJ//CarCharacter/CarWheel_RF.obj");
	meshList[unsigned int(MESH::CAR_WHEEL_LB)] = MeshBuilder::GenerateOBJ("OBJ//CarCharacter/CarWheel_LB.obj");
	meshList[unsigned int(MESH::CAR_WHEEL_RB)] = MeshBuilder::GenerateOBJ("OBJ//CarCharacter/CarWheel_RB.obj");
	for(unsigned int i = unsigned int(MESH::CAR_BODY); i <= unsigned int(MESH::CAR_WHEEL_RB); ++i){
		meshList[i]->textureID = LoadTGA("image//Car.tga");
	}

	//Init other meshes
	meshList[unsigned int(MESH::GROUND)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::GROUND)]->textureID = LoadTGA("image//Grass.tga");
	meshList[unsigned int(MESH::HUT)] = MeshBuilder::GenerateOBJ("OBJ//Hut.obj");
	meshList[unsigned int(MESH::HUT)]->textureID = LoadTGA("image//Hut.tga");
	meshList[unsigned int(MESH::LIGHT_SPHERE)] = MeshBuilder::GenerateSphere(Color(1.f, 1.f, 1.f), 20, 20, 1.f);
	meshList[unsigned int(MESH::BULLET)] = MeshBuilder::GenerateCuboid(Color(1.f, 0.f, 0.f), .4f, .4f, .4f);
	meshList[unsigned int(MESH::SMOKE)] = MeshBuilder::GenerateCuboid(Color(1.f, 1.f, 1.f), .8f, .8f, .8f);
	meshList[unsigned int(MESH::TEXT)] = MeshBuilder::GenerateText(16, 16);
	meshList[unsigned int(MESH::TEXT)]->textureID = LoadTGA("image//Font.tga");
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)] = MeshBuilder::GenerateText(16, 16);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)]->textureID = LoadTGA("image//FontOnScreen.tga");
	meshList[unsigned int(MESH::TURRET_TOP)] = MeshBuilder::GenerateOBJ("OBJ//TurretObj/TurretTop.obj");
	meshList[unsigned int(MESH::TURRET_BOTTOM)] = MeshBuilder::GenerateOBJ("OBJ//TurretObj/TurretBottom.obj");
}

void MyScene::Init(){ //Init scene
	glGenVertexArrays(1, &m_vertexArrayID); //Generate a default VAO
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_CULL_FACE); //Enable back-face culling
	glEnable(GL_BLEND); //Enable blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST); //Enable depth test
	m_programID = LoadShaders("Shader//vShader.vertexshader", "Shader//fShader.fragmentshader"); //Load shaders
	glUseProgram(m_programID);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	Camera::getCam().Init(car.getPos() + Vector3(0.f, 5.f, -30.f), car.getPos(), Vector3(0.f, 1.f, 0.f));
	InitLight();
	InitMeshes();
	bulletGenerator.InitParticles();
	smokeEmitter.InitParticles();
	showDebugInfo = 1;
	showLightSphere = vibrate = 0;
	autoBounceTime = 10.0;
	changeBounceTime = dayBounceTime = debugBounceTime = flickerBounceTime = lightBounceTime = 0.0;
}

void MyScene::Exit(Scene* newScene){ //Exit scene
	for(int i = 0; i < int(MESH::NUM_GEOMETRY); ++i){
		if(meshList[i] != 0){
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
	if(dynamic_cast<MyScene*>(newScene) != this){
		newScene->Init();
	}
}

void MyScene::UpdateCar(double dt){
	car.setSpeed(float(dt) * 30.f); //Set Car speed
	if(Application::IsKeyPressed(VK_UP)){ //Move forward
		Vector3 front = (car.getTarget() - car.getPos()).Normalized();
		front.y = 0;
		car.setWheelSpinAngle(car.getWheelSpinAngle() + car.getSpeed() * 30);
		car.setPos(car.getPos() + car.getSpeed() * front);
		car.setTarget(car.getTarget() + car.getSpeed() * front);
		light[0].position.x += car.getSpeed() * front.x;
		light[1].position.x += car.getSpeed() * front.x;
		light[2].position.x += car.getSpeed() * front.x;
		light[0].position.z += car.getSpeed() * front.z;
		light[1].position.z += car.getSpeed() * front.z;
		light[2].position.z += car.getSpeed() * front.z;

		//Spawn smoke particles
		if(smokeBounceTime <= elapsedTime && smokeEmitter.currAmt < smokeEmitter.maxAmt){
			Particle* p = smokeEmitter.particlePool[smokeEmitter.GetIndex()];
			p->color = Color(1.f, 1.f, 1.f);
			p->dir = (car.getTarget() - car.getPos()).Normalized();
			p->dir.y = 0.f;
			p->life = 1.5f;
			p->pos = car.getPos() - p->dir * 7.f;
			++smokeEmitter.currAmt;
			smokeBounceTime = elapsedTime + 0.15;
		}
	}
	if(Application::IsKeyPressed(VK_DOWN)){ //Move backward
		Vector3 front = (car.getTarget() - car.getPos()).Normalized();
		front.y = 0;
		car.setWheelSpinAngle(car.getWheelSpinAngle() - car.getSpeed() * 30);
		car.setPos(car.getPos() - car.getSpeed() * front);
		car.setTarget(car.getTarget() - car.getSpeed() * front);
		light[0].position.x -= car.getSpeed() * front.x;
		light[1].position.x -= car.getSpeed() * front.x;
		light[2].position.x -= car.getSpeed() * front.x;
		light[0].position.z -= car.getSpeed() * front.z;
		light[1].position.z -= car.getSpeed() * front.z;
		light[2].position.z -= car.getSpeed() * front.z;
	}

	Mtx44 r;
	if(Application::IsKeyPressed(VK_LEFT)){ //Turn left
		Vector3 front = (car.getTarget() - car.getPos()).Normalized();
		front.y = 0;
		if(car.getWheelTurnAngle() < 4.f){
			car.setWheelTurnAngle(car.getWheelTurnAngle() + .5f);
		}
		if(Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed(VK_DOWN)){
			if(Application::IsKeyPressed(VK_UP)){
				car.setBodyTurnAngle(car.getBodyTurnAngle() + 1.5f);
				r.SetToRotation(1.5f, 0.f, 1.f, 0.f);
			} else{
				car.setBodyTurnAngle(car.getBodyTurnAngle() - 1.5f);
				r.SetToRotation(-1.5f, 0.f, 1.f, 0.f);
			}
			front = r * front;
			car.setTarget(car.getPos() + front);

		}
	}
	if(Application::IsKeyPressed(VK_RIGHT)){ //Turn right
		Vector3 front = (car.getTarget() - car.getPos()).Normalized();
		front.y = 0;
		if(car.getWheelTurnAngle() > -4.f){
			car.setWheelTurnAngle(car.getWheelTurnAngle() - .5f);
		}
		if(Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed(VK_DOWN)){
			if(Application::IsKeyPressed(VK_UP)){
				car.setBodyTurnAngle(car.getBodyTurnAngle() - 1.5f);
				r.SetToRotation(-1.5f, 0.f, 1.f, 0.f);
			} else{
				car.setBodyTurnAngle(car.getBodyTurnAngle() + 1.5f);
				r.SetToRotation(1.5f, 0.f, 1.f, 0.f);
			}
			front = r * front;
			car.setTarget(car.getPos() + front);
		}
	}
	if(Application::IsKeyPressed(VK_LEFT) - Application::IsKeyPressed(VK_RIGHT) && Application::IsKeyPressed(VK_UP) - Application::IsKeyPressed(VK_DOWN)){ //Update light according to motion of car
		Vector3 front = (car.getTarget() - car.getPos()).Normalized();
		front.y = 0;
		light[1].spotDirection = -front.Normalized();
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_SPOTDIRECTION)], 1, &light[1].spotDirection.x);
		light[2].spotDirection = -front.Normalized();
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_SPOTDIRECTION)], 1, &light[2].spotDirection.x);
		Vector3 vec = Vector3(light[1].position.x, light[1].position.y, light[1].position.z) - car.getPos(); //Vec of car pos to light[1] pos
		vec = r * vec;
		light[1].position.x = car.getPos().x + vec.x;
		light[1].position.z = car.getPos().z + vec.z;
		vec = Vector3(light[2].position.x, light[2].position.y, light[2].position.z) - car.getPos(); //Vec of car pos to light[2] pos
		vec = r * vec;
		light[2].position.x = car.getPos().x + vec.x;
		light[2].position.z = car.getPos().z + vec.z;
	}

	//Jump, mini jump, double jump
	if(Application::IsKeyPressed(VK_SPACE) && car.getMaxJump() && car.isKeyReleased()){
		car.setJumpHeight(1.3f);
		car.setJumping(1);
		car.setKeyReleased(0);
		car.reduceMaxJump();
	}
	if(!Application::IsKeyPressed(VK_SPACE)){
		car.setKeyReleased(1);
		if(car.isJumping() && car.getJumpHeight() > 0.0f){
			car.setJumpHeight(0.f);
		}
	}
	if(car.isJumping()){
		car.setPos(car.getPos() + Vector3(0.f, car.getJumpHeight(), 0.f));
		car.setTarget(car.getTarget() + Vector3(0.f, car.getJumpHeight(), 0.f));
		car.setJumpHeight(car.getJumpHeight() - car.getGrav());
	}
	if(car.getPos().y < 0.0f){
		car.setPos(Vector3(car.getPos().x, 0.f, car.getPos().z));
		car.setJumpHeight(0.f);
		car.setJumping(0);
		car.setMaxJump(2);
	}

	if(car.getWheelSpinAngle() >= 360.f){ //Limit wheel spin angle
		car.setWheelSpinAngle(car.getWheelSpinAngle() - 360.f);
	}
	if(car.getBodyTurnAngle() >= 360.f){ //Limit body turn angle
		car.setBodyTurnAngle(car.getBodyTurnAngle() - 360.f);
	}
	if(car.getWheelTurnAngle() && !Application::IsKeyPressed(VK_LEFT) && !Application::IsKeyPressed(VK_RIGHT)){ //Set wheel turn angle for when car tries to turn while stationary
		car.setWheelTurnAngle(car.getWheelTurnAngle() - (car.getWheelTurnAngle() / abs(car.getWheelTurnAngle())) * .5f);
	}
	scaleFactor = 500.f + sqrt(pow(car.getPos().x, 2) + pow(car.getPos().z, 2)) * 2.5f;
	smokeEmitter.UpdateParticles(dt, car);
}

void MyScene::Update(double dt, float FOV){ //Update scene
	UpdateCar(dt); //Update Car
	for(int i = 0; i < 13; ++i){
		if(Application::IsKeyPressed(keys[i])){
			switch(keys[i]){
				case '1': glDisable(GL_CULL_FACE); break; //Disable back-face culling
				case '2': glEnable(GL_CULL_FACE); break; //Enable back-face culling
				case '3': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break; //Set polygon mode to GL_FILL (default mode)
				case '4': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break; //Set polygon mode to GL_LINE (wireframe mode)
				case '5': { //Change to point light
					light[0].type = Light::LIGHT_TYPE::POINT;
					glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_TYPE)], GLint(light[0].type));
					break;
				}
				case '6': { //Change to directional light
					light[0].type = Light::LIGHT_TYPE::DIRECTIONAL;
					glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_TYPE)], GLint(light[0].type));
					break;
				}
				case '7': { //Change to spotlight
					light[0].type = Light::LIGHT_TYPE::SPOT;
					glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_TYPE)], GLint(light[0].type));
					break;
				}
				case 'I': light[0].position.z += float(10.f * dt); break; //Move light in the direction of the positive z-axis
				case 'J': light[0].position.x += float(10.f * dt); break; //Move light in the direction of the positive x-axis
				case 'K': light[0].position.z -= float(10.f * dt); break; //Move light in the direction of the negative z-axis
				case 'L': light[0].position.x -= float(10.f * dt); break; //Move light in the direction of the negative x-axis
				case 'O': light[0].position.y -= float(10.f * dt); break; //Move light in the direction of the negative y-axis
				case 'U': light[0].position.y += float(10.f * dt); break; //Move light in the direction of the positive y-axis
			}
		}
	}
	if(Application::IsKeyPressed('P') && lightBounceTime <= elapsedTime){ //Show/Hide light sphere
		showLightSphere = !showLightSphere;
		lightBounceTime = elapsedTime + 0.4;
	}
	if(changeBounceTime <= elapsedTime){ //Change light color randomly
		light[0].color.Set(float(rand() % 999 + 1) / 1000.f, float(rand() % 999 + 1) / 1000.f, float(rand() % 999 + 1) / 1000.f);
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_COLOR)], 1, &light[0].color.R);
		changeBounceTime = elapsedTime + 0.99;
	}
	if(flickerBounceTime <= elapsedTime){ //Change light power randomly
		light[0].power = float(rand() % 11 + 10) / 10.f;
		glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POWER)], light[0].power);
		flickerBounceTime = elapsedTime + 0.05;
	}
	if((Application::IsKeyPressed('M') && dayBounceTime <= elapsedTime) || autoBounceTime <= elapsedTime){ //Change time of day and update light accordingly
		if(light[3].color.R == 0.f){
			light[1].power = 0.f;
			light[2].power = 0.f;
			light[3].color.Set(1.f, 1.f, 1.f); //White
			light[3].position.Set(0.f, 1.f, 200.f);
			meshList[unsigned int(MESH::LEFT)]->textureID = LoadTGA("image//Skyboxes/Day/DayLeft.tga");
			meshList[unsigned int(MESH::RIGHT)]->textureID = LoadTGA("image//Skyboxes/Day/DayRight.tga");
			meshList[unsigned int(MESH::TOP)]->textureID = LoadTGA("image//Skyboxes/Day/DayTop.tga");
			meshList[unsigned int(MESH::FRONT)]->textureID = LoadTGA("image//Skyboxes/Day/DayFront.tga");
			meshList[unsigned int(MESH::BACK)]->textureID = LoadTGA("image//Skyboxes/Day/DayBack.tga");
		} else if(light[3].color.B == 0.f){
			light[1].power = 5.f;
			light[2].power = 5.f;
			light[3].color.Set(0.f, 0.f, 1.f); //Blue
			light[3].position.Set(0.f, 100.f, 0.f);
			meshList[unsigned int(MESH::LEFT)]->textureID = LoadTGA("image//Skyboxes/Night/NightLeft.tga");
			meshList[unsigned int(MESH::RIGHT)]->textureID = LoadTGA("image//Skyboxes/Night/NightRight.tga");
			meshList[unsigned int(MESH::TOP)]->textureID = LoadTGA("image//Skyboxes/Night/NightTop.tga");
			meshList[unsigned int(MESH::FRONT)]->textureID = LoadTGA("image//Skyboxes/Night/NightFront.tga");
			meshList[unsigned int(MESH::BACK)]->textureID = LoadTGA("image//Skyboxes/Night/NightBack.tga");
		} else{
			light[3].color.Set(1.f, 0.647f, 0.f); //Orange
			light[3].position.Set(0.f, 1.f, -200.f);
			meshList[unsigned int(MESH::LEFT)]->textureID = LoadTGA("image//Skyboxes/Dusk/DuskLeft.tga");
			meshList[unsigned int(MESH::RIGHT)]->textureID = LoadTGA("image//Skyboxes/Dusk/DuskRight.tga");
			meshList[unsigned int(MESH::TOP)]->textureID = LoadTGA("image//Skyboxes/Dusk/DuskTop.tga");
			meshList[unsigned int(MESH::FRONT)]->textureID = LoadTGA("image//Skyboxes/Dusk/DuskFront.tga");
			meshList[unsigned int(MESH::BACK)]->textureID = LoadTGA("image//Skyboxes/Dusk/DuskBack.tga");
		}
		glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_POWER)], light[1].power);
		glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_POWER)], light[2].power);
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_COLOR)], 1, &light[3].color.R);
		autoBounceTime = elapsedTime + 10.0;
		dayBounceTime = elapsedTime + 0.2;
	}
	if(Application::IsKeyPressed(VK_SHIFT) && debugBounceTime <= elapsedTime){ //Show/Hide debug info
		showDebugInfo = !showDebugInfo;
		debugBounceTime = elapsedTime + 0.5;
	}

	if(Application::IsKeyPressed('T')){ //Spawn turret
		meshList[unsigned int(MESH::TURRET_TOP)]->textureID = 0;
		if(turretBounceTime <= elapsedTime && meshList[unsigned int(MESH::TURRET_TOP)]->textureID == 0){
			do{
				turretPos = Vector3(car.getPos().x + 30.f * cos(Math::DegreeToRadian(float(rand() % 45 + 1))) * cos(Math::DegreeToRadian(float(rand() % 45 + 1))) * (rand() & 1 ? 1 : -1),
					0.f, car.getPos().z + 30.f * cos(Math::DegreeToRadian(float(rand() % 45 + 1))) * sin(Math::DegreeToRadian(float(rand() % 45 + 1))) * (rand() & 1 ? 1 : -1));
			} while(turretPos == Vector3(0.f, 0.f, 0.f));
			turretFront = Vector3(0.f, 0.f, 30.f) - Vector3(turretPos.x, 0.f, turretPos.z);
			turretAngle = Math::RadianToDegree(acos(turretFront.Dot(Vector3(0.f, 0.f, 30.f)) / (turretFront.Length() * Vector3(0.f, 0.f, 30.f).Length())));
			if(turretPos.x > 0.f){
				turretAngle = 360.f - turretAngle;
			}
			meshList[unsigned int(MESH::TURRET_TOP)]->textureID = LoadTGA("image//TurretTopALB.tga");
			meshList[unsigned int(MESH::TURRET_BOTTOM)]->textureID = LoadTGA("image//TurretBottomALB.tga");
			turretBounceTime = elapsedTime + 3.0;
		}
	}
	if(meshList[unsigned int(MESH::TURRET_TOP)]->textureID != 0){ //Spawn bullets
		if(bulletBounceTime <= elapsedTime && bulletGenerator.currAmt < bulletGenerator.maxAmt){
			Particle* p = bulletGenerator.particlePool[bulletGenerator.GetIndex()];
			p->color = Color(1.f, 0.f, 0.f);
			p->dir = turretFront.Normalized();
			p->life = (turretPos - Vector3(0.f, 0.f, 30.f)).Length() / 26.f;
			p->pos = turretPos + p->dir * 2.5f + Vector3(0.f, 7.5f, 0.f);
			++bulletGenerator.currAmt;
			bulletBounceTime = elapsedTime + 0.2;
		}
		bulletGenerator.UpdateParticles(dt, turretPos);
	}
	if(vibrateBounceTime <= elapsedTime){ //Vibration control
		vibrate = !vibrate;
		vibrateBounceTime = elapsedTime + 0.04;
	}

	//Billboarding
	bossTextFront = Vector3(Camera::getCam().pos.x, 0.f, Camera::getCam().pos.z) - Vector3(0.f, 0.f, 30.f);
	bossTextAngle = Math::RadianToDegree(acos(bossTextFront.Dot(Vector3(0.f, 0.f, -30.f)) / (bossTextFront.Length() * Vector3(0.f, 0.f, -30.f).Length())));
	if(Camera::getCam().pos.x > 0.f){
		bossTextAngle = 360.f - bossTextAngle;
	}
	hutTextFront = Vector3(Camera::getCam().pos.x, 0.f, Camera::getCam().pos.z) - Vector3(0.f, 0.f, 65.f);
	hutTextAngle = Math::RadianToDegree(acos(hutTextFront.Dot(Vector3(0.f, 0.f, -65.f)) / (hutTextFront.Length() * Vector3(0.f, 0.f, -65.f).Length())));
	if(Camera::getCam().pos.x > 0.f){
		hutTextAngle = 360.f - hutTextAngle;
	}

	if(Application::IsKeyPressed('0') && hutTextFront.Length() <= 50.f){ //Change scene
		SceneManager::getScMan()->SetNextScene();
	}

	Mtx44 projection;
	projection.SetToPerspective(FOV, 4.f / 3.f, 0.1f, 1000.f); //FOV value affects cam zoom
	projectionStack.LoadMatrix(projection);
}

void MyScene::Render(double dt){ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(Camera::getCam().pos.x, Camera::getCam().pos.y, Camera::getCam().pos.z,
		Camera::getCam().target.x, Camera::getCam().target.y, Camera::getCam().target.z,
		Camera::getCam().up.x, Camera::getCam().up.y, Camera::getCam().up.z);
	modelStack.LoadIdentity();
	
	//Render smoke particles
	for(Particle* p: smokeEmitter.particlePool){
		if(p->life > 0.0f){
			delete meshList[unsigned int(MESH::SMOKE)];
			meshList[unsigned int(MESH::SMOKE)] = MeshBuilder::GenerateCuboid(p->color, .8f, .8f, .8f);
			modelStack.PushMatrix();
				modelStack.Translate(p->pos.x, p->pos.y, p->pos.z);
				RenderMesh(meshList[unsigned int(MESH::SMOKE)], 1);
			modelStack.PopMatrix();
		}
	}

	RenderLight();

	//Render Skybox
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 100.f, 0.f);
		modelStack.Translate(car.getPos().x, 0.f, car.getPos().z);
		modelStack.Scale(5.f, 5.f, 5.f);
		RenderSkybox();
	modelStack.PopMatrix();

	//Render Ground
	modelStack.PushMatrix();
		modelStack.Rotate(-90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(scaleFactor, scaleFactor, scaleFactor);
		RenderMesh(meshList[unsigned int(MESH::GROUND)], 1);
	modelStack.PopMatrix();

	//Render Boss
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 30.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		modelStack.Scale(1.5f, 1.5f, 1.5f);
		modelStack.PushMatrix();
			RenderMesh(meshList[unsigned int(MESH::BOSS_BODY)], 1);
			RenderMesh(meshList[unsigned int(MESH::BOSS_ARM_L)], 1);
			RenderMesh(meshList[unsigned int(MESH::BOSS_ARM_R)], 1);
			RenderMesh(meshList[unsigned int(MESH::BOSS_LEG_LF)], 1);
			RenderMesh(meshList[unsigned int(MESH::BOSS_LEG_RF)], 1);
			RenderMesh(meshList[unsigned int(MESH::BOSS_LEG_LB)], 1);
			RenderMesh(meshList[unsigned int(MESH::BOSS_LEG_RB)], 1);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Render Car
	modelStack.PushMatrix();
		modelStack.Translate(car.getPos().x, car.getPos().y, car.getPos().z);
		modelStack.Rotate(car.getBodyTurnAngle(), 0.f, 1.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
		RenderMesh(meshList[unsigned int(MESH::CAR_BODY)], 1);
		modelStack.PushMatrix();
			modelStack.Translate(0.f, 1.398f, 5.177f);
			modelStack.Rotate(car.getWheelTurnAngle(), 0.f, 1.f, 0.f);
			modelStack.Rotate(car.getWheelSpinAngle() * 2, 1.f, 0.f, 0.f);
			modelStack.Translate(0.f, -1.398f, -5.177f);
			RenderMesh(meshList[unsigned int(MESH::CAR_WHEEL_LF)], 1);
			RenderMesh(meshList[unsigned int(MESH::CAR_WHEEL_RF)], 1);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
			modelStack.Translate(0.f, 1.471f, -5.927f);
			modelStack.Rotate(car.getWheelSpinAngle() * 2, 1.f, 0.f, 0.f);
			modelStack.Translate(0.f, -1.471f, 5.927f);
			RenderMesh(meshList[unsigned int(MESH::CAR_WHEEL_LB)], 1);
			RenderMesh(meshList[unsigned int(MESH::CAR_WHEEL_RB)], 1);
		modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Render Turret and Bullets
	if(meshList[unsigned int(MESH::TURRET_TOP)]->textureID != 0){
		modelStack.PushMatrix();
			modelStack.Translate(turretPos.x, turretPos.y, turretPos.z);
			modelStack.Scale(.5f, .5f, .5f);
			modelStack.PushMatrix();
				modelStack.Translate((vibrate ? 0.1f : -0.1f), 0.f, (vibrate ? 0.4f : -0.4f));
				modelStack.Rotate(turretAngle, 0.f, 1.f, 0.f);
				RenderMesh(meshList[unsigned int(MESH::TURRET_TOP)], 1);
			modelStack.PopMatrix();
			RenderMesh(meshList[unsigned int(MESH::TURRET_BOTTOM)], 1);
		modelStack.PopMatrix();
		for(Particle* p : bulletGenerator.particlePool){
			if(p->life > 0.0f){
				delete meshList[unsigned int(MESH::BULLET)];
				meshList[unsigned int(MESH::BULLET)] = MeshBuilder::GenerateCuboid(p->color, .4f, .4f, .4f);
				modelStack.PushMatrix();
				modelStack.Translate(p->pos.x, p->pos.y, p->pos.z);
				RenderMesh(meshList[unsigned int(MESH::BULLET)], 1);
				modelStack.PopMatrix();
			}
		}
	}

	//Render Hut
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 65.f);
		modelStack.PushMatrix();
			modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
			RenderMesh(meshList[unsigned int(MESH::HUT)], 1);
		modelStack.PopMatrix();
		if(hutTextFront.Length() <= 50.f){
			modelStack.PushMatrix();
				modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
				modelStack.Rotate(hutTextAngle, 0.f, 1.f, 0.f);
				modelStack.Translate(-8.9f, 14.f, 0.f);
				RenderText(meshList[unsigned int(MESH::TEXT)], "Press '0' to enter", Color(1.f, 1.f, 0.f));
			modelStack.PopMatrix();
		}
	modelStack.PopMatrix();

	//Render generic objs
	modelStack.PushMatrix();
		modelStack.Translate(0.f, .3f, 72.f);
		modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
	RenderMesh(meshList[unsigned int(MESH::BASEBALL_BAT)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(20.f, 0.f, 10.f);
		modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
		RenderMesh(meshList[unsigned int(MESH::BENCH)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(20.f, 0.f, 30.f);
		modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
		RenderMesh(meshList[unsigned int(MESH::BENCH)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(20.f, 0.f, 50.f);
		modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
		RenderMesh(meshList[unsigned int(MESH::BENCH)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-20.f, 0.f, 10.f);
		modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
		RenderMesh(meshList[unsigned int(MESH::BENCH)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-20.f, 0.f, 30.f);
		modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
		RenderMesh(meshList[unsigned int(MESH::BENCH)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-20.f, 0.f, 50.f);
		modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
		RenderMesh(meshList[unsigned int(MESH::BENCH)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(6.5f, 0.f, 65.f);
		modelStack.Scale(.2f, .2f, .2f);
		RenderMesh(meshList[unsigned int(MESH::POT)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-9.7f, 0.f, 65.f);
		modelStack.Scale(.3f, .3f, .3f);
		RenderMesh(meshList[unsigned int(MESH::RECYCLING_BIN)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-6.3f, 1.4f, 65.f);
		modelStack.Scale(.3f, .3f, .3f);
		RenderMesh(meshList[unsigned int(MESH::TRASH)], 1);
	modelStack.PopMatrix();

	//Render Boss text
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 30.f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		modelStack.Scale(1.5f, 1.5f, 1.5f);
		modelStack.Rotate(bossTextAngle, 0.f, 1.f, 0.f);
		modelStack.Translate(-3.7f, 9.f, 0.f);
		RenderText(meshList[unsigned int(MESH::TEXT)], "Fight Me", Color(1.f, 0.f, 0.f));
	modelStack.PopMatrix();

	//Render on-screen text
	std::ostringstream ss;
	if(showDebugInfo){
		ss << std::fixed << std::setprecision(1);
		ss << "Car target: " << car.getTarget().x << ", " << car.getTarget().y << ", " << car.getTarget().z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.f, 1.f, 0.f), 2.f, .2f, 29.f);
		ss.str("");
		ss << "Car pos: " << car.getPos().x << ", " << car.getPos().y << ", " << car.getPos().z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.f, 1.f, 0.f), 2.f, .2f, 28.f);
		ss.str("");
		ss << std::setprecision(3);
		ss << "Elapsed: " << elapsedTime;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.f, 1.f, 0.f), 2.f, .2f, 1.f);
		ss.str("");
		ss << "FPS: " << 1.0 / dt;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(0.f, 1.f, 0.f), 2.f, .2f, 0.f);
		ss.str("");
	}
}

void MyScene::RenderLight(){
	if(light[0].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POSITION)], 1, &lightDirection_cameraspace.x);
	} else if(light[0].type == Light::LIGHT_TYPE::SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POSITION)], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_SPOTDIRECTION)], 1, &spotDirection_cameraspace.x);
	} else{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POSITION)], 1, &lightPosition_cameraspace.x);
	}
	if(light[1].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_POSITION)], 1, &lightDirection_cameraspace.x);
	} else if(light[1].type == Light::LIGHT_TYPE::SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_POSITION)], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_SPOTDIRECTION)], 1, &spotDirection_cameraspace.x);
	} else{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT1_POSITION)], 1, &lightPosition_cameraspace.x);
	}
	if(light[2].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[2].position.x, light[2].position.y, light[2].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_POSITION)], 1, &lightDirection_cameraspace.x);
	} else if(light[2].type == Light::LIGHT_TYPE::SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_POSITION)], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[2].spotDirection;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_SPOTDIRECTION)], 1, &spotDirection_cameraspace.x);
	} else{
		Position lightPosition_cameraspace = viewStack.Top() * light[2].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT2_POSITION)], 1, &lightPosition_cameraspace.x);
	}
	if(light[3].type == Light::LIGHT_TYPE::DIRECTIONAL){
		Vector3 lightDir(light[3].position.x, light[3].position.y, light[3].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_POSITION)], 1, &lightDirection_cameraspace.x);
	} else if(light[3].type == Light::LIGHT_TYPE::SPOT){
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_POSITION)], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[3].spotDirection;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_SPOTDIRECTION)], 1, &spotDirection_cameraspace.x);
	} else{
		Position lightPosition_cameraspace = viewStack.Top() * light[3].position;
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT3_POSITION)], 1, &lightPosition_cameraspace.x);
	}
	if(showLightSphere){
		modelStack.PushMatrix();
			modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
			modelStack.Scale(.8f, .8f, .8f);
			RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
			modelStack.Translate(light[1].position.x, light[1].position.y + 1.f, light[1].position.z);
			modelStack.Rotate(car.getBodyTurnAngle(), 0.f, 1.f, 0.f);
			modelStack.Scale(.2f, .2f, .2f);
			RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
			modelStack.Translate(light[2].position.x, light[2].position.y + 1.f, light[2].position.z);
			modelStack.Rotate(car.getBodyTurnAngle(), 0.f, 1.f, 0.f);
			modelStack.Scale(.2f, .2f, .2f);
			RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
			modelStack.Translate(light[3].position.x, light[3].position.y + 100.f, light[3].position.z);
			modelStack.Scale(30.f, 30.f, 30.f);
			RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
	}
}

void MyScene::RenderMesh(Mesh* mesh, bool enableLight){
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MVP)], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MODELVIEW)], 1, GL_FALSE, &modelView.a[0]);
	if(enableLight){
		glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHTENABLED)], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MODELVIEW_INVERSE_TRANSPOSE)], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//Load material
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_AMBIENT)], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_DIFFUSE)], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_SPECULAR)], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_MATERIAL_SHININESS)], mesh->material.kShininess);
	} else{
		glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHTENABLED)], 0);
	}
	if(mesh->textureID > 0){
		glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE_ENABLED)], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE)], 0);
	} else{ 
		glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE_ENABLED)], 0);
	} 
	mesh->Render(); //Shld only be called once in the whole function
}

void MyScene::RenderSkybox(){
	modelStack.PushMatrix();
		modelStack.Translate(-49.8f, 0.f, 0.f);
		modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::LEFT)], 0);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(49.8f, 0.f, 0.f);
		modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::RIGHT)], 0);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 49.8f, 0.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Rotate(270.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::TOP)], 0);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, -49.8f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::FRONT)], 0);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 49.8f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::BACK)], 0);
	modelStack.PopMatrix();
}

void MyScene::RenderText(Mesh* mesh, std::string text, Color color){
	if(!mesh || mesh->textureID < 0){
		return;
	}
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_ENABLED)], 1);
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_COLOR)], 1, &color.R);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHTENABLED)], 0);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE_ENABLED)], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE)], 0);
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MVP)], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_ENABLED)], 0);
	glEnable(GL_DEPTH_TEST);
}

void MyScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y){
	if(!mesh || mesh->textureID <= 0) //Proper error check return
		glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //Size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need cam for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_ENABLED)], 1);
	glUniform3fv(m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_COLOR)], 1, &color.R);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHTENABLED)], 0);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE_ENABLED)], 1);
	glActiveTexture(GL_TEXTURE0);
	if(mesh != 0){
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	}
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_COLOR_TEXTURE)], 0);
	for(unsigned i = 0; i < text.length(); ++i){
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.f, 0, 0); //1.f is spacing
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[unsigned int(UNIFORM_TYPE::U_MVP)], 1, GL_FALSE, &MVP.a[0]);
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_TEXT_ENABLED)], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
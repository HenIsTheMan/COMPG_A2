#include <iostream>
#include <iomanip>
#include <sstream>
#include "OtherScene.h"
#include "GL\glew.h"
#include "Application.h"
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "SceneManager.h"

extern double elapsedTime;

void OtherScene::InitLight(){
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
	light[0].type = Light::LIGHT_TYPE::DIRECTIONAL;
	light[0].power = 0.f;
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

	glUniform1i(m_parameters[unsigned int(UNIFORM_TYPE::U_NUMLIGHTS)], 1);
}

void OtherScene::InitMeshes(){
	//Init meshes of hut barriers
	meshList[unsigned int(MESH::LEFT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::LEFT)]->textureID = LoadTGA("image//Wood.tga");
	meshList[unsigned int(MESH::RIGHT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::RIGHT)]->textureID = LoadTGA("image//Wood.tga");
	meshList[unsigned int(MESH::FRONT)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::FRONT)]->textureID = LoadTGA("image//Wood.tga");
	meshList[unsigned int(MESH::BACK)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::BACK)]->textureID = LoadTGA("image//Wood.tga");
	meshList[unsigned int(MESH::TOP)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::TOP)]->textureID = LoadTGA("image//Wood.tga");
	meshList[unsigned int(MESH::BOTTOM)] = MeshBuilder::GenerateQuad(Color(1.f, 1.f, 1.f), 1.f, 1.f);
	meshList[unsigned int(MESH::BOTTOM)]->textureID = LoadTGA("image//Wood.tga");

	//Init generic obj meshes
	meshList[unsigned int(MESH::BED)] = MeshBuilder::GenerateOBJ("OBJ//Bed.obj");
	meshList[unsigned int(MESH::BED)]->textureID = LoadTGA("image//Bed.tga");
	meshList[unsigned int(MESH::CEILING_LIGHT)] = MeshBuilder::GenerateOBJ("OBJ//CeilingLight.obj");
	meshList[unsigned int(MESH::CEILING_LIGHT)]->textureID = LoadTGA("image//CeilingLight.tga");
	meshList[unsigned int(MESH::CHAIR)] = MeshBuilder::GenerateOBJ("OBJ//Chair.obj");
	meshList[unsigned int(MESH::CHAIR)]->textureID = LoadTGA("image//Chair.tga");
	meshList[unsigned int(MESH::DART)] = MeshBuilder::GenerateOBJ("OBJ//Dart.obj");
	meshList[unsigned int(MESH::DART)]->textureID = LoadTGA("image//Dart.tga");
	meshList[unsigned int(MESH::DARTBOARD)] = MeshBuilder::GenerateOBJ("OBJ//Dartboard.obj");
	meshList[unsigned int(MESH::DARTBOARD)]->textureID = LoadTGA("image//Dartboard.tga");
	meshList[unsigned int(MESH::DIE)] = MeshBuilder::GenerateOBJ("OBJ//Die.obj");
	meshList[unsigned int(MESH::DIE)]->textureID = LoadTGA("image//Die.tga");
	meshList[unsigned int(MESH::SHOE)] = MeshBuilder::GenerateOBJ("OBJ//Shoe.obj");
	meshList[unsigned int(MESH::SHOE)]->textureID = LoadTGA("image//Shoe.tga");
	meshList[unsigned int(MESH::MAIN_TABLE)] = MeshBuilder::GenerateOBJ("OBJ//MainTable.obj");
	meshList[unsigned int(MESH::MAIN_TABLE)]->textureID = LoadTGA("image//MainTable.tga");
	meshList[unsigned int(MESH::SIDE_TABLE)] = MeshBuilder::GenerateOBJ("OBJ//SideTable.obj");
	meshList[unsigned int(MESH::SIDE_TABLE)]->textureID = LoadTGA("image//SideTable.tga");
	meshList[unsigned int(MESH::WINE_BOTTLE)] = MeshBuilder::GenerateOBJ("OBJ//WineBottle.obj");
	meshList[unsigned int(MESH::WINE_BOTTLE)]->textureID = LoadTGA("image//WineBottle.tga");

	//Init other meshes
	meshList[unsigned int(MESH::LIGHT_SPHERE)] = MeshBuilder::GenerateSphere(Color(1.f, 1.f, 1.f), 20, 20, 1.f);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)] = MeshBuilder::GenerateText(16, 16);
	meshList[unsigned int(MESH::TEXT_ON_SCREEN)]->textureID = LoadTGA("image//FontOnScreen.tga");
}

void OtherScene::Init(){ //Init scene
	glGenVertexArrays(1, &m_vertexArrayID); //Generate a default VAO
	glBindVertexArray(m_vertexArrayID);
	glEnable(GL_CULL_FACE); //Enable back-face culling
	glEnable(GL_BLEND); //Enable blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST); //Enable depth test
	m_programID = LoadShaders("Shader//vShader.vertexshader", "Shader//fShader.fragmentshader"); //Load shaders
	glUseProgram(m_programID);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	Camera::getCam().Init(Vector3(0.f, 5.f, -30.f), Vector3(0.f, 5.f, 0.f), Vector3(0.f, 1.f, 0.f));
	InitLight();
	InitMeshes();
	showDebugInfo = 1;
	showLightSphere = 0;
	debugBounceTime = lightBounceTime = 0.0;
}

void OtherScene::Exit(Scene* newScene){ //Exit scene
	for(int i = 0; i < int(MESH::NUM_GEOMETRY); ++i){
		if(meshList[i] != 0){
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
	if(dynamic_cast<OtherScene*>(newScene) != this){
		newScene->Init();
	}
}

void OtherScene::Update(double dt, float FOV){ //Update scene
	for(int i = 0; i < 7; ++i){
		if(Application::IsKeyPressed(keys[i])){
			switch(keys[i]){
				case '1': glDisable(GL_CULL_FACE); break; //Disable back-face culling
				case '2': glEnable(GL_CULL_FACE); break; //Enable back-face culling
				case '3': glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break; //Set polygon mode to GL_FILL (default mode)
				case '4': glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break; //Set polygon mode to GL_LINE (wireframe mode)
				case '8': { //Off the light
					light[0].power = 0.f;
					glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POWER)], light[0].power);
					break;
				}
				case '9': { //On the light
					light[0].power = 1.f;
					glUniform1f(m_parameters[unsigned int(UNIFORM_TYPE::U_LIGHT0_POWER)], light[0].power);
					break;
				}
				case '0': SceneManager::getScMan()->SetNextScene(); //Change scene
			}
		}
	}
	if(Application::IsKeyPressed('P') && lightBounceTime <= elapsedTime){ //Show/Hide light sphere
		showLightSphere = !showLightSphere;
		lightBounceTime = elapsedTime + 0.4;
	}
	if(Application::IsKeyPressed(VK_SHIFT) && debugBounceTime <= elapsedTime){ //Show/Hide debug info
		showDebugInfo = !showDebugInfo;
		debugBounceTime = elapsedTime + 0.5;
	}
	Mtx44 projection;
	projection.SetToPerspective(FOV, 4.f / 3.f, 0.1f, 1000.f); //FOV value affects cam zoom
	projectionStack.LoadMatrix(projection);
}

void OtherScene::Render(double dt){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewStack.LoadIdentity();
	viewStack.LookAt(Camera::getCam().pos.x, Camera::getCam().pos.y, Camera::getCam().pos.z,
		Camera::getCam().target.x, Camera::getCam().target.y, Camera::getCam().target.z,
		Camera::getCam().up.x, Camera::getCam().up.y, Camera::getCam().up.z);
	modelStack.LoadIdentity();

	RenderLight();

	//Render generic objs
	modelStack.PushMatrix();
		modelStack.Translate(-60.f, 2.f, -20.f);
		modelStack.Rotate(-90.f, 1.f, 0.f, 0.f);
		modelStack.Scale(.5f, .5f, .5f);
	RenderMesh(meshList[unsigned int(MESH::BED)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 188.4f, 0.f);
		modelStack.Scale(2.f, 2.f, 2.f);
		RenderMesh(meshList[unsigned int(MESH::CEILING_LIGHT)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(30.f, 28.7f, 0.f);
		modelStack.Scale(3.f, 3.f, 3.f);
		RenderMesh(meshList[unsigned int(MESH::CHAIR)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-94.f, 115.25f, -.45f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		modelStack.Scale(3.f, 3.f, 3.f);
		RenderMesh(meshList[unsigned int(MESH::DART)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-93.9f, 100.f, 0.f);
		modelStack.Scale(1.5f, 5.5f, 5.5f);
		RenderMesh(meshList[unsigned int(MESH::DARTBOARD)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(6.f, 36.2f, 3.1f);
		modelStack.Rotate(45.f, 0.f, 1.f, 0.f);
		modelStack.Scale(6.5f, 6.5f, 6.5f);
		RenderMesh(meshList[unsigned int(MESH::DIE)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(9.f, 1.f, 5.f);
		modelStack.Scale(3.f, 3.f, 3.f);
		RenderMesh(meshList[unsigned int(MESH::MAIN_TABLE)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(-60.5f, 0.f, 64.f);
		modelStack.Scale(70.f, 70.f, 70.f);
		RenderMesh(meshList[unsigned int(MESH::SIDE_TABLE)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 1.2f, 0.f);
		modelStack.Scale(5.f, 5.f, 5.f);
		RenderMesh(meshList[unsigned int(MESH::SHOE)], 1);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(12.f, 29.f, -3.1f);
		modelStack.Rotate(-175.f, 0.f, 1.f, 0.f);
		modelStack.Scale(5.f, 5.f, 5.f);
		RenderMesh(meshList[unsigned int(MESH::WINE_BOTTLE)], 1);
	modelStack.PopMatrix();

	//Render hut barriers
	modelStack.PushMatrix();
		modelStack.Translate(0.f, 100.f, 0.f);
		modelStack.Scale(2.f, 2.f, 2.f);
		RenderHutBarriers(!light[0].power);
	modelStack.PopMatrix();

	//Render Text
	std::ostringstream ss;
	if(showDebugInfo){
		ss << std::fixed << std::setprecision(2);
		ss << "Cam target: " << Camera::getCam().target.x << ", " << Camera::getCam().target.y << ", " << Camera::getCam().target.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 2.f, .2f, 29.f);
		ss.str("");
		ss << "Cam pos: " << Camera::getCam().pos.x << ", " << Camera::getCam().pos.y << ", " << Camera::getCam().pos.z;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 2.f, .2f, 28.f);
		ss.str("");
		ss << std::setprecision(3);
		ss << "Elapsed: " << elapsedTime;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 2.f, .2f, 1.f);
		ss.str("");
		ss << "FPS: " << 1.0 / dt;
		RenderTextOnScreen(meshList[unsigned int(MESH::TEXT_ON_SCREEN)], ss.str(), Color(1.f, .5f, .6f), 2.f, .2f, 0.f);
		ss.str("");
	}
}

void OtherScene::RenderLight(){
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
	if(showLightSphere){
		modelStack.PushMatrix();
			modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
			modelStack.Scale(2.f, 2.f, 2.f);
			RenderMesh(meshList[unsigned int(MESH::LIGHT_SPHERE)], 0);
		modelStack.PopMatrix();
	}
}

void OtherScene::RenderMesh(Mesh* mesh, bool enableLight){
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

void OtherScene::RenderHutBarriers(bool lightSwitch){
	modelStack.PushMatrix();
		modelStack.Translate(-49.8f, 0.f, 0.f);
		modelStack.Rotate(90.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::LEFT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(49.8f, 0.f, 0.f);
		modelStack.Rotate(-90.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::RIGHT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, -49.8f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::FRONT)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 49.8f);
		modelStack.Rotate(180.f, 0.f, 1.f, 0.f);
		modelStack.Rotate(180.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::BACK)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, 49.8f, 0.f);
		modelStack.Rotate(90.f, 1.f, 0.f, 0.f);
		modelStack.Rotate(270.f, 0.f, 0.f, 1.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		RenderMesh(meshList[unsigned int(MESH::TOP)], lightSwitch);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0.f, -49.8f, 0.f);
		modelStack.Scale(100.f, 100.f, 100.f);
		modelStack.Rotate(-90.f, 1.f, 0.f, 0.f);
		modelStack.PushMatrix();
			modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
			RenderMesh(meshList[unsigned int(MESH::BOTTOM)], lightSwitch);
		modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void OtherScene::RenderText(Mesh* mesh, std::string text, Color color){
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

void OtherScene::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y){
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
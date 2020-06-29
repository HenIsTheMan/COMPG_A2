#include "MyScene.h"
#include "SceneManager.h"

extern bool hideCursor;
extern const unsigned int frameTime;
extern double elapsedTime;
extern float FOV;

SceneManager::SceneManager(): currSceneID(0), nextSceneID(0), screenBounceTime(0.0), switchBounceTime(0.0){}

SceneManager::~SceneManager(){
	scStorage[currSceneID]->Exit(scStorage[currSceneID]);
	for(size_t i = 0; i < scStorage.size(); ++i){
		delete scStorage[i];
	}
}

SceneManager* SceneManager::scMan = 0;

SceneManager* SceneManager::getScMan(){
	if(!scMan){
		scMan = new SceneManager;
	}
	return scMan;
}

void SceneManager::AddScene(Scene* newScene){
	scStorage.emplace_back(newScene);
	if(scStorage.size() == 1){
		scStorage[currSceneID]->Init();
	} else{
		SceneManager::getScMan()->SetNextSceneID(scStorage.size() - 1);
	}
}

void SceneManager::SetNextScene(){
	if(scStorage.size() > 1){
		scStorage[currSceneID]->Exit(scStorage[nextSceneID]);
	}
	currSceneID = nextSceneID;
	if(++nextSceneID == scStorage.size()){
		nextSceneID = 0;
	}
}

void SceneManager::SetNextSceneID(int newID){
	nextSceneID = newID;
}

void SceneManager::Update(Application& app, GLFWwindow* m_window){ //Update current scene
	double dt = app.m_timer.getElapsedTime();
	elapsedTime += dt;
	if(Application::IsKeyPressed('C') && switchBounceTime <= elapsedTime){
		hideCursor = !hideCursor;
		if(hideCursor){
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Hide window cursor
		} else{
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); //Show window cursor
		}
		switchBounceTime = elapsedTime + 0.5;
	}
	if(Application::IsKeyPressed('F') && screenBounceTime <= elapsedTime){ //Toggle fullscreen
		if(app.fullscreen){
			glfwSetWindowMonitor(m_window, 0, int(app.mode->width / 4), int(app.mode->height / 30), int(app.mode->width * 2 / 3), int(app.mode->width * 2 / 3) * 3 / 4, GLFW_DONT_CARE);
		} else{
			glfwSetWindowMonitor(m_window, glfwGetPrimaryMonitor(), 0, 0, int(app.mode->width), int(app.mode->height), GLFW_DONT_CARE);
		}
		app.fullscreen = !app.fullscreen;
		screenBounceTime = elapsedTime + 0.5;
	}
	if(Application::IsKeyPressed(VK_END)){ //Reset scene
		Camera::getCam().pos = Camera::getCam().defaultPos;
		Camera::getCam().target = Camera::getCam().defaultTarget;
		Camera::getCam().up = Camera::getCam().defaultUp;
		FOV = 45.f;
		((MyScene*)scStorage[currSceneID])->getCarRef().setPos(Vector3(0.f, 0.f, 0.f));
		((MyScene*)scStorage[currSceneID])->getCarRef().setTarget(Vector3(0.f, 0.f, 1.f));
		((MyScene*)scStorage[currSceneID])->getCarRef().resetAngles();
		((MyScene*)scStorage[currSceneID])->getLight0Ref() = Light();
		((MyScene*)scStorage[currSceneID])->getLight1Ref() = Light(-1.4f, .2f, 4.2f, Vector3(0.f, 0.f, -1.f));
		((MyScene*)scStorage[currSceneID])->getLight2Ref() = Light(1.4f, .2f, 4.2f, Vector3(0.f, 0.f, -1.f));
	}
	Camera::getCam().Update(dynamic_cast<MyScene*>(scStorage[currSceneID]), static_cast<MyScene*>(scStorage[currSceneID])->getCar(), dt);
	scStorage[currSceneID]->Update(dt, FOV);
	scStorage[currSceneID]->Render(dt);
	glfwSwapBuffers(m_window);
	glfwPollEvents(); //Get and organize events like kb and mouse input, window resizing, etc.
	app.m_timer.waitUntil(frameTime); //Limits each frame to a specified time in ms
}
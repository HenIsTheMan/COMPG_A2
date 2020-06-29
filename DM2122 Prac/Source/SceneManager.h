#pragma once
#include "Application.h"
#include "Scene.h"
#include <vector>

class SceneManager{ //Singleton
	SceneManager();
	SceneManager(const SceneManager&); //Private copy ctor
	SceneManager(SceneManager&&); //Private move ctor
	SceneManager& operator=(const SceneManager&){}; //Private copy assignment operator
	SceneManager& operator=(SceneManager&&) noexcept{}; //Private move assignment operator
	double screenBounceTime, switchBounceTime;
	int currSceneID, nextSceneID;
	static SceneManager* scMan;
	std::vector<Scene*> scStorage;
public:
	~SceneManager();
	static SceneManager* getScMan();
	void AddScene(Scene*), SetNextScene(), SetNextSceneID(int), Update(Application&, GLFWwindow*);
};
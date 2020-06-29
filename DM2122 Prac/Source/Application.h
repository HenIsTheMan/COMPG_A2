#pragma once
#include <GLFW/glfw3.h>
#include "timer.h"

class Application{ //Singleton
	Application();
	static Application* app;
	void Run();
public:
	Application(Application const&) = delete; //Delete copy ctor
	Application(Application&&) = delete; //Delete move ctor
	Application& operator=(Application const&) = delete; //Delete copy assignment operator
	Application& operator=(Application&&) = delete; //Delete move assignment operator
	~Application();
	static Application* getApp();
	static bool IsKeyPressed(unsigned short);
	static void IRun();
	bool fullscreen;
	const GLFWvidmode* mode;
	StopWatch m_timer;
};
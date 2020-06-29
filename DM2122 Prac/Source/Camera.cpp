#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"

double modeBounceTime = 0.0;
extern double elapsedTime = 0.0;
extern float FOV;

Camera& Camera::getCam(){ //Static getter for Singleton
	static Camera cam;
	return cam;
}

Camera::Camera(): focusSpd(100.f), freeSpd(50.f){ //Default ctor
	mode = MODE::FOCUS;
	leftMouse = rightMouse = 0;
}

void Camera::Init(const Vector3 &pos, const Vector3 &target, const Vector3 &up){ //Init cam
	this->pos = defaultPos = pos;
	this->target = defaultTarget = target;
	this->up = defaultUp = up;
}

void Camera::Update(bool isMyScene, Car car, double dt){ //Update cam
	if(Application::IsKeyPressed('B') && modeBounceTime <= elapsedTime){ //Change cam mode
		mode = MODE(!bool(mode));
		Vector3 dir = target - pos, front = dir.Normalized(), right = front.Cross(up).Normalized();
		right.y = 0;
		if(mode == MODE::FOCUS){
			if(isMyScene){
				target = car.getPos();
			} else{
				target = Vector3(0.f, 0.f, 0.f);
				pos = Vector3(0.f, 5.f, -30.f);
			}
			front = target - pos;
			front.y = 0;
			right = front.Cross(up);
			right.y = 0;
			up = right.Cross(front).Normalized();
		}
		modeBounceTime = elapsedTime + 0.2;
	}

	if(isMyScene && mode == MODE::FOCUS && (Application::IsKeyPressed(VK_UP) - Application::IsKeyPressed(VK_DOWN))){ //Make cam follow car
		Vector3 dir = target - pos, front = dir.Normalized(), right = front.Cross(up).Normalized();
		right.y = 0;
		target = car.getPos();
		Vector3 carFront = (car.getTarget() - car.getPos()).Normalized();
		carFront.y = 0;
		pos += float(Application::IsKeyPressed(VK_UP) - Application::IsKeyPressed(VK_DOWN)) * car.getSpeed() * carFront;
	}

	if(Application::IsKeyPressed('A') - Application::IsKeyPressed('D')){ //Move cam left or right
		Vector3 dir = target - pos, front = dir.Normalized(), right = front.Cross(up).Normalized();
		right.y = 0;
		if(mode == MODE::FOCUS){
			float yaw = float(float(Application::IsKeyPressed('A') - Application::IsKeyPressed('D')) * -focusSpd * dt);
			Mtx44 rotation;
			rotation.SetToRotation(yaw, 0, 1, 0);
			front = rotation * (target - pos);
			pos = target - front;
			right = front.Cross(up);
			right.y = 0;
			up = right.Cross(front).Normalized();
		} else if(mode == MODE::FREE){
			pos += float(Application::IsKeyPressed('A') - Application::IsKeyPressed('D')) * float(-freeSpd * dt) * right;
			target += float(Application::IsKeyPressed('A') - Application::IsKeyPressed('D')) * float(-freeSpd * dt) * right;
		}
	}

	if(Application::IsKeyPressed('Q') - Application::IsKeyPressed('E')){ //Move cam up or down
		Vector3 dir = target - pos, front = dir.Normalized(), right = front.Cross(up).Normalized();
		right.y = 0;
		if(mode == MODE::FOCUS){
			float pitch = -float(float(Application::IsKeyPressed('Q') - Application::IsKeyPressed('E')) * focusSpd * dt);
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			front = rotation * (target - pos);
			pos = target - front;
			right = front.Cross(up);
			right.y = 0;
			up = right.Cross(front).Normalized();
		} else if(mode == MODE::FREE){
			pos += float(Application::IsKeyPressed('Q') - Application::IsKeyPressed('E')) * float(freeSpd * dt) * up;
			target += float(Application::IsKeyPressed('Q') - Application::IsKeyPressed('E')) * float(freeSpd * dt) * up;
		}
	}

	if(Application::IsKeyPressed('W') || (leftMouse && !rightMouse)){ //Move cam forward or towards the target
		Vector3 dir = target - pos, front = dir.Normalized(), right = front.Cross(up).Normalized();
		right.y = 0;
		if(mode == MODE::FOCUS){
			pos += front * float(focusSpd / 2 * dt) * (dir.Length() > 12);
		} else{
			if(Application::IsKeyPressed('W')){
				front.y = 0;
			}
			pos += float(freeSpd * dt) * front;
			target += float(freeSpd * dt) * front;
		}
	}
	if(Application::IsKeyPressed('S') || (rightMouse && !leftMouse)){ //Move cam backward or away from the target
		Vector3 dir = target - pos, front = dir.Normalized(), right = front.Cross(up).Normalized();
		right.y = 0;
		if(mode == MODE::FOCUS){
			pos += front * float(-focusSpd / 2 * dt) * (dir.Length() < 200);
		} else{
			if(Application::IsKeyPressed('S')){
				front.y = 0;
			}
			pos += float(-freeSpd * dt) * front;
			target += float(-freeSpd * dt) * front;
		}
	}
}

void Camera::UpdateCamVectors(float yaw, float pitch){ //For cam to respond to mouse movement
	Vector3 front = (target - pos).Normalized(), right = front.Cross(up).Normalized();
	right.y = 0;
	Mtx44 r1, r2;
	r1.SetToRotation(-yaw, 0, 1, 0);
	r2.SetToRotation(-pitch, right.x, right.y, right.z);
	if(mode == MODE::FOCUS){
		front = r1 * r2 * (target - pos);
		pos = target - front;
		right = front.Cross(up);
		right.y = 0;
		up = right.Cross(front).Normalized();
	} else if(mode == MODE::FREE){
		front = r1 * r2 * front;
		target = pos + front;
	}
	up = right.Cross(front).Normalized();
}
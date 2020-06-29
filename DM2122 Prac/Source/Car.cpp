#include "Car.h"

Car::Car(): pos(0.f, 0.f, 0.f), target(0.f, 0.f, 1.f){
	jumping = keyReleased = 0;
	speed = wheelSpinAngle = bodyTurnAngle = wheelTurnAngle = jumpHeight = 0.f;
	grav = .1f;
	maxJump = 2;
}

bool Car::isJumping() const{
	return jumping;
}

bool Car::isKeyReleased() const{
	return keyReleased;
}

float Car::getSpeed() const{
	return speed;
}

float Car::getWheelSpinAngle() const{
	return wheelSpinAngle;
}

float Car::getBodyTurnAngle() const{
	return bodyTurnAngle;
}

float Car::getWheelTurnAngle() const{
	return wheelTurnAngle;
}

float Car::getGrav() const{
	return grav;
}

float Car::getJumpHeight() const{
	return jumpHeight;
}

int Car::getMaxJump() const{
	return maxJump;
}

Vector3 Car::getPos() const{
	return pos;
}

Vector3 Car::getTarget() const{
	return target;
}

void::Car::reduceMaxJump(){
	--maxJump;
}

void Car::resetAngles(){
	speed = wheelSpinAngle = bodyTurnAngle = wheelTurnAngle = 0.f;
}

void Car::setSpeed(float newSpeed){
	speed = newSpeed;
}

void Car::setWheelSpinAngle(float newAngle){
	wheelSpinAngle = newAngle;
}

void Car::setBodyTurnAngle(float newAngle){
	bodyTurnAngle = newAngle;
}

void Car::setWheelTurnAngle(float newAngle){
	wheelTurnAngle = newAngle;
}

void Car::setPos(Vector3 newPos){
	pos = newPos;
}

void Car::setTarget(Vector3 newTarget){
	target = newTarget;
}

void Car::setJumpHeight(float newHeight){
	jumpHeight = newHeight;
}

void Car::setJumping(bool newJumpState){
	jumping = newJumpState;
}

void Car::setKeyReleased(bool newReleaseState){
	keyReleased = newReleaseState;
}

void Car::setMaxJump(int newMaxJump){
	maxJump = newMaxJump;
}
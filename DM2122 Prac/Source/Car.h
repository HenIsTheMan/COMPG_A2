#pragma once
#include "Vector3.h"

class Car{
	bool jumping, keyReleased;
	float speed, wheelSpinAngle, bodyTurnAngle, wheelTurnAngle, grav, jumpHeight;
	int maxJump;
	Vector3 pos, target;
public:
	Car();
	bool isJumping() const, isKeyReleased() const;
	float getSpeed() const, getWheelSpinAngle() const, getBodyTurnAngle() const, getWheelTurnAngle() const, getGrav() const, getJumpHeight() const;
	int getMaxJump() const;
	Vector3 getPos() const, getTarget() const;
	void reduceMaxJump(), resetAngles(), setSpeed(float), setWheelSpinAngle(float), setBodyTurnAngle(float), setWheelTurnAngle(float), setPos(Vector3), setTarget(Vector3),
		setJumpHeight(float), setJumping(bool), setKeyReleased(bool), setMaxJump(int);
};
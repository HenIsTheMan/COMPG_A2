#pragma once
#include "Vertex.h"

struct Light{
	Light(float x = 0.f, float y = 8.f, float z = 0.f, Vector3 spotDir = Vector3(0.f, 1.f, 0.f)){
		type = LIGHT_TYPE::SPOT;
		position.Set(x, y, z);
		color.Set(1.f, 1.f, 1.f);
		power = 1.f;
		kC = 1.f;
		kL = .01f;
		kQ = .001f;
		cosCutoff = cos(Math::DegreeToRadian(45.f));
		cosInner = cos(Math::DegreeToRadian(30.f));
		exponent = 32.f;
		spotDirection.Set(spotDir.x, spotDir.y, spotDir.z);
	}
	enum class LIGHT_TYPE{
		POINT, DIRECTIONAL, SPOT
	};
	Color color;
	float power, kC, kL, kQ, cosCutoff, cosInner, exponent;
	LIGHT_TYPE type;
	Position position;
	Vector3 spotDirection;
};
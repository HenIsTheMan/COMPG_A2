#pragma once
#include "Vector3.h"

struct Color{
	float R, G, B;
	Color(float R = 1, float G = 1, float B = 1){
		Set(R, G, B);
	}
	void Set(float R, float G, float B){
		this->R = R; this->G = G; this->B = B;
	}
};

struct Position{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0){
		Set(x, y, z);
	}
	void Set(float x, float y, float z){
		this->x = x; this->y = y; this->z = z;
	}
};

struct TexCoord{
	float U, V;
	TexCoord(float U = 0, float V = 0){
		Set(U, V);
	}
	void Set(float U, float V){
		this->U = U; this->V = V;
	}
};

struct Vertex{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
};
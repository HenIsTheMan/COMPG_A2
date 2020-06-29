#pragma once
#include "Vertex.h"
#include "Material.h"

class Mesh{ //To store Vertex Buffer Obj (VBO, for vertices and colors) and Index Buffer Obj (IBO)
public:
	enum class DRAW_MODE{
		DRAW_TRIANGLES, DRAW_TRIANGLE_STRIP, DRAW_LINES, DRAW_FAN, DRAW_MODE_LAST
	};
	Mesh(), ~Mesh();
	void Render(), Render(unsigned, unsigned);
	DRAW_MODE mode;
	unsigned vertexBuffer, colorBuffer, indexBuffer, textureID;
	Material material;
};
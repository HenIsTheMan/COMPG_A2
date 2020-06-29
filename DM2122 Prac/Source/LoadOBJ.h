#pragma once
#include <vector>
#include "Vertex.h"

bool LoadOBJ(const char*, std::vector<Position>&, std::vector<TexCoord>&, std::vector<Vector3>&);
void IndexVBO(std::vector<Position>&, std::vector<TexCoord>&, std::vector<Vector3>&, std::vector<unsigned>&, std::vector<Vertex>&);
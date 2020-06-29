#include <iostream>
#include <fstream>
#include <map>
#include "LoadOBJ.h"

bool LoadOBJ(const char* filePath, std::vector<Position>& outVertices, std::vector<TexCoord>& outUVs, std::vector<Vector3>& outNormals){
	std::ifstream fileStream(filePath, std::ios::binary);
	if(!fileStream.is_open()){
		std::cout << "Unable to open \"" << filePath << "\".\n";
		return 0;
	}
	std::vector<unsigned> vertexIndices, UVIndices, normalIndices;
	std::vector<Position> tempVertices;
	std::vector<TexCoord> tempUVs;
	std::vector<Vector3> tempNormals;
	while(!fileStream.eof()){
		char buf[256];
		fileStream.getline(buf, 256);
		if(strncmp("v ", buf, 2) == 0){
			Position vertex;
			sscanf_s(buf + 2, "%f%f%f", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		} else if(strncmp("vt ", buf, 3) == 0){
			TexCoord tc;
			sscanf_s(buf + 2, "%f%f", &tc.U, &tc.V);
			tempUVs.push_back(tc);
		} else if(strncmp("vn ", buf, 3) == 0){
			Vector3 normal;
			sscanf_s(buf + 2, "%f%f%f", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		} else if(strncmp("f ", buf, 2) == 0){
			unsigned int vertexIndex[4], UVIndex[4], normalIndex[4];
			int matches = sscanf_s(buf + 2, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", 
				&vertexIndex[0], &UVIndex[0], &normalIndex[0],
				&vertexIndex[1], &UVIndex[1], &normalIndex[1],
				&vertexIndex[2], &UVIndex[2], &normalIndex[2],
				&vertexIndex[3], &UVIndex[3], &normalIndex[3]);
			if(matches == 9){ //Triangle
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				UVIndices.push_back(UVIndex[0]);
				UVIndices.push_back(UVIndex[1]);
				UVIndices.push_back(UVIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			} else if(matches == 12){ //Quad
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				UVIndices.push_back(UVIndex[0]);
				UVIndices.push_back(UVIndex[1]);
				UVIndices.push_back(UVIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);

				vertexIndices.push_back(vertexIndex[2]);
				vertexIndices.push_back(vertexIndex[3]);
				vertexIndices.push_back(vertexIndex[0]);
				UVIndices.push_back(UVIndex[2]);
				UVIndices.push_back(UVIndex[3]);
				UVIndices.push_back(UVIndex[0]);
				normalIndices.push_back(normalIndex[2]);
				normalIndices.push_back(normalIndex[3]);
				normalIndices.push_back(normalIndex[0]);
			} else{ //Cater for vertices without UV texture
				matches = sscanf_s(buf + 2, "%d//%d %d//%d %d//%d %d//%d\n",
					&vertexIndex[0], &normalIndex[0],
					&vertexIndex[1], &normalIndex[1],
					&vertexIndex[2], &normalIndex[2],
					&vertexIndex[3], &normalIndex[3]);
				if(matches == 6){ //Triangle
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					UVIndices.push_back(0);
					UVIndices.push_back(0);
					UVIndices.push_back(0);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				} else if(matches == 8){ //Quad
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					UVIndices.push_back(0);
					UVIndices.push_back(0);
					UVIndices.push_back(0);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);

					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
					vertexIndices.push_back(vertexIndex[0]);
					UVIndices.push_back(0);
					UVIndices.push_back(0);
					UVIndices.push_back(0);
					normalIndices.push_back(normalIndex[2]);
					normalIndices.push_back(normalIndex[3]);
					normalIndices.push_back(normalIndex[0]);
				} else{
					std::cout << "Error line: " << buf << std::endl;
					std::cout << "File can't be read by parser!\n";
					return 0;
				}
			}
		}
	}
	fileStream.close();
	for(unsigned i = 0; i < vertexIndices.size(); ++i){ //For each vertex of each triangle
		//Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int UVIndex = UVIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		//Get the attributes thanks to the index
		Position vertex = tempVertices[vertexIndex - 1];
		TexCoord UV;
		if(UVIndex > 0){
			UV = tempUVs[UVIndex - 1];
		}
		Vector3 normal = tempNormals[normalIndex - 1];
		
		//Put the attributes in buffers
		outVertices.push_back(vertex);
		outUVs.push_back(UV);
		outNormals.push_back(normal);
	}
	return 1;
}

struct PackedVertex{
	Position position;
	TexCoord UV;
	Vector3 normal;
	bool operator<(const PackedVertex that) const{
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

bool getSimilarVertexIndex_fast(PackedVertex& packed, std::map<PackedVertex, unsigned short>& VertexToOutIndex, unsigned short& result){
	std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
	if(it == VertexToOutIndex.end()){
		return 0;
	}
	result = it->second;
	return 1;
}

void IndexVBO(std::vector<Position>& inVertices, std::vector<TexCoord>& inUVs, std::vector<Vector3>& inNormals, std::vector<unsigned>& outIndices, std::vector<Vertex>& outVertices){
	std::map<PackedVertex,unsigned short> VertexToOutIndex;
	for(unsigned int i = 0; i < inVertices.size(); ++i){ //For each input vertex
		PackedVertex packed = {inVertices[i], inUVs[i], inNormals[i]};

		//Try to find a similar vertex in outXXXXX
		unsigned short index;
		if(getSimilarVertexIndex_fast(packed, VertexToOutIndex, index)){ 
			outIndices.push_back(index); //A similar vertex is alr in the VBO so use it instead
		} else{ //If not, it needs to be added in the output data
			Vertex v;
			v.pos.Set(inVertices[i].x, inVertices[i].y, inVertices[i].z);
			v.texCoord.Set(inUVs[i].U, inUVs[i].V);
			v.normal.Set(inNormals[i].x, inNormals[i].y, inNormals[i].z);
			v.color.Set(1, 1, 1);
			outVertices.push_back(v);
			unsigned newindex = unsigned(outVertices.size()) - 1;
			outIndices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}
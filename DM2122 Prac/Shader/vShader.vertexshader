#version 330 core

//Input vertex data (diff for all executions of this shader)
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal_modelspace;
layout(location = 3) in vec2 vertexTexCoord;

//Output data (will be interpolated for each fragment)
out vec2 texCoord;
out vec3 vertexPosition_cameraspace, fragmentColor, vertexNormal_cameraspace;

//Values that stay constant for the whole mesh
uniform bool lightEnabled;
uniform mat4 MVP, MV, MV_inverse_transpose;

void main(){
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1); //Output pos of vertex in clip space (MVP * pos)
	vertexPosition_cameraspace = (MV * vec4(vertexPosition_modelspace, 1)).xyz; //Vector pos in cam space
	if(lightEnabled){
		vertexNormal_cameraspace = (MV_inverse_transpose * vec4(vertexNormal_modelspace, 0)).xyz; //Vertex normal in cam space, use MV if ModelMatrix does not scale the model
	}
	fragmentColor = vertexColor; //Color of each vertex will be interpolated to produce color of each fragment
	texCoord = vertexTexCoord; 	//TexCoord of each fragment will be interpolated from texCoord of each vertex
}
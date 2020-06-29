#pragma once
#include <MatrixStack.h>
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"

class OtherScene: public Scene{
	enum class MESH{
		LEFT, RIGHT, FRONT, BACK, TOP, BOTTOM, LIGHT_SPHERE, TEXT_ON_SCREEN, BED, CEILING_LIGHT, CHAIR, DART, DARTBOARD, DIE, MAIN_TABLE, SIDE_TABLE, SHOE, WINE_BOTTLE, NUM_GEOMETRY
	};
	enum class UNIFORM_TYPE{
		U_MVP, U_MODELVIEW, U_MODELVIEW_INVERSE_TRANSPOSE, U_MATERIAL_AMBIENT, U_MATERIAL_DIFFUSE, U_MATERIAL_SPECULAR, U_MATERIAL_SHININESS, U_LIGHTENABLED,
		U_LIGHT0_POSITION, U_LIGHT0_COLOR, U_LIGHT0_POWER, U_LIGHT0_KC, U_LIGHT0_KL, U_LIGHT0_KQ, U_LIGHT0_TYPE, U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF, U_LIGHT0_COSINNER, U_LIGHT0_EXPONENT,
		U_NUMLIGHTS, U_COLOR_TEXTURE_ENABLED, U_COLOR_TEXTURE, U_TEXT_ENABLED, U_TEXT_COLOR, U_TOTAL
	};
	bool showDebugInfo, showLightSphere;
	char keys[7] = {'1', '2', '3', '4', '8', '9', '0'};
	double debugBounceTime, lightBounceTime;
	Light light[1]{Light(0.f, 192.4f, 0.f)};
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	unsigned m_vertexArrayID, m_programID, m_parameters[(unsigned int)UNIFORM_TYPE::U_TOTAL];
	void InitLight(), InitMeshes();
	void RenderLight(), RenderMesh(Mesh*, bool), RenderHutBarriers(bool), RenderText(Mesh*, std::string, Color), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float);
public:
	~OtherScene() override{}
	void Init() override, Update(double, float) override, Render(double) override, Exit(Scene*) override;
};
#pragma once
#include <MatrixStack.h>
#include "Car.h"
#include "Scene.h"
#include "Mesh.h"
#include "Light.h"
#include "ParticleSystem.h"

class MyScene: public Scene{
	Car car;
	enum class MESH{
		LEFT, RIGHT, TOP, FRONT, BACK, BOSS_BODY, BOSS_ARM_L, BOSS_ARM_R, BOSS_LEG_LF, BOSS_LEG_RF, BOSS_LEG_LB, BOSS_LEG_RB, BULLET, BASEBALL_BAT, BENCH, POT, RECYCLING_BIN, TRASH,
		CAR_BODY, CAR_WHEEL_LF, CAR_WHEEL_RF, CAR_WHEEL_LB, CAR_WHEEL_RB, GROUND, HUT, LIGHT_SPHERE, SMOKE, TEXT, TEXT_ON_SCREEN, TURRET_TOP, TURRET_BOTTOM, NUM_GEOMETRY
	};
	enum class UNIFORM_TYPE{
		U_MVP, U_MODELVIEW, U_MODELVIEW_INVERSE_TRANSPOSE, U_MATERIAL_AMBIENT, U_MATERIAL_DIFFUSE, U_MATERIAL_SPECULAR, U_MATERIAL_SHININESS, U_LIGHTENABLED,
		U_LIGHT0_POSITION, U_LIGHT0_COLOR, U_LIGHT0_POWER, U_LIGHT0_KC, U_LIGHT0_KL, U_LIGHT0_KQ, U_LIGHT0_TYPE, U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF, U_LIGHT0_COSINNER, U_LIGHT0_EXPONENT, 
		U_LIGHT1_POSITION, U_LIGHT1_COLOR, U_LIGHT1_POWER, U_LIGHT1_KC, U_LIGHT1_KL, U_LIGHT1_KQ, U_LIGHT1_TYPE, U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF, U_LIGHT1_COSINNER, U_LIGHT1_EXPONENT,
		U_LIGHT2_POSITION, U_LIGHT2_COLOR, U_LIGHT2_POWER, U_LIGHT2_KC, U_LIGHT2_KL, U_LIGHT2_KQ, U_LIGHT2_TYPE, U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF, U_LIGHT2_COSINNER, U_LIGHT2_EXPONENT,
		U_LIGHT3_POSITION, U_LIGHT3_COLOR, U_LIGHT3_POWER, U_LIGHT3_KC, U_LIGHT3_KL, U_LIGHT3_KQ, U_LIGHT3_TYPE, U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF, U_LIGHT3_COSINNER, U_LIGHT3_EXPONENT,
		U_NUMLIGHTS, U_COLOR_TEXTURE_ENABLED, U_COLOR_TEXTURE, U_TEXT_ENABLED, U_TEXT_COLOR, U_TOTAL
	};
	bool showDebugInfo, showLightSphere, vibrate;
	char keys[13] = {'1', '2', '3', '4', '5', '6', '7', 'I', 'J', 'K', 'L', 'O', 'U'};
	double autoBounceTime, bulletBounceTime, changeBounceTime, dayBounceTime, debugBounceTime, flickerBounceTime, lightBounceTime, smokeBounceTime, turretBounceTime, vibrateBounceTime;
	float bossTextAngle, hutTextAngle, turretAngle, scaleFactor = 500.f;
	Light light[4]{Light(), Light(-1.4f, .2f, 4.2f, Vector3(0.f, 0.f, -1.f)), Light(1.4f, .2f, 4.2f, Vector3(0.f, 0.f, -1.f)), Light(0.f, 80.f, 500.f)};
	Mesh* meshList[static_cast<unsigned int>(MESH::NUM_GEOMETRY)];
	MS modelStack, viewStack, projectionStack;
	ParticleEmitter bulletGenerator, smokeEmitter;
	unsigned m_vertexArrayID, m_programID, m_parameters[(unsigned int)UNIFORM_TYPE::U_TOTAL];
	Vector3 bossTextFront, hutTextFront, turretFront, turretPos;
	void InitLight(), InitMeshes(), UpdateCar(double);
	void RenderLight(), RenderMesh(Mesh*, bool), RenderSkybox(), RenderText(Mesh*, std::string, Color), RenderTextOnScreen(Mesh*, std::string, Color, float, float, float);
public:
	Car getCar() const{
		return car;
	}
	Car& getCarRef(){
		return car;
	}
	Light& getLight0Ref(){
		return light[0];
	}
	Light& getLight1Ref(){
		return light[1];
	}
	Light& getLight2Ref(){
		return light[2];
	}
	~MyScene() override{}
	void Init() override, Update(double, float) override, Render(double) override, Exit(Scene*) override;
};
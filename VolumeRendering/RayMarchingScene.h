#pragma once
#include <Scene.h>
class RayMarchingScene : public Scene{
	std::shared_ptr<Material> rayTraceVolumeMaterial;
	float minStep = 0.002f;
	float treshold = 0.3f;
	glm::vec3 boundingCubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	RayMarchingScene(std::shared_ptr<Camera> camera);
	RayMarchingScene();

	Scene& update(float dt, float t) override;
	Scene& onInitialization() override;
	Scene& onMouseMove(int px, int py) override;
	Scene& onMouseClick(int button, int state, int px, int py) override;
	Scene& onKeyboardDown(unsigned char key) override;
	Scene& onKeyboardUp(unsigned char key) override;

};


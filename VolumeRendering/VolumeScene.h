#pragma once
#include <Scene.h>
class VolumeScene : public Scene{
	std::shared_ptr<Material> rayTraceVolumeMaterial;
	float minStep = 0.04f;
	glm::vec3 boundingCubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
public:
	VolumeScene(std::shared_ptr<Camera> camera);
	VolumeScene();

	Scene& update(float dt, float t) override; //todo dt
	Scene& onInitialization() override;
	Scene& onMouseMove(int px, int py) override;
	Scene& onMouseClick(int button, int state, int px, int py) override;
	Scene& onKeyboardDown(unsigned char key) override;
	Scene& onKeyboardUp(unsigned char key) override;

};


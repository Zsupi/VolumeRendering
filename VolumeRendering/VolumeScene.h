#pragma once
#include <Scene.h>
class VolumeScene : public Scene{

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


#pragma once
#include <Scene.h>
class DebugScene : public Scene
{
public:
	DebugScene(std::shared_ptr<Camera> camera);
	DebugScene();

	Scene& onInitialization() override;

	Scene& update(float dt, float t) override;
	Scene& onMouseMove(int px, int py) override;
	Scene& onMouseClick(int button, int state, int px, int py) override;
	Scene& onKeyboardDown(unsigned char key) override;
	Scene& onKeyboardUp(unsigned char key) override;
};


#pragma once
#include <Scene.h>
#include <SSBO.h>

class MyScene : public Scene
{
	unsigned int vaoPosition;

	//std::shared_ptr<SSBO> positionBuffer;
	//std::shared_ptr<SSBO> velocityBuffer;
	unsigned int positionBufferID;
	unsigned int velocityBufferID;

	std::shared_ptr<Program> basicProgram;
	std::shared_ptr<Program> bounceComputeProgram;

public:
	MyScene();

	Scene& update(float dt, float t) override;
	Scene& onInitialization() override;
	Scene& onMouseMove(int px, int py) override;
	Scene& onMouseClick(int button, int state, int px, int py) override;
	Scene& onKeyboardDown(unsigned char key) override;
	Scene& onKeyboardUp(unsigned char key) override;
};


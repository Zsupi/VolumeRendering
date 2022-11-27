#pragma once
#include <Scene.h>
#include "ABuffer.h"

class MetaballScene : public Scene {
	static const unsigned int metaballNumber = 6 * 6 * 6;
	static const unsigned int pixelPerMetaball = 200;
	float minStep = 0.04f;
	glm::vec3 boundingCubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	
	std::shared_ptr<ABufferBuilder::ABufferObject> aBuffer;

public:

	MetaballScene();

	Scene& update(float dt, float t) override;
	Scene& onInitialization() override;
	Scene& onMouseMove(int px, int py) override;
	Scene& onMouseClick(int button, int state, int px, int py) override;
	Scene& onKeyboardDown(unsigned char key) override;
	Scene& onKeyboardUp(unsigned char key) override;

private:
	void generateSSBOs();
	void bindSSBOs();
	std::vector<glm::vec4> generateMetaballs(glm::vec3 dimension);
};


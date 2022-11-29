#pragma once
#include <Scene.h>
#include "ABuffer.h"

class MetaballScene : public Scene {
	static const unsigned int pixelPerMetaball = 10000;
	float minStep = 0.04f;
	glm::vec3 boundingCubePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::uvec3 metaballDimension = glm::uvec3(6u, 6u, 6u);
	unsigned int metaballNumber = metaballDimension.x * metaballDimension.y * metaballDimension.z;
	
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
	std::vector<glm::vec4> generateMetaballs(glm::vec3 dimension);
};


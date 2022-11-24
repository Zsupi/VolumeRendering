#pragma once
#include <Scene.h>
class MetaballScene : public Scene {
public:
	static const unsigned int metaballNumber = 6 * 6 * 6;
	static const unsigned int pixelPerMetaball = 200;

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


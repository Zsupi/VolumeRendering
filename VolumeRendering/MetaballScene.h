#pragma once
#include <Scene.h>
#include <ACB.h>
#include <SSBO.h>

/*
	Padding is needed to scale the buffer's element up to 16 byte (vec4 in glsl).
	Otherwise the std430 or std140 type buffers won't work properly.
*/

struct ScreenBuffer {
	unsigned int pixel;
private:
	float __padding[3];
};

struct LinkedListBuffer {
	glm::uvec2 element;
private:
	float __padding[2];
};

class MetaballScene : public Scene {
	static const unsigned int metaballNumber = 6 * 6 * 6;
	static const unsigned int pixelPerMetaball = 200;

	std::shared_ptr<SSBO> screenBuffer;
	std::shared_ptr <SSBO> linkedListBuffer;
	std::shared_ptr<ACB> atomicCounterBuffer;

	std::shared_ptr<Program> metaballProgram;
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


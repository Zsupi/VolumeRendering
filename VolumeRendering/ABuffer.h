#pragma once
#include <SSBO.h>
#include <ACB.h>
#include <Program.h>
class ABufferBuilder {

public:
	class ABufferObject {

		enum Stage {
			CREATE,
			USE
		};

		friend class ABufferBuilder;
		std::shared_ptr<SSBO> screenBuffer;
		std::shared_ptr<SSBO> linkedListBuffer;
		std::shared_ptr<SSBO> positionBuffer;
		std::shared_ptr<ACB> atomicCounterBuffer;

		unsigned int linkedListBufferSize = 0;
		unsigned int screenBufferSize = 0;

		unsigned int positiobBufferLocation = 1;
		unsigned int screenBufferLocation = 2;
		unsigned int linkedListBufferLocation = 3;
		unsigned int atomicCounterLocation = 0;

		std::shared_ptr<Program> creationProgram;
		std::shared_ptr<Program> drawProgram;

		Stage stage;

		std::vector<SSBO::uvec2_element> zeroScreenBuffer;

		ABufferObject& resetScreenBuffer();
		ABufferObject& resetLinkedListBuffer();

	public:
		ABufferObject();

		ABufferObject& bind();
		ABufferObject& unbind();
		ABufferObject& resetCounter();
		ABufferObject& changeProgram();
		ABufferObject& resetBuffers();
	};

private:
	std::shared_ptr<ABufferObject> aBuffer;

public:

	ABufferBuilder();

	ABufferBuilder& setCreationProgram(std::shared_ptr<Program> program);
	ABufferBuilder& setDrawProgram(std::shared_ptr<Program> program);
	ABufferBuilder& setListSize(unsigned int size);
	ABufferBuilder& setPixelNumber(unsigned int size);
	ABufferBuilder& setMetaballData(std::vector<glm::vec4> positions);
	ABufferBuilder& setScreenBufferLocation(unsigned int location);
	ABufferBuilder& setLinkedListBufferLocation(unsigned int location);
	ABufferBuilder& setPositionBufferLocation(unsigned int location);
	ABufferBuilder& setCounterLocation(unsigned int location);
	std::shared_ptr<ABufferObject> build();
};



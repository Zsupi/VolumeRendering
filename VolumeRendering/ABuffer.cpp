#include "ABuffer.h"

ABufferBuilder::ABufferObject& ABufferBuilder::ABufferObject::resetScreenBuffer() {
	screenBuffer->LoadData(zeroScreenBuffer, screenBufferSize * sizeof(SSBO::uint_element));
	return *this;
}

ABufferBuilder::ABufferObject& ABufferBuilder::ABufferObject::resetLinkedListBuffer() {
	std::vector<SSBO::uvec2_element> data;
	for (unsigned int i = 0; i < linkedListBufferSize; i++) {
		SSBO::uvec2_element element;
		data.push_back(element);
	}

	linkedListBuffer->LoadData(data, linkedListBufferSize * sizeof(SSBO::uvec2_element));
	return *this;
}

ABufferBuilder::ABufferObject::ABufferObject() {
	atomicCounterBuffer = std::make_shared<ACB>();
	atomicCounterBuffer->Create();
	stage = Stage::CREATE;

	for (unsigned int i = 0; i < linkedListBufferSize; i++) {
		SSBO::uvec2_element element;
		zeroScreenBuffer.push_back(element);
	}
}

ABufferBuilder::ABufferObject& ABufferBuilder::ABufferObject::bind() {
	stage == Stage::CREATE ? creationProgram->bind() : drawProgram->bind();
	positionBuffer->Bind(positiobBufferLocation);
	screenBuffer->Bind(screenBufferLocation);
	linkedListBuffer->Bind(linkedListBufferLocation);
	atomicCounterBuffer->Bind(atomicCounterLocation);
	return *this;
}

ABufferBuilder::ABufferObject& ABufferBuilder::ABufferObject::unbind() {
	positionBuffer->Unbind();
	screenBuffer->Unbind();
	linkedListBuffer->Unbind();
	atomicCounterBuffer->Unbind();
	return *this;
}

ABufferBuilder::ABufferObject& ABufferBuilder::ABufferObject::resetCounter() {
	atomicCounterBuffer->Reset(atomicCounterLocation);
	return *this;
}

ABufferBuilder::ABufferObject& ABufferBuilder::ABufferObject::changeProgram() {
	if (stage == Stage::CREATE) {
		stage = Stage::USE;
	}
	else {
		stage = Stage::CREATE;
	}
	return *this;
}

ABufferBuilder::ABufferObject& ABufferBuilder::ABufferObject::resetBuffers() {
	//resetLinkedListBuffer();
	resetScreenBuffer();
	return *this;
}

ABufferBuilder::ABufferBuilder() {
	aBuffer = std::make_shared<ABufferBuilder::ABufferObject>();
}

ABufferBuilder& ABufferBuilder::setCreationProgram(std::shared_ptr<Program> program) {
	aBuffer->creationProgram = program;
	return *this;
}

ABufferBuilder& ABufferBuilder::setDrawProgram(std::shared_ptr<Program> program) {
	aBuffer->drawProgram = program;
	return *this;
}

ABufferBuilder& ABufferBuilder::setListSize(unsigned int size) {
	aBuffer->linkedListBufferSize = size;
	aBuffer->linkedListBuffer = std::make_shared<SSBO>();
	aBuffer->resetLinkedListBuffer();
	return *this;
}

ABufferBuilder& ABufferBuilder::setPixelNumber(unsigned int size) {
	aBuffer->screenBufferSize = size;
	aBuffer->screenBuffer = std::make_shared<SSBO>();
	aBuffer->resetScreenBuffer();
	return *this;
}

ABufferBuilder& ABufferBuilder::setMetaballData(std::vector<glm::vec4> positions) {
	aBuffer->positionBuffer = std::make_shared<SSBO>();
	aBuffer->positionBuffer->LoadData(positions, positions.size() * sizeof(glm::vec4));
	return *this;
}

ABufferBuilder& ABufferBuilder::setScreenBufferLocation(unsigned int location) {
	aBuffer->screenBufferLocation = location;
	return *this;
}

ABufferBuilder& ABufferBuilder::setLinkedListBufferLocation(unsigned int location) {
	aBuffer->linkedListBufferLocation = location;
	return *this;
}

ABufferBuilder& ABufferBuilder::setPositionBufferLocation(unsigned int location) {
	aBuffer->positiobBufferLocation = location;
	return *this;
}

ABufferBuilder& ABufferBuilder::setCounterLocation(unsigned int location) {
	aBuffer->atomicCounterLocation = location;
	return *this;
}

std::shared_ptr<ABufferBuilder::ABufferObject> ABufferBuilder::build() {
	return aBuffer;
}

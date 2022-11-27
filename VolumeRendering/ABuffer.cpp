#include "ABuffer.h"

ABufferBuilder::ABufferObject::ABufferObject() {
	atomicCounterBuffer = std::make_shared<ACB>();
	atomicCounterBuffer->Create();
	stage = Stage::CREATE;
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
	aBuffer->linkedListBuffer = std::make_shared<SSBO>();
	
	std::vector<SSBO::uvec2_element> data;
	for (unsigned int i = 0; i < size; i++) {
		SSBO::uvec2_element element;
		data.push_back(element);
	}
	
	aBuffer->linkedListBuffer->LoadData(data, size * sizeof(SSBO::uvec2_element));
	return *this;
}

ABufferBuilder& ABufferBuilder::setPixelNumber(unsigned int size) {
	aBuffer->screenBuffer = std::make_shared<SSBO>();

	std::vector<SSBO::uint_element> data;
 	for (unsigned int i = 0; i < size; i++) {
		SSBO::uint_element element;
		data.push_back(element);
	}

	aBuffer->linkedListBuffer->LoadData(data, size * sizeof(SSBO::uint_element));
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

#pragma once
#include <SSBO.h>
#include <Program.h>
#include <Texture3D.h>
#include <ACB.h>
class MetaballCreator {
	std::shared_ptr<Program> computeProgram;

	std::shared_ptr<SSBO> positions;
	std::shared_ptr<ACB> counter;
	std::shared_ptr<Texture3D> volumeData;
	
	glm::vec3 dimension = glm::vec3(6.0f, 6.0f, 6.0f);

	bool ran = false;

public:
	MetaballCreator(std::shared_ptr<Program> program, std::shared_ptr<Texture3D> volumeData, glm::vec3 dimension);
	MetaballCreator& create();
	std::shared_ptr<SSBO> getPositions();
};


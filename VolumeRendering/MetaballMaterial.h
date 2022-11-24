#pragma once
#include <Material.h>
#include <SSBO.h>
class MetaballMaterial : public Material {
	std::shared_ptr<SSBO> screenBuffer;
	std::shared_ptr <SSBO> linkedListBuffer;

	static const unsigned int treshold = 10;

public:
	MetaballMaterial(std::shared_ptr<Program> program);
	MetaballMaterial(const MetaballMaterial& material);

	MetaballMaterial& operator=(const MetaballMaterial& material);

	void draw() override;
};


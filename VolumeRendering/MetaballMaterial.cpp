#include <GlutApplication.h>
#include <IntUniform.h>
#include "MetaballMaterial.h"
#include "MetaballScene.h"

MetaballMaterial::MetaballMaterial(std::shared_ptr<Program> program) : Material(program) {
	screenBuffer = std::make_shared<SSBO>();
	linkedListBuffer = std::make_shared<SSBO>();

	screenBuffer->LoadZeros(GlutApplication::windowHeight * GlutApplication::windowWidth * sizeof(unsigned int));
	linkedListBuffer->LoadZeros(MetaballScene::metaballNumber * MetaballScene::pixelPerMetaball);

	std::shared_ptr<IntUniform> listSize = std::make_shared<IntUniform>(MetaballScene::metaballNumber * MetaballScene::pixelPerMetaball, "listSize");
	addUniform(listSize);
}

MetaballMaterial::MetaballMaterial(const MetaballMaterial& material) : Material(material) {
	screenBuffer = material.screenBuffer;
	linkedListBuffer = material.linkedListBuffer;
}

MetaballMaterial& MetaballMaterial::operator=(const MetaballMaterial& material) {
	if (this == &material) {
		return *this;
	}

	Material::operator=(material);
	screenBuffer = material.screenBuffer;
	linkedListBuffer = material.linkedListBuffer;

	return *this;
}

void MetaballMaterial::draw() {
	screenBuffer->Bind(2);
	linkedListBuffer->Bind(3);
	Material::draw();
}

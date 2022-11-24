#pragma once
#include <Geometry.h>
#include <SSBO.h>
class MetaballGeometry : public Geometry {
	std::vector<glm::vec4> positions;
	std::shared_ptr<SSBO> positionBuffer;
public:
	MetaballGeometry(std::vector<glm::vec4> metaballPositions);
	MetaballGeometry(const MetaballGeometry& geometry);

	std::vector<unsigned int> getIndices(unsigned int size) const;
	std::vector<unsigned int> getIndices() const;
	
	MetaballGeometry& operator=(const MetaballGeometry& geometry);

	virtual void draw() override;
};


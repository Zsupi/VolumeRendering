#pragma once
#include <Geometry.h>
#include <SSBO.h>
class MetaballGeometry : public Geometry {
	unsigned int nMetaballs;
public:
	MetaballGeometry(unsigned int nMetaballs);
	MetaballGeometry(const MetaballGeometry& geometry);

	std::vector<unsigned int> getIndices(unsigned int size) const;
	std::vector<unsigned int> getIndices() const;
	
	MetaballGeometry& operator=(const MetaballGeometry& geometry);

	virtual void draw() override;
};


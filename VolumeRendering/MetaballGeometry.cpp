#include "MetaballGeometry.h"

MetaballGeometry::MetaballGeometry(std::vector<glm::vec4> metaballPositions) : Geometry(), positions(metaballPositions) {
    vao.Bind();
    
    auto metaballIndices = getIndices(metaballPositions.size());
    VBO metaballIndicesVbo(metaballIndices);
    
    positionBuffer = std::make_shared<SSBO>();
    positionBuffer->LoadData(positions, positions.size() * sizeof(glm::vec4));

    vao.LinkAttrib(metaballIndicesVbo, 0, 1, GL_UNSIGNED_INT, 0, NULL);

    vao.Unbind();
    metaballIndicesVbo.Unbind();
}

MetaballGeometry::MetaballGeometry(const MetaballGeometry& geometry) 
    : Geometry(geometry), positions(geometry.positions) {}

std::vector<unsigned int> MetaballGeometry::getIndices(unsigned int size) const {
    std::vector<unsigned int> metaballIndices;

    for (unsigned int i = 0; i < size; i++) {
        metaballIndices.push_back(i);
    }

    return metaballIndices;
}

std::vector<unsigned int> MetaballGeometry::getIndices() const {
    std::vector<unsigned int> metaballIndices;

    for (unsigned int i = 0; i < positions.size(); i++) {
        metaballIndices.push_back(i);
    }

    return metaballIndices;
}

MetaballGeometry& MetaballGeometry::operator=(const MetaballGeometry& geometry) {
    if (this == &geometry) {
        return *this;
    }

    Geometry::operator=(geometry);
    this->positions = geometry.positions;

    return *this;
}

void MetaballGeometry::draw() {
    vao.Bind();
    positionBuffer->Bind(1);
    glDrawArrays(GL_POINTS, 0, positions.size());
    vao.Unbind();
}

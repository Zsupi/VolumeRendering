#include "MetaballGeometry.h"

MetaballGeometry::MetaballGeometry(unsigned int nMetaballs) : Geometry(), nMetaballs(nMetaballs) {
    vao.Bind();
    
    auto metaballIndices = getIndices(nMetaballs);
    VBO metaballIndicesVbo(metaballIndices);

    vao.LinkAttrib(metaballIndicesVbo, 0, 1, GL_UNSIGNED_INT, 0, NULL);

    vao.Unbind();
    metaballIndicesVbo.Unbind();
}

MetaballGeometry::MetaballGeometry(const MetaballGeometry& geometry) 
    : Geometry(geometry), nMetaballs(geometry.nMetaballs) {}

std::vector<unsigned int> MetaballGeometry::getIndices(unsigned int size) const {
    std::vector<unsigned int> metaballIndices;

    for (unsigned int i = 0; i < size; i++) {
        metaballIndices.push_back(i);
    }

    return metaballIndices;
}

std::vector<unsigned int> MetaballGeometry::getIndices() const {
    std::vector<unsigned int> metaballIndices;

    for (unsigned int i = 0; i < nMetaballs; i++) {
        metaballIndices.push_back(i);
    }

    return metaballIndices;
}

MetaballGeometry& MetaballGeometry::operator=(const MetaballGeometry& geometry) {
    if (this == &geometry) {
        return *this;
    }

    Geometry::operator=(geometry);
    this->nMetaballs = geometry.nMetaballs;

    return *this;
}

void MetaballGeometry::draw() {
    vao.Bind();
    glDrawArrays(GL_POINTS, 0, nMetaballs);
    vao.Unbind();
}

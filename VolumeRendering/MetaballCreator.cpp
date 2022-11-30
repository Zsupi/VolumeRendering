#include "MetaballCreator.h"

MetaballCreator::MetaballCreator(std::shared_ptr<Program> program, std::shared_ptr<Texture3D> volumeData, glm::vec3 dimension) {
    this->computeProgram = program;
    this->volumeData = volumeData;
    this->dimension = dimension;

    unsigned int size = dimension.x * dimension.y * dimension.z;

    positions = std::make_shared<SSBO>();
    positions->LoadZeros(size * sizeof(glm::vec4));

    counter = std::make_shared<ACB>();
    counter->Create();
}

MetaballCreator& MetaballCreator::create() {
    if (!ran) {
        volumeData->bind(0);
        computeProgram->setUniform(0, "volumeData");
        computeProgram->setUniform(dimension, "volumeDimension");
        counter->Bind(0);
        positions->Bind(1);
        computeProgram->bind();
        glDispatchCompute(dimension.x, dimension.y, dimension.z);
        glMemoryBarrier(GL_ALL_BARRIER_BITS);
        ran = true;
    }
    return *this;
}

std::shared_ptr<SSBO> MetaballCreator::getPositions() {
    return positions;
}

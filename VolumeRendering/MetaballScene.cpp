#include "MetaballScene.h"
#include "MetaballGeometry.h"
#include <FloatUniform.h>
#include <FullScreenQuad.h>
#include <UVec2Uniform.h>

MetaballScene::MetaballScene() {
    drawMesh(false);
}

Scene& MetaballScene::update(float dt, float t) {
    glDepthFunc(GL_ALWAYS);
    aBuffer->changeProgram();
    aBuffer->resetCounter();
    aBuffer->resetBuffers();
    aBuffer->bind();
    getMesh("abuffer")->draw(camera);
    glDepthFunc(GL_LESS);

    aBuffer->changeProgram();
    aBuffer->bind();
    getMesh("rayMarch")->draw(camera);

    return *this;
}

Scene& MetaballScene::onInitialization() {
    std::vector<glm::vec4> metaballs = generateMetaballs(glm::vec3(6, 6, 6));

#pragma region A-Buffer Program
    std::shared_ptr<Program> aBufferProgram = std::make_shared<Program>();
    aBufferProgram->attachShader(CreateShader(GL_VERTEX_SHADER, "Abuffer.vert"))
        .attachShader(CreateShader(GL_GEOMETRY_SHADER, "Abuffer.geom"))
        .attachShader(CreateShader(GL_FRAGMENT_SHADER, "Abuffer.frag"))
        .linkProgram();

    std::shared_ptr<Material> aBufferMaterial = std::make_shared<Material>(aBufferProgram);
    aBufferMaterial->addUniform(std::make_shared<UVec2Uniform>(glm::uvec2(GlutApplication::windowWidth, GlutApplication::windowHeight), "windowSize"));
    std::shared_ptr<MetaballGeometry> aBufferGeometry = std::make_shared<MetaballGeometry>(metaballs.size());
    
    Mesh aBufferMetaball = Mesh(aBufferMaterial, aBufferGeometry);
    addMesh(aBufferMetaball, "abuffer");

#pragma endregion

#pragma region RayMarching Program
    std::shared_ptr<Program> rayMarchingProgram = std::make_shared<Program>();
    rayMarchingProgram->attachShader(CreateShader(GL_VERTEX_SHADER, "ABufferRayMarch.vert"))
        .attachShader(CreateShader(GL_FRAGMENT_SHADER, "ABufferRayMarch.frag"))
        .linkProgram();

    std::shared_ptr<Material> rayMarchingMaterial = std::make_shared<Material>(rayMarchingProgram);
    rayMarchingMaterial->addUniform(std::make_shared<UVec2Uniform>(glm::uvec2(GlutApplication::windowWidth, GlutApplication::windowHeight), "windowSize"));
    rayMarchingMaterial->addUniform(std::make_shared<FloatUniform>(minStep, "minStep"));
    std::shared_ptr<FullScreenQuad> fullScreenQuad = std::make_shared< FullScreenQuad>();
    
    Mesh rayTraceVolumeMesh = Mesh(rayMarchingMaterial, fullScreenQuad);
    addMesh(rayTraceVolumeMesh, "rayMarch");
#pragma endregion

#pragma region A-Buffer 
    aBuffer = ABufferBuilder()
        .setCreationProgram(aBufferProgram)
        .setDrawProgram(rayMarchingProgram)
        .setMetaballData(metaballs)
        .setListSize(MetaballScene::metaballNumber * MetaballScene::pixelPerMetaball)
        .setPixelNumber(GlutApplication::windowHeight * GlutApplication::windowWidth)
        .build();
#pragma endregion
    
    return *this;
}

Scene& MetaballScene::onMouseMove(int px, int py) {
    return *this;
}

Scene& MetaballScene::onMouseClick(int button, int state, int px, int py) {
    return *this;
}

Scene& MetaballScene::onKeyboardDown(unsigned char key) {
    return *this;
}

Scene& MetaballScene::onKeyboardUp(unsigned char key) {
    return *this;
}

std::vector<glm::vec4> MetaballScene::generateMetaballs(glm::vec3 dimension) {

    std::vector<glm::vec4> positions;

    for (int i = 0; i < dimension.x; i++) {
        for (int j = 0; j < dimension.y; j++) {
            for (int k = 0; k < dimension.z; k++) {
                positions.push_back(glm::vec4(-i, -j, -k, 1.0f)/glm::vec4(dimension, 1.0f));
            }
        }
    }

    return positions;
}


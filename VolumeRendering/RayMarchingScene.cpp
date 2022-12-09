#include <Texture3D.h>
#include <FloatUniform.h>
#include <FullScreenQuad.h>
#include "RayMarchingScene.h"
#include <Vec3Uniform.h>

RayMarchingScene::RayMarchingScene(std::shared_ptr<Camera> camera) : Scene(camera) {
}

RayMarchingScene::RayMarchingScene() : Scene(glm::vec3(glm::vec3(0.5, 0, 0)), glm::vec3(0, 0, 0)) {
}

Scene& RayMarchingScene::update(float dt, float t) {
    return *this;
}

Scene& RayMarchingScene::onInitialization() {
    //std::shared_ptr<Program> rayTraceVolumeProgram = std::make_shared<Program>("fullScreenVS.vert", "raytraceVolumeFS.frag");
    std::shared_ptr<Program> rayTraceVolumeProgram = std::make_shared<Program>("fullScreenVS.vert", "raymarchBrain.frag");
    //std::shared_ptr<Program> rayTraceVolumeProgram = std::make_shared<Program>("fullScreenVS.vert", "raymarchMetaball.frag");
    rayTraceVolumeMaterial = std::make_shared<Material>(rayTraceVolumeProgram);
    rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(minStep, "minStep"));
    rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(treshold, "treshold"));
    //rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    
    rayTraceVolumeMaterial->addTexture(std::make_shared<Texture3D>("brain-at_4096.jpg"), "brainTexture");
    //rayTraceVolumeMaterial->addTexture(std::make_shared<Texture3D>("body-at_4096.jpg"), "brainTexture");
    //rayTraceVolumeMaterial->addTexture(std::make_shared<Texture3D>("internals-at_4096.jpg"), "brainTexture");
    
    std::shared_ptr<FullScreenQuad> fullScreenQuad = std::make_shared< FullScreenQuad>();
    Mesh rayTraceVolumeMesh = Mesh(rayTraceVolumeMaterial, fullScreenQuad);

    addMesh(rayTraceVolumeMesh, "FullScreenQuad");
    
    return *this;
}

Scene& RayMarchingScene::onMouseMove(int px, int py) {
    return *this;
}

Scene& RayMarchingScene::onMouseClick(int button, int state, int px, int py) {
    return *this;
}

Scene& RayMarchingScene::onKeyboardDown(unsigned char key) {
    if (key == 'f') {
        if (minStep > 0.02)
            minStep -= 0.001f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(minStep, "minStep"));
    }
    if (key == 'g') {
        minStep += 0.001f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(minStep, "minStep"));
    }
    if (key == 'r') {
        treshold -= 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(treshold, "treshold"));
    }
    if (key == 't') {
        treshold += 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(treshold, "treshold"));
    }

    /*if (key == GlutApplication::ARROW_UP_VALUE) {
        boundingCubePosition.z -= 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    }
    if (key == GlutApplication::ARROW_DOWN_VALUE) {
        boundingCubePosition.z += 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    }
    if (key == GlutApplication::ARROW_RIGHT_VALUE) {
        boundingCubePosition.x += 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    }
    if (key == GlutApplication::ARROW_LEFT_VALUE) {
        boundingCubePosition.x -= 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    }
    std::cout << boundingCubePosition.x << " " << boundingCubePosition.y << " " << boundingCubePosition.z << std::endl;
    */return *this;
}

Scene& RayMarchingScene::onKeyboardUp(unsigned char key) {
    return *this;
}

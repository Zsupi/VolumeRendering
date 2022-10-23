#include <Texture3D.h>
#include <FloatUniform.h>
#include <FullScreenQuad.h>
#include "VolumeScene.h"
#include <Vec3Uniform.h>

VolumeScene::VolumeScene(std::shared_ptr<Camera> camera) : Scene(camera) {
}

VolumeScene::VolumeScene() : Scene() {
}

Scene& VolumeScene::update(float dt, float t) {
    return *this;
}

Scene& VolumeScene::onInitialization() {
    //std::shared_ptr<Program> rayTraceVolumeProgram = std::make_shared<Program>("fullScreenVS.glsl", "raytraceVolumeFS.glsl");
    //std::shared_ptr<Program> rayTraceVolumeProgram = std::make_shared<Program>("fullScreenVS.glsl", "raymarchBrain.glsl");
    std::shared_ptr<Program> rayTraceVolumeProgram = std::make_shared<Program>("fullScreenVS.glsl", "raymarchMetaball.glsl");
    rayTraceVolumeMaterial = std::make_shared<Material>(rayTraceVolumeProgram);
    rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(minStep, "minStep"));
    //rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    
    rayTraceVolumeMaterial->addTexture(std::make_shared<Texture3D>("brain-at_4096.jpg"), "brainTexture");
    //rayTraceVolumeMaterial->addTexture(std::make_shared<Texture3D>("body-at_4096.jpg"), "brainTexture");
    //rayTraceVolumeMaterial->addTexture(std::make_shared<Texture3D>("internals-at_4096.jpg"), "brainTexture");
    
    std::shared_ptr<FullScreenQuad> fullScreenQuad = std::make_shared< FullScreenQuad>();
    Mesh rayTraceVolumeMesh = Mesh(rayTraceVolumeMaterial, fullScreenQuad);

    addMesh(rayTraceVolumeMesh, "FullScreenQuad");
    
    return *this;
}

Scene& VolumeScene::onMouseMove(int px, int py) {
    // // O: insert return statement here
    return *this;
}

Scene& VolumeScene::onMouseClick(int button, int state, int px, int py) {
    return *this;
}

Scene& VolumeScene::onKeyboardDown(unsigned char key) {
    if (key == 'f') {
        if (minStep > 0.02)
            minStep -= 0.01f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(minStep, "minStep"));
    }
    if (key == 'g') {
        minStep += 0.01f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<FloatUniform>(minStep, "minStep"));
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
    if (key == 'r') {
        boundingCubePosition.y += 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    }
    if (key == 't') {
        boundingCubePosition.y -= 0.1f;
        rayTraceVolumeMaterial->addUniform(std::make_shared<Vec3Uniform>(boundingCubePosition, "cubePosition"));
    }
    std::cout << boundingCubePosition.x << " " << boundingCubePosition.y << " " << boundingCubePosition.z << std::endl;
    */return *this;
}

Scene& VolumeScene::onKeyboardUp(unsigned char key) {
    // // O: insert return statement here
    return *this;
}

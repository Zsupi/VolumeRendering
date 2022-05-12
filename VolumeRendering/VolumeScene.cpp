#include <Texture3D.h>
#include "VolumeScene.h"
#include "FullScreenQuad.h"

VolumeScene::VolumeScene(std::shared_ptr<Camera> camera) : Scene(camera) {
}

VolumeScene::VolumeScene() : Scene() {
}

Scene& VolumeScene::update(float dt, float t) {
    return *this;
}

Scene& VolumeScene::onInitialization() {
    std::shared_ptr<Program> rayTraceVolumeProgram = std::make_shared<Program>("fullScreenVS.glsl", "raytraceVolumeFS.glsl");
    std::shared_ptr<Material> rayTraceVolumeMaterial = std::make_shared<Material>(rayTraceVolumeProgram);
    rayTraceVolumeMaterial->addTexture(std::make_shared<Texture3D>("brain-at_4096.jpg"), "textureColor");
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
    // // O: insert return statement here
    return *this;
}

Scene& VolumeScene::onKeyboardDown(unsigned char key) {
    // // O: insert return statement here
    return *this;
}

Scene& VolumeScene::onKeyboardUp(unsigned char key) {
    // // O: insert return statement here
    return *this;
}

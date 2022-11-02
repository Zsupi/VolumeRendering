#include "DebugScene.h"
#include "Cube.h"
#include "Light.h"

DebugScene::DebugScene(std::shared_ptr<Camera> camera) : Scene(camera) {
}

DebugScene::DebugScene() : Scene() {
}

Scene& DebugScene::update(float dt, float  t) {
    return *this;
}

Scene& DebugScene::onInitialization() {
    
    std::shared_ptr<Program> basicProgram = std::make_shared<Program>("defaultVS.glsl", "solidColorFS.glsl");
    
    std::shared_ptr<Cube> cube = std::make_shared<Cube>();
    std::shared_ptr<Material> material = std::make_shared<Material>(basicProgram);
    material->setSolidColor(glm::vec3(1.0f, 0.5f, 0.0f));
    setUpLightUniforms(material);
    Illumination defaultIllumination(1.6f, 4.4f, 1.0f, 35.0f);
    material->setIllumination(defaultIllumination);
    Mesh cubeMesh = Mesh(material, cube);



    LightData lightData = LightData(
        glm::vec3(0.4f, 0.4f, 0.4f),
        glm::vec3(0.8f, 0.5f, 0.0f),
        glm::vec3(0.75f, 0.75f, 0.75f),
        glm::vec3(5.0f, 3.0f, 2.0f),
        0.09f,
        0.032f);


    addMesh(cubeMesh, "cube");
    addLight(lightData);

    return *this;
}

Scene& DebugScene::onMouseMove(int px, int py) {
    return *this;
}
Scene& DebugScene::onMouseClick(int button, int state, int px, int py) {
    return *this;
}
Scene& DebugScene::onKeyboardDown(unsigned char key) {
    return *this;
}

Scene& DebugScene::onKeyboardUp(unsigned char key) {
    return *this;
}
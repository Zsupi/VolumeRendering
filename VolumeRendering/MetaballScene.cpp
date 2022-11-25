#include "MetaballScene.h"
#include "MetaballGeometry.h"

MetaballScene::MetaballScene() {
}

Scene& MetaballScene::update(float dt, float t) {
    //todo turn off the depth buffer
    metaballProgram->bind();
    bindSSBOs();
    metaballProgram->unbind();
    return *this;
}

Scene& MetaballScene::onInitialization() {
    metaballProgram = std::make_shared<Program>();
    metaballProgram->attachShader(CreateShader(GL_VERTEX_SHADER, "Abuffer.vert"))
        .attachShader(CreateShader(GL_GEOMETRY_SHADER, "Abuffer.geom"))
        .attachShader(CreateShader(GL_FRAGMENT_SHADER, "Abuffer.frag"))
        .linkProgram();

    std::shared_ptr<Material> metaballMaterial = std::make_shared<Material>(metaballProgram);
    std::shared_ptr<MetaballGeometry> metaballGeometry = std::make_shared<MetaballGeometry>(generateMetaballs(glm::vec3(6, 6, 6)));
    
    Mesh aBufferMetaball = Mesh(metaballMaterial, metaballGeometry);
    addMesh(aBufferMetaball, "abuffer");

    generateSSBOs();

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

void MetaballScene::generateSSBOs() {
    screenBuffer = std::make_shared<SSBO>();
    linkedListBuffer = std::make_shared<SSBO>();
    atomicCounterBuffer = std::make_shared<ACB>();

    //todo change it to loadData
    screenBuffer->LoadZeros(GlutApplication::windowHeight * GlutApplication::windowWidth * sizeof(ScreenBuffer));
    linkedListBuffer->LoadZeros(MetaballScene::metaballNumber * MetaballScene::pixelPerMetaball * sizeof(LinkedListBuffer));
    atomicCounterBuffer->Create();
}

void MetaballScene::bindSSBOs() {
    screenBuffer->Bind(2);
    linkedListBuffer->Bind(3);
    atomicCounterBuffer->Bind(0);
}

std::vector<glm::vec4> MetaballScene::generateMetaballs(glm::vec3 dimension) {

    std::vector<glm::vec4> positions;

    for (int i = 0; i < dimension.x; i++) {
        for (int j = 0; j < dimension.y; j++) {
            for (int k = 0; k < dimension.z; k++) {
                positions.push_back(glm::vec4(i, j, k, 1.0f));
            }
        }
    }

    return positions;
}


#include "MetaballScene.h"
#include "MetaballMaterial.h"
#include "MetaballGeometry.h"

MetaballScene::MetaballScene() {
}

Scene& MetaballScene::update(float dt, float t) {
    return *this;
}

Scene& MetaballScene::onInitialization() {
    std::shared_ptr<Program> metaballProgram = std::make_shared<Program>();
    metaballProgram->attachShader(CreateShader(GL_VERTEX_SHADER, "Abuffer.vert"))
        .attachShader(CreateShader(GL_GEOMETRY_SHADER, "Abuffer.geom"))
        .attachShader(CreateShader(GL_FRAGMENT_SHADER, "Abuffer.frag"))
        .linkProgram();

    std::shared_ptr<MetaballMaterial> metaballMaterial = std::make_shared<MetaballMaterial>(metaballProgram);
    std::shared_ptr<MetaballGeometry> metaballGeometry = std::make_shared<MetaballGeometry>(generateMetaballs(glm::vec3(6, 6, 6)));
    
    Mesh aBufferMetaball = Mesh(metaballMaterial, metaballGeometry);
    addMesh(aBufferMetaball, "abuffer");

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
                positions.push_back(glm::vec4(i, j, k, 1.0f));
            }
        }
    }

    return positions;
}


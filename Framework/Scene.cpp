#include "Scene.h"
#include "IntUniform.h"

#include "Cube.h"
#include "GroundPlane.h"
#include "Texture2D.h"
#include "Texture3D.h"
#include "Textured3DCube.h"
#include "FullScreenQuad.h"

void Scene::glutUpdate(float dt, float t) {
	camera->Animate(0.01f);
	camera->Update();

	for (auto i : meshes)
		i.second->draw(camera);

	for (auto i : lights)
		i.draw(camera);
	//this->update();
}

void Scene::glutOnMouseMove(int pX, int pY) {
	camera->Move2D(pX, pY);
	this->onMouseMove(pX, pY);
}

void Scene::glutOnMouseClick(int button, int state, int pX, int pY) {
	camera->SetPos(button, state, pX, pY);
	this->onMouseClick(button, state, pX, pY);
}

void Scene::glutOnKeyboardDown(unsigned char key) {
	camera->ProcessMessage(key, KeyStatus::KEYDOWN);
	this->onKeyboardDown(key);
}

void Scene::glutOnKeyboardUp(unsigned char key) {
	camera->ProcessMessage(key, KeyStatus::KEYUP);
	this->onKeyboardUp(key);
}

void Scene::glutOnInitialization() {
	this->onInitialization();
}

Scene::Scene(std::shared_ptr<Camera> camera):camera(camera) {
	camera->SetViewport(0, 0, GlutApplication::windowWidth, GlutApplication::windowHeight);
	camera->SetPosition(glm::vec3(0.5, 0, 0));
	camera->SetLookAt(glm::vec3(0, 0, 0));
	camera->SetClipping(.1, 1000);
	camera->SetFOV(45);
	camera->Update();

	/*LightData data(
		glm::vec3(0.4f, 0.4f, 0.4f),
		glm::vec3(0.8f, 0.5f, 0.0f),
		glm::vec3(0.75f, 0.75f, 0.75f),
		glm::vec3(5.0f, 3.0f, 2.0f),
		0.09f,
		0.032f
	);

	addLight(data);
	data.diffuse = glm::vec3(0.7f, 0.9f, 1.0f);
	data.position = glm::vec3(-8.0f, 6.0f, -2.0f);
	addLight(data);

	std::shared_ptr<Program> defaultProgram = std::make_shared<Program>("defaultVS.glsl", "solidColorFS.glsl");

	std::shared_ptr<Material> defaultMaterial = std::make_shared<Material>(defaultProgram);
	Illumination defaultIllumination(1.6f, 4.4f, 1.0f, 35.0f);
	defaultMaterial->setIllumination(defaultIllumination);
	defaultMaterial->setSolidColor(glm::vec3(0.24f, 0.68f, 0.64f));
	setUpLightUniforms(defaultMaterial);

	std::shared_ptr<Material> groundMaterial = std::make_shared<Material>(defaultProgram);
	Illumination groundIllumination(1.6f, 4.4f, 1.0f, 1.0f);
	groundMaterial->setIllumination(groundIllumination).setSolidColor(glm::vec3(0.80f, 0.81f, 0.83f));;
	setUpLightUniforms(groundMaterial);

	std::shared_ptr<Cube> cubeGeometry = std::make_shared<Cube>();
	Mesh cubeMesh = Mesh(defaultMaterial, cubeGeometry);
	cubeMesh.setPosition(glm::vec3(0.0f, 1.0f, 0.0f));

	std::shared_ptr<GroundPlane> groundPlaneGeometry = std::make_shared<GroundPlane>();
	Mesh groundPlaneMesh = Mesh(groundMaterial, groundPlaneGeometry);

	std::shared_ptr<Program> texturedProgram = std::make_shared<Program>("defaultVS.glsl", "texturedFS.glsl");
	std::shared_ptr<Material> texturedMaterial = std::make_shared<Material>(texturedProgram);
	texturedMaterial->addTexture(std::make_shared<Texture2D>("dust.jpg"), "textureColor");
	texturedMaterial->setIllumination(defaultIllumination);
	setUpLightUniforms(texturedMaterial);
	Mesh texturedCubeMesh = Mesh(texturedMaterial, cubeGeometry);
	texturedCubeMesh.setPosition(glm::vec3(10.0f, 1.0f, 0.0f));

	std::shared_ptr<Program> volumeProgram = std::make_shared<Program>("volumeCubeVS.glsl", "volumeCubeFS.glsl");
	std::shared_ptr<Material> volumeMaterial = std::make_shared<Material>(volumeProgram);
	std::shared_ptr<Textured3DCube> volumeCubeGeometry = std::make_shared<Textured3DCube>();
	volumeMaterial->addTexture(std::make_shared<Texture3D>("brain-at_4096.jpg"), "textureColor");
	Mesh volumeCubeMesh = Mesh(volumeMaterial, volumeCubeGeometry);
	volumeCubeMesh.setPosition(glm::vec3(-10.0f, 1.0f, 0.0f));

	addMesh(cubeMesh, "Cube");
	addMesh(groundPlaneMesh, "Ground");
	addMesh(texturedCubeMesh, "TexturedCube");
	addMesh(volumeCubeMesh, "VolumeCube");*/
}

Scene::Scene() {
	camera = std::make_shared<Camera>();
	camera->SetViewport(0, 0, GlutApplication::windowWidth, GlutApplication::windowHeight);
	camera->SetPosition(glm::vec3(0.5, 0, 0));
	camera->SetLookAt(glm::vec3(0, 0, 0));
	camera->SetClipping(.1, 1000);
	camera->SetFOV(45);
	camera->Update();
}

Scene& Scene::addMesh(const Mesh& mesh, std::string name) {
	if (meshes.find(name) != meshes.end()) {
		std::cout << "[Error][Scene] '" << name << "' mesh already exist." << std::endl;
		return *this;
	}

	meshes[name] = std::make_shared<Mesh>(mesh);
	return *this;
}

Scene& Scene::addLight(LightData lightData) {
	lights.push_back(Light(lightData));
	return *this;
}

Scene& Scene::setUpLightUniforms(std::shared_ptr<Material> material) {
	for (int i = 0; i < lights.size(); i++) {
		lights[i].setLightUniforms(material, i);
	}
	material->addUniform(std::make_shared<IntUniform>(lights.size(), "nLight"));
	return *this;
}


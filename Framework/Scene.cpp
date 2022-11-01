#include "Scene.h"
#include "IntUniform.h"

#include "Cube.h"
#include "GroundPlane.h"
#include "Texture2D.h"
#include "Texture3D.h"
#include "Textured3DCube.h"
#include "FullScreenQuad.h"

void Scene::glutUpdate(float dt, float t) {
	camera->Animate(dt);
	camera->Update();

	for (auto i : meshes)
		i.second->draw(camera);

	for (auto i : lights)
		i.draw(camera);
	this->update(dt, t);
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


#pragma once
#include <algorithm>
#include "GlutApplication.h"
#include "Light.h"

class Scene : public GlutApplication::GlutAppInterface{
	std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;
	std::vector<Light> lights;
	bool draw = true;

	virtual void glutUpdate(float dt, float t) override final;
	virtual void glutOnMouseMove(int pX, int pY) override final;
	virtual void glutOnMouseClick(int button, int state, int pX, int pY) override final;
	virtual void glutOnKeyboardDown(unsigned char key) override final;
	virtual void glutOnKeyboardUp(unsigned char key) override final;
	virtual void glutOnInitialization() override final;

protected:
	std::shared_ptr<Camera> camera;
public:

	Scene(std::shared_ptr<Camera> camera);
	Scene();
	Scene(glm::vec3 cameraPosition, glm::vec3 lookatPoint);
	
	virtual Scene& drawMesh(bool draw) final;

	virtual Scene& addMesh(const Mesh& mesh, std::string name) final;
	virtual std::shared_ptr<Mesh> getMesh(const std::string name) final;
	virtual Scene& update(float dt, float t) = 0;

	virtual Scene& onInitialization() = 0;
	virtual Scene& onMouseMove(int pX, int pY) = 0;
	virtual Scene& onMouseClick(int button, int state, int pX, int pY) = 0;
	virtual Scene& onKeyboardDown(unsigned char key) = 0;
	virtual Scene& onKeyboardUp(unsigned char key) = 0;

	virtual Scene& addLight(LightData lightData) final;
	virtual Scene& setUpLightUniforms(std::shared_ptr<Material> material) final;
};
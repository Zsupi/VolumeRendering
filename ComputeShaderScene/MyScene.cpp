#include "MyScene.h"
#include <Cube.h>
#include <SSBO.h>

MyScene::MyScene() : Scene(glm::vec3(glm::vec3(50, 0, 0)), glm::vec3(0, 0, 0)) {}

Scene& MyScene::update(float dt, float t) {

	//draw as glpoints.
	particleProgram->bind();
	glm::mat4 V;
	glm::mat4 P;
	glm::mat4 M;
	camera->GetMatricies(V, P, M);
	particleProgram->setUniform(V * P, "viewProjMatrix");

	glBindVertexArray(vaoPosition);
	//positionBuffer->Bind();
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer->ID);
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, size*size);
	
	positionBuffer->Bind(0);
	velocityBuffer->Bind(1);

	bounceComputeProgram->bind();
	//unifrom setting in compute shader
	bounceComputeProgram->setUniform(dt / 1000.0f, "dt");
	glDispatchCompute(size*size, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
	return *this;
}

Scene& MyScene::onInitialization() {
	std::shared_ptr<Program> basicProgram = std::make_shared<Program>();
	
	//Create shaders explicitly
	unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, "basicVS.glsl");
	unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, "basicFS.glsl");

	//Attach shaders to program
	basicProgram->attachShader(vertexShader);
	basicProgram->attachShader(fragmentShader);

	//Link and validate program
	basicProgram->linkProgram();

	//As an alternative to all of the above, you can use:
	//std::shared_ptr<Program> basicProgram = std::make_shared<Program>("basicVS.glsl", "basicFS.glsl");

	std::shared_ptr<Material> basicMaterial = std::make_shared<Material>(basicProgram);
	std::shared_ptr<Cube> cubeGeometry = std::make_shared<Cube>();
	Mesh cubeMesh = Mesh(basicMaterial, cubeGeometry);
	cubeMesh.setPosition(glm::vec3(-5, -5, -5));
	addMesh(cubeMesh, "TestCube");


	bounceComputeProgram = std::make_shared<Program>();
	//Compute shader creation.
	unsigned int bounceComputeShader = CreateShader(GL_COMPUTE_SHADER, "bounceCS.glsl");
	//Attach
	bounceComputeProgram->attachShader(bounceComputeShader);
	//Link
	bounceComputeProgram->linkProgram();

	//Create vector with position data
	std::vector<glm::vec4> positions = std::vector<glm::vec4>(size*size);
	for (int i = 0; i < size*size; i++) {
		int x = i % size * 2;
		int z = i / size * 2;
		int y = x + z;
		y += 1;
		positions[i] = glm::vec4(x, y, z, 1);
	}

	//Create buffer for positions
	positionBuffer = std::make_shared<SSBO>();
	positionBuffer->LoadData(positions, positions.size() * sizeof(glm::vec4));

	//Create buffer for velocities
	velocityBuffer = std::make_shared<SSBO>();
	velocityBuffer->LoadZeros(positions.size() * sizeof(glm::vec4));

	//Create vao for drawing
	glGenVertexArrays(1, &vaoPosition);
	glBindVertexArray(vaoPosition);

	glEnableVertexAttribArray(0);
	//Cannot use positionBuffer->Bind() here, the target is not the same.
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer->ID);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	particleProgram = std::make_shared<Program>();
	unsigned int particleVs = CreateShader(GL_VERTEX_SHADER, "particleVS.glsl");
	unsigned int particleGs = CreateShader(GL_GEOMETRY_SHADER, "particleGS.glsl");
	unsigned int particleFs = CreateShader(GL_FRAGMENT_SHADER, "particleFS.glsl");
	particleProgram->attachShader(particleVs);
	particleProgram->attachShader(particleGs);
	particleProgram->attachShader(particleFs);
	particleProgram->linkProgram();


	return *this;
}

Scene& MyScene::onMouseMove(int px, int py)
{
	return *this;
}

Scene& MyScene::onMouseClick(int button, int state, int px, int py)
{
	return *this;
}

Scene& MyScene::onKeyboardDown(unsigned char key)
{
	return *this;
}

Scene& MyScene::onKeyboardUp(unsigned char key)
{
	return *this;
}


#include <chrono>
#include "GlutApplication.h"
#include "Scene.h"

GlutApplication::GlutApplication() {	
}

void GlutApplication::onInitialization(std::shared_ptr<GlutAppInterface> scene) {
	this->scene = scene;
	scene->glutOnInitialization();

	timeAtFirstFrame = glutGet(GLUT_ELAPSED_TIME);
	timeAtLastFrame = timeAtFirstFrame;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_TEXTURE_3D);
	glClearDepth(1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GlutApplication::onDisplay() {
	glClearColor(0.13f, 0.20f, 0.29f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float timeAtThisFrame = glutGet(GLUT_ELAPSED_TIME);
	float dt = (timeAtThisFrame - timeAtLastFrame) / 1000.0f;
	float t = (timeAtThisFrame - timeAtFirstFrame) / 1000.0f;
	timeAtLastFrame = timeAtThisFrame;

	scene->glutUpdate(dt, t);
	glutSwapBuffers();


}

void GlutApplication::onMouseMove(int pX, int pY) {
	scene->glutOnMouseMove(pX, pY);
}

void GlutApplication::onMouseClick(int button, int state, int pX, int pY) {
	scene->glutOnMouseClick(button, state, pX, pY);
}

void GlutApplication::onKeyboardDown(unsigned char key, int pX, int pY) {
	scene->glutOnKeyboardDown(key);
}

void GlutApplication::onKeyboardUp(unsigned char key, int pX, int pY) {
	scene->glutOnKeyboardUp(key);
}

void GlutApplication::onIdle() {
	//todo dt t felvezetni
	glutPostRedisplay();
}

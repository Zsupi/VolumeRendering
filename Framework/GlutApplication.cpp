#include "GlutApplication.h"
#include "Scene.h"

GlutApplication::GlutApplication() {	
}

void GlutApplication::onInitialization(std::shared_ptr<GlutAppInterface> scene) {
	this->scene = scene;
	scene->glutOnInitialization();

	timeAtFirstFrame = std::chrono::steady_clock::now();
	timeAtLastFrame = timeAtFirstFrame;
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_TEXTURE_3D);
	glClearDepth(1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GlutApplication::onDisplay() {
	glClearColor(0.13f, 0.20f, 0.29f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	crntTime = glutGet(GLUT_ELAPSED_TIME);
	timeDiff = crntTime - prevTime;
	frame++;

	if (crntTime - prevTime > 1000) {

		float fps = frame * 1000.0 / (crntTime - prevTime);

		std::string FPS = std::to_string(fps);
		std::string title = "VolumeRendering " + FPS + " FPS";
		glutSetWindowTitle(title.c_str());
		prevTime = crntTime;
		frame = 0;
	}

	ChronoTime timeAtThisFrame = std::chrono::steady_clock::now();

	float dt = std::chrono::duration<float, std::milli>(timeAtThisFrame - timeAtLastFrame).count();
	float t = std::chrono::duration<float, std::milli>(timeAtThisFrame - timeAtLastFrame).count();
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

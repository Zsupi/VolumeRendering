#pragma once

#include "Scene.h"
namespace App {

	void onDisplay() {
		
		GlutApplication::getInstance()->onDisplay();
	}
	void onMouseMove(int pX, int pY) {
		
		GlutApplication::getInstance()->onMouseMove(pX, pY);
	}
	void onMouseClick(int button, int state, int pX, int pY) {
		
		GlutApplication::getInstance()->onMouseClick(button, state, pX, pY);
	}
	void onKeyboardDown(unsigned char key, int pX, int pY) {
		
		GlutApplication::getInstance()->onKeyboardDown(key, pX, pY);
	}
	void onKeyboardUp(unsigned char key, int pX, int pY) {
		
		GlutApplication::getInstance()->onKeyboardUp(key, pX, pY);
	}
	void onIdle() {
		GlutApplication::getInstance()->onIdle();
	}

	void onSpecialFunc(int key, int x, int y) {

		if (key == GLUT_KEY_UP) {
			GlutApplication::getInstance()->onKeyboardDown(GlutApplication::ARROW_UP_VALUE, x, y);
		}
		if (key == GLUT_KEY_DOWN) {
			GlutApplication::getInstance()->onKeyboardDown(GlutApplication::ARROW_DOWN_VALUE, x, y);
		}
		if (key == GLUT_KEY_RIGHT) {
			GlutApplication::getInstance()->onKeyboardDown(GlutApplication::ARROW_RIGHT_VALUE, x, y);
		}
		if (key == GLUT_KEY_LEFT) {
			GlutApplication::getInstance()->onKeyboardDown(GlutApplication::ARROW_LEFT_VALUE, x, y);
		}
	}

	void onInitialization(std::shared_ptr<Scene> scene, int argc, char* argv[]) {
		
		// Initialize GLUT, Glew and OpenGL 
		glutInit(&argc, argv);

		// OpenGL major and minor versions
		int majorVersion = 4, minorVersion = 3;
#if !defined(__APPLE__)
		glutInitContextVersion(majorVersion, minorVersion);
#endif
		glutInitWindowSize(GlutApplication::windowWidth, GlutApplication::windowHeight);				// Application window is initially of resolution 600x600
		glutInitWindowPosition(100, 100);							// Relative location of the application window
#if defined(__APPLE__)
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_4_3_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
#else
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif
		glutCreateWindow(argv[0]);

#if !defined(__APPLE__)
		glewExperimental = true;	// magic
		glewInit();
#endif
		printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
		printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
		printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
		printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
		printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


		GlutApplication::getInstance()->onInitialization(scene);

		glutDisplayFunc(App::onDisplay);
		glutMouseFunc(App::onMouseClick);
		glutIdleFunc(App::onIdle);
		glutKeyboardFunc(App::onKeyboardDown);
		glutKeyboardUpFunc(App::onKeyboardUp);
		glutMotionFunc(App::onMouseMove);
		glutSpecialFunc(App::onSpecialFunc);
		glutMainLoop();
	}

}

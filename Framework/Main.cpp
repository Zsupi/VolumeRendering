//#pragma once
//#include "App.h"
//
//// Entry point of the application
//int main(int argc, char* argv[]) {
//	// Initialize GLUT, Glew and OpenGL 
//	glutInit(&argc, argv);
//
//	// OpenGL major and minor versions
//	int majorVersion = 3, minorVersion = 3;
//#if !defined(__APPLE__)
//	glutInitContextVersion(majorVersion, minorVersion);
//#endif
//	glutInitWindowSize(GlutApplication::windowWidth, GlutApplication::windowHeight);				// Application window is initially of resolution 600x600
//	glutInitWindowPosition(100, 100);							// Relative location of the application window
//#if defined(__APPLE__)
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);  // 8 bit R,G,B,A + double buffer + depth buffer
//#else
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//#endif
//	glutCreateWindow(argv[0]);
//
//#if !defined(__APPLE__)
//	glewExperimental = true;	// magic
//	glewInit();
//#endif
//	printf("GL Vendor    : %s\n", glGetString(GL_VENDOR));
//	printf("GL Renderer  : %s\n", glGetString(GL_RENDERER));
//	printf("GL Version (string)  : %s\n", glGetString(GL_VERSION));
//	glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
//	glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
//	printf("GL Version (integer) : %d.%d\n", majorVersion, minorVersion);
//	printf("GLSL Version : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
//
//	
//	App::onInitialization();
//	
//	glutDisplayFunc(App::onDisplay);                
//	glutMouseFunc(App::onMouseClick);
//	glutIdleFunc(App::onIdle);
//	glutKeyboardFunc(App::onKeyboardDown);
//	glutKeyboardUpFunc(App::onKeyboardUp);
//	glutMotionFunc(App::onMouseMove);
//	glutMainLoop();
//	return 1;
//}
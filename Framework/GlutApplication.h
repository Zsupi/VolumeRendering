#pragma once
#include <memory>


class GlutApplication{

public:

	class GlutAppInterface {
		friend class GlutApplication;
		virtual void glutUpdate(float dt, float t) = 0;
		virtual void glutOnMouseMove(int pX, int pY) = 0;
		virtual void glutOnMouseClick(int button, int state, int pX, int pY) = 0;
		virtual void glutOnKeyboardDown(unsigned char key) = 0;
		virtual void glutOnKeyboardUp(unsigned char key) = 0;
		virtual void glutOnInitialization() = 0;
	};

private:
	std::shared_ptr<GlutAppInterface> scene;
	GlutApplication();

public:

	static const unsigned int windowWidth = 800, windowHeight = 800;

	static std::shared_ptr<GlutApplication> getInstance() {
		static std::shared_ptr<GlutApplication> instance(new GlutApplication);
		return instance;
	}

	GlutApplication(const GlutApplication&) = delete;
	GlutApplication& operator=(const GlutApplication&) = delete;
	
	virtual void onInitialization(std::shared_ptr<GlutAppInterface> scene);
	virtual void onDisplay();
	virtual void onMouseMove(int pX, int pY);
	virtual void onMouseClick(int button, int state, int pX, int pY);
	virtual void onKeyboardDown(unsigned char key, int pX, int pY);
	virtual void onKeyboardUp(unsigned char key, int pX, int pY);
	virtual void onIdle();
	
	virtual ~GlutApplication() {}

	

};

//todo virtualis destruktort csinalni majdnem minden osztalynak
//todo finalnak jelolni par osztalyt
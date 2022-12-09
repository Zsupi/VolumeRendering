#pragma once
#include <memory>
#include <chrono>

typedef std::chrono::steady_clock::time_point ChronoTime;

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

	static const char ARROW_UP_VALUE = '@';
	static const char ARROW_DOWN_VALUE = '#';
	static const char ARROW_RIGHT_VALUE = '~';
	static const char ARROW_LEFT_VALUE = '%';

private:


	std::shared_ptr<GlutAppInterface> scene;
	ChronoTime timeAtFirstFrame;
	ChronoTime timeAtLastFrame;

	int prevTime = 0;
	int crntTime = 0;
	int timeDiff;
	unsigned int frame = 0;

	GlutApplication();

public:

	static const unsigned int windowWidth = 600, windowHeight = 600;

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
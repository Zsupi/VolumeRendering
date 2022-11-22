#include <App.h>
#include "MyScene.h"

int main(int argc, char* argv[]) {
	std::shared_ptr<MyScene> scene = std::make_shared<MyScene>();
	App::onInitialization(scene, argc, argv);

	return 0;
}
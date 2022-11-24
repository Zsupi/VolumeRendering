#include <App.h>
#include "RayMarchingScene.h"
int main(int argc, char* argv[]) {
	std::shared_ptr<RayMarchingScene> scene = std::make_shared<RayMarchingScene>();
	App::onInitialization(scene, argc, argv);

	return 0;
}
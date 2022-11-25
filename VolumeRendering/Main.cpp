#include <App.h>
#include "RayMarchingScene.h"
#include "MetaballScene.h"

int main(int argc, char* argv[]) {
	//std::shared_ptr<RayMarchingScene> scene = std::make_shared<RayMarchingScene>();
	std::shared_ptr<MetaballScene> scene = std::make_shared<MetaballScene>();
	App::onInitialization(scene, argc, argv);

	return 0;
}
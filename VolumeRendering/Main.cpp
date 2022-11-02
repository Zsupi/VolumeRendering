#include <App.h>
#include "VolumeScene.h"
#include "DebugScene.h"

int main(int argc, char* argv[]) {
	std::shared_ptr<VolumeScene> scene = std::make_shared<VolumeScene>();
	//std::shared_ptr<DebugScene> scene = std::make_shared<DebugScene>();
	App::onInitialization(scene, argc, argv);
	return 0;
}
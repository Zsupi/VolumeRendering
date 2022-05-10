#include <App.h>
#include "VolumeScene.h"
int main(int argc, char* argv[]) {
	std::shared_ptr<VolumeScene> scene = std::make_shared<VolumeScene>();
	App::onInitialization(scene, argc, argv);

	return 0;
}
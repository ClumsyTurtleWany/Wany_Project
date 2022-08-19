#include "Engine.hpp"
#include "Core.hpp"
#define GameMode3D

int main()
{
	Engine* engine = Engine::getEngine();
	CoreBase* GameCore = engine->getCore();
	GameCore->run();

	return 0;
}
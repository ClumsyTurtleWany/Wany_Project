#include "Engine.hpp"
#include "Core.hpp"
#define GameMode3D

int main()
{
	Engine* engine = Engine::getEngine(CORE_TYPE::GAME_3D);
	CoreBase* GameCore = engine->getCore();
	GameCore->run();

	return 0;
}
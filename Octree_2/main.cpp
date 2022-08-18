#include "Engine.hpp"
#define GameMode3D

int main()
{
#ifdef GameMode3D
	Engine* engine = Engine::getEngine(CORE_TYPE::GAME_3D);
#else
	Engine* engine = Engine::getEngine(CORE_TYPE::GAME_2D);
#endif

	Core* GameCore = engine->getCore();
	GameCore->run();

	return 0;
}
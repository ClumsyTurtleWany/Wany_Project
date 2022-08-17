#include "Core3D.hpp"
#include "Core2D.hpp"

int main()
{
	/*Core* GameCore = new Core2D;
	GameCore->run();
	return 0;*/

	Core* GameCore = new Core3D;
	GameCore->run();
	return 0;
}
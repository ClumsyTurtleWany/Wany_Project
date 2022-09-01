#include "Engine.hpp"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    
    //Engine* engine = Engine::getEngine(CORE_TYPE::GAME_3D);
    ////Engine* engine = Engine::getEngine(CORE_TYPE::GAME_2D);
    //Core* GameCore = engine->getCore();
    //GameCore->run();

    ////WindowUI ui;
    //SampleShader ui;
    //ui.createWindow(hInstance, L"TestName", 1024, 768);
    //ui.run();
   
    Engine* engine = Engine::getEngine(CORE_TYPE::GAME_2D);
    engine->createWindow(hInstance, L"TestName", 1024, 768);
    engine->run();

    return 1;
}

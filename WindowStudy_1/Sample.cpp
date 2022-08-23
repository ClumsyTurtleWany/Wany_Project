#include "WindowUI.hpp"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    //WindowUI ui;
    TestUI ui;
    ui.createWindow(hInstance, L"Test Name", 1024, 768);
    ui.run();
   
    return 1;
}

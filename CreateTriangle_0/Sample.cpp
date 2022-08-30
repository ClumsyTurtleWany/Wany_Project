#include "SampleShader.hpp"


int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    //WindowUI ui;
    SampleShader ui;
    ui.createWindow(hInstance, L"TestName", 1024, 768);
    ui.run();
   
    return 1;
}

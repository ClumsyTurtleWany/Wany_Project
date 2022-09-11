#include "Sample.h"

// 2022-09-06

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample sampleWindow;
    sampleWindow.createWindow(hInstance, L"TestName", 1024, 768);
    sampleWindow.run();

    return 1;
}



bool Sample::initialize()
{
    srand(time(NULL));

    CollisionMap = new QuadTree<float>;
    Rect2f rect(0, 0, 1024, 768);
    CollisionMap->create(&rect);

    for (int i = 0; i < 50; i++)
    {
        objectBase* pObj = new object2D<float>;
        pObj->Random();
        pObj->createShader(ShaderType::Normal);

        objList.push_back(pObj);
        CollisionMap->addObject(pObj);
    }

    user = new object2D<float>;
    user->Random();
    user->createShader(ShaderType::Texture);
    if (DXTextureManager::getInstance()->Load(RSRC_BACKGROUND))
    {
        user->setTexture(DXTextureManager::getInstance()->getTexture(RSRC_BACKGROUND));
    }

    return true;
}

bool Sample::frame()
{
    CollisionMap->Collision(user, &renderList);
    return true;
}

bool Sample::render()
{
    //DXShaderManager::getInstance()->render();
    CollisionMap->render();

    for (auto it : objList)
    {
        it->setColor(Vector4f(0.0f, 1.0f, 0.0f, 1.0f));
        it->render();
    }

    for (auto it : renderList)
    {
        it->setColor(Vector4f(1.0f, 0.0f, 0.0f, 1.0f));
        it->render();
    }


    user->render();
    return true;
}

bool Sample::release()
{
    return true;
}
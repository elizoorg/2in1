#include "Core.h"

int Core::Run()
{
    bool _end = Init();
    while (_end) Loop();
    return 0;
}

bool Core::Init()
{
    return false;
}

bool Core::Update()
{
    return false;
}

bool Core::Draw()
{
    return false;
}

void Core::Loop()
{
    Update();
    Draw();
}

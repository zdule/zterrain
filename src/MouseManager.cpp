#include "MouseManager.h"

MouseManager::MouseManager()
{
    mouseLocation = glm::vec2(WINDOW_WITH/2,WINDOW_HEIGHT/2);
    speed = 0.006;
}

MouseManager::~MouseManager()
{
    //dtor
}

glm::vec2 MouseManager::getMouseLocation()
{
    return mouseLocation;
}

glm::vec2 MouseManager::getMouseMovement()
{
    return mouseMovement;
}

void MouseManager::onMotion(int x, int y, int xrel, int yrel)
{
    newMouseMovement += glm::vec2(xrel,yrel)*speed;
}

void MouseManager::onUpdate()
{
    mouseMovement = newMouseMovement;
    newMouseMovement = glm::vec2(0);
    mouseLocation += mouseMovement;
}

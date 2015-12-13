#include "Camera.h"

Camera::Camera(bool _isMain)
{
    isMain = _isMain;
    if(isMain)
    {
        game.matrixManager.setMode(matrixProjection);
        game.matrixManager.perspective(45,8/6,0.1,600);
    }
}

Camera::~Camera()
{

}

int Camera::onInit()
{
    position = glm::vec3(0.0);
    position.z = START_Y; position.x = START_X;
    horizontalAngle = 0;
    verticalAngle = 0;
    speed = float(1)/20;
    keyA = false; keyS = false; keyD = false; keyW = false; keyShift = false; keySpace = false;
    return 0;
}

void Camera::onRender()
{

}

void Camera::onUpdate(int delta)
{
    if(isMain)
    {
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 left;
        glm::vec3 move(0.0f);

        horizontalAngle -= game.mouseManager.getMouseMovement().x*delta;
        verticalAngle -= game.mouseManager.getMouseMovement().y*delta;

        float h = glm::radians(horizontalAngle+180);
        float v = glm::radians(verticalAngle);
        forward = glm::vec3(glm::cos(v) * glm::sin(h),glm::sin(v),glm::cos(v)*glm::cos(h));

        h = glm::radians(horizontalAngle+180);
        v = glm::radians(verticalAngle+90);
        up = glm::vec3(glm::cos(v) * glm::sin(h),glm::sin(v),glm::cos(v)*glm::cos(h));


        left = -glm::cross(forward,up);

        if(keyW)
            move+=forward;
        if(keyS)
            move-=forward;
        if(keyA)
            move+=left;
        if(keyD)
            move-=left;
        if(keySpace && !keyShift)
           move+=glm::vec3(0,1,0);
        if(keySpace && keyShift)
            move-=glm::vec3(0,1,0);

        if(move != glm::vec3(0,0,0))
            move = glm::normalize(move);
        position += move*(speed*delta);

        posX = int(position.x); posY = int(position.z);
        //position.y = getTerrain(position.x,position.z)+0.1;

        game.matrixManager.setMode(matrixView);
        game.matrixManager.lookAt(position,position+forward,up);
        game.matrixManager.setMatrixs();
    }
}

void Camera::onEvent(SDL_Event* event)
{
    bool state;
    if (event->type == SDL_KEYDOWN)
        state = true;
    else if (event->type == SDL_KEYUP)
        state = false;
    else
        return;

    if (event->key.keysym.sym == SDLK_a)
        keyA = state;
    if (event->key.keysym.sym == SDLK_s)
        keyS = state;
    if (event->key.keysym.sym == SDLK_d)
        keyD = state;
    if (event->key.keysym.sym == SDLK_w)
        keyW = state;
    if (event->key.keysym.sym == SDLK_SPACE)
        keySpace = state;

    if((SDL_GetModState() & KMOD_LSHIFT) > 0)
        keyShift = true;
    else
        keyShift = false;
}


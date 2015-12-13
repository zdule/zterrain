#ifndef CAMERA_H
#define CAMERA_H

#include "Game.h"
#include "Object.h"
#include <glm/glm.hpp>
#include "TerrainGenerator.h"

class Camera : public Object
{
    public:
        Camera(bool _isMain);
        virtual ~Camera();
        int onInit();
        void onRender();
        void onUpdate(int delta);
        void onEvent(SDL_Event* event);
        int posX, posY;
    protected:
    private:
        bool isMain;
        glm::vec3 position;
        float horizontalAngle;
        float verticalAngle;
        float speed;
        bool keyW, keyA, keyS, keyD, keySpace, keyShift;
};

#endif // CAMERA_H

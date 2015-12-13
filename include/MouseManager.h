#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H
#include <glm/glm.hpp>
#include "../Global.h"
class MouseManager
{
    public:
        MouseManager();
        virtual ~MouseManager();
        glm::vec2 getMouseLocation();
        glm::vec2 getMouseMovement();
        void onMotion(int x, int y, int xrel, int yrel);
        void onUpdate();
    protected:
    private:
        float speed;
        glm::vec2 mouseLocation;
        glm::vec2 mouseMovement;
        glm::vec2 newMouseMovement;
};

#endif // MOUSEMANAGER_H

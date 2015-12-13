#ifndef OBJECT_H
#define OBJECT_H

#include "SDL/SDL.h"
class Object
{
    public:
        Object();
        virtual ~Object();
        virtual int onInit() = 0;
        virtual void onRender() = 0;
        virtual void onUpdate(int delta) = 0;
        virtual void onEvent(SDL_Event* event);
    protected:
    private:
};

#endif // OBJECT_H

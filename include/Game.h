#ifndef GAME_H
#define GAME_H

#include <cstdio>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Object.h"
#include "../Global.h"
#include "Camera.h"
#include "Terrain.h"
#include "MatrixManager.h"
#include "MouseManager.h"
#include "../ShaderUtils.h"
class Camera;
class Terrain;
class Game
{
    public:
        Game();
        virtual ~Game();
        int onInit();
        void run();

        MatrixManager matrixManager;
        MouseManager mouseManager;

        Camera* camera;
        Terrain* terrain;

        GLuint getProgram();
    protected:
    private:
        void onRender();
        void onUpdate(int delta);
        void onEvent(SDL_Event* event);

        struct
        {
            GLuint program;
            struct
            {
                GLuint modelMatrix;
                GLuint viewMatrix;
                GLuint projectionMatrix;
            } uniforms;
        } resources;
        bool running;
        SDL_Surface *sdlDisplay;
};

extern Game game;
#endif // GAME_H

#ifndef TERRAINCHUNK_H
#define TERRAINCHUNK_H

#include "../Global.h"
#include "Game.h"
#include "glm/glm.hpp"
#include "math.h"
#include "TerrainGenerator.h"

class TerrainChunk : public Object
{
    public:
        TerrainChunk(int _x, int _y);
        virtual ~TerrainChunk();
        int onInit();
        void onRender();
        void onUpdate(int delta);
        void onEvent(SDL_Event* event);
    protected:
    private:
        float terrainData[(CHUNK_SIZE*CHUNK_SIZE)*3];
        GLuint elementData[(CHUNK_SIZE-1)*(CHUNK_SIZE-1)*2*3];
        struct
        {
            struct
            {
                GLuint color;
            }uniforms;
            GLuint vertexBuffer;
            GLuint vertexArray;
            GLuint elementBuffer;
        } resources;
        int posX, posY;
};

#endif // TERRAINCHUNK_H

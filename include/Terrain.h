#ifndef TERRAIN_H
#define TERRAIN_H

#include "TerrainChunk.h"
#include "../Global.h"
#include "Camera.h"

class TerrainChunk;
class Terrain : public Object
{
    public:
        Terrain();
        virtual ~Terrain();
        int onInit();
        void onRender();
        void onUpdate(int delta);
        void onEvent(SDL_Event* event);
    protected:
    private:
        void moveTerrain();
        int chunkX, chunkY;
        TerrainChunk* a[VIEW_DISTANCE][VIEW_DISTANCE];
        int chunkNum = VIEW_DISTANCE;
};

#endif // TERRAIN_H

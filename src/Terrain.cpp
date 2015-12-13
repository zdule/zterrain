#include "Terrain.h"

Terrain::Terrain()
{
    int _chunkX = START_X / CHUNK_SIZE, _chunkY = START_Y / CHUNK_SIZE;
    for(int i = 0; i < chunkNum; i++)
        for(int j = 0; j < chunkNum; j++)
            a[j][i] = new TerrainChunk(_chunkX-chunkNum/2+i,_chunkY-chunkNum/2+j);
}

Terrain::~Terrain()
{
    for(int i = 0; i < chunkNum; i++)
        for(int j = 0; j < chunkNum; j++)
            delete a[i][j];
}

int Terrain::onInit()
{
    chunkX = 0; chunkY = 0;
    for(int i = 0; i < chunkNum; i++)
        for(int j = 0; j < chunkNum; j++)
            a[i][j]->onInit();
}
void Terrain::onRender()
{
    for(int i = 0; i < chunkNum; i++)
        for(int j = 0; j < chunkNum; j++)
            a[i][j]->onRender();
}
void Terrain::moveTerrain()
{
    int _chunkX = game.camera->posX / CHUNK_SIZE, _chunkY = game.camera->posY / CHUNK_SIZE;

        if (_chunkY == chunkY+1) //moved forward;
        {
            for(int i = 0; i < chunkNum; i++)
                delete a[0][i];
            for(int i = 0; i < chunkNum-1; i++)
                for(int j = 0; j < chunkNum; j++)
                    a[i][j] = a[i+1][j];
            for(int i = 0; i < chunkNum; i++)
            {
                a[chunkNum-1][i] = new TerrainChunk(_chunkX-chunkNum/2+i,_chunkY+chunkNum/2-1);
                a[chunkNum-1][i]->onInit();
            }
        }
        if (_chunkY == chunkY-1) //moved backvard
        {
            for(int i = 0; i < chunkNum; i++)
                delete a[chunkNum-1][i];
            for(int i = chunkNum-1; i > 0; i--)
                for(int j = 0; j < chunkNum; j++)
                    a[i][j] = a[i-1][j];
            for(int i = 0; i < chunkNum; i++)
            {
                a[0][i] = new TerrainChunk(_chunkX-chunkNum/2+i,_chunkY-chunkNum/2);
                a[0][i]->onInit();
            }
        }
        if (_chunkX == chunkX+1) //moved left
        {
            for(int i = 0; i < chunkNum; i++)
                delete a[i][0];
            for(int i = 0; i < chunkNum-1; i++)
                for(int j = 0; j < chunkNum; j++)
                    a[j][i] = a[j][i+1];
            for(int i = 0; i < chunkNum; i++)
            {
                a[i][chunkNum-1] = new TerrainChunk(_chunkX+chunkNum/2-1,_chunkY-chunkNum/2+i);
                a[i][chunkNum-1]->onInit();
            }
        }
        if (_chunkX == chunkX-1) //moved right
        {
            for(int i = 0; i < chunkNum; i++)
                delete a[i][chunkNum-1];
            for(int i = chunkNum-1; i > 0; i--)
                for(int j = 0; j < chunkNum; j++)
                    a[j][i] = a[j][i-1];
            for(int i = 0; i < chunkNum; i++)
            {
                a[i][0] = new TerrainChunk(_chunkX-chunkNum/2,_chunkY-chunkNum/2+i);
                a[i][0]->onInit();
            }
        }

    chunkX = _chunkX; chunkY = _chunkY;
}
void Terrain::onUpdate(int x)
{
    moveTerrain();

    for(int i = 0; i < chunkNum; i++)
        for(int j = 0; j < chunkNum; j++)
            a[i][j]->onUpdate(x);
}
void Terrain::onEvent(SDL_Event* event)
{
    for(int i = 0; i < chunkNum; i++)
        for(int j = 0; j < chunkNum; j++)
            if (a[i][j] != NULL)
                a[i][j]->onEvent(event);
}

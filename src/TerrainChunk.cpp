#include "TerrainChunk.h"
void getError()
{
    GLenum error = glGetError();
    char* serror;
    switch(error)
    {
        case GL_INVALID_OPERATION:      serror="INVALID_OPERATION";      break;
        case GL_INVALID_ENUM:           serror="INVALID_ENUM";           break;
        case GL_INVALID_VALUE:          serror="INVALID_VALUE";          break;
        case GL_OUT_OF_MEMORY:          serror="OUT_OF_MEMORY";          break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:  serror="INVALID_FRAMEBUFFER_OPERATION";  break;
    }
    if(error != GL_NO_ERROR)
    {
        printf("error: %s\n",serror);
    }
}


TerrainChunk::TerrainChunk(int _x, int _y)
{
    posX = _x;
    posY = _y;
}

TerrainChunk::~TerrainChunk()
{
    //dtor
}

int TerrainChunk::onInit()
{
    glGenVertexArrays(1,&resources.vertexArray);
    glBindVertexArray(resources.vertexArray);

    for(int j = 0; j < CHUNK_SIZE; j++)
    {
        for(int i = 0; i < CHUNK_SIZE; i++)
        {
            terrainData[(j*CHUNK_SIZE+i)*3] = posX*(CHUNK_SIZE-1)+i;
            terrainData[(j*CHUNK_SIZE+i)*3+1] = getTerrain((posX*(CHUNK_SIZE-1)+i)*1.5,(posY*(CHUNK_SIZE-1)+j)*1.5);
            terrainData[(j*CHUNK_SIZE+i)*3+2] = posY*(CHUNK_SIZE-1)+j;
        }
    }

    for(int j = 0; j < CHUNK_SIZE-1; j++)
    {
        for(int i = 0; i < CHUNK_SIZE-1; i++)
        {
            int point = j*(CHUNK_SIZE-1)+i;
            elementData[(point*2)*3] = j*CHUNK_SIZE+i; elementData[(point*2)*3+1] = (j+1)*CHUNK_SIZE+i; elementData[(point*2)*3+2] = (j+1)*CHUNK_SIZE+i+1;
            elementData[(point*2+1)*3] = j*CHUNK_SIZE+i; elementData[(point*2+1)*3+1] = (j+1)*CHUNK_SIZE+i+1; elementData[(point*2+1)*3+2] = j*CHUNK_SIZE+i+1;
        }
    }

    glGenBuffers(1, &resources.vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(terrainData), terrainData, GL_STATIC_DRAW);

    glGenBuffers(1, &resources.elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resources.elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);

    resources.uniforms.color = glGetUniformLocation(game.getProgram(), "color");
    return 0;
}

void TerrainChunk::onRender()
{
    game.matrixManager.setMode(matrixModel);
    game.matrixManager.pushMatrix();
    game.matrixManager.setMatrixs();

    glBindVertexArray(resources.vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, resources.vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, resources.elementBuffer);

    glEnable(GL_POLYGON_OFFSET_LINE);

    glUniform4f(resources.uniforms.color,0,0,0,1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES,3*(CHUNK_SIZE-1)*(CHUNK_SIZE-1)*2,GL_UNSIGNED_INT, (void*)0);

    glPolygonOffset(-1.0f, -1.0f);
    glUniform4f(resources.uniforms.color,0,1,0,1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES,3*(CHUNK_SIZE-1)*(CHUNK_SIZE-1)*2,GL_UNSIGNED_INT, (void*)0);

    glDisable(GL_POLYGON_OFFSET_LINE);

    glDisableVertexAttribArray(0);

    game.matrixManager.setMode(matrixModel);
    game.matrixManager.popMatrix();
}

void TerrainChunk::onUpdate(int delta)
{

}

void TerrainChunk::onEvent(SDL_Event* event)
{

}

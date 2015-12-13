#include "Game.h"
Game game;
Game::Game()
{
    running = true;
    camera = new Camera(true);
    terrain = new Terrain();
}

Game::~Game()
{
    delete camera;
    delete terrain;
}

int Game::onInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if((sdlDisplay = SDL_SetVideoMode(WINDOW_WITH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL)
    {
        return false;
    }
    SDL_SetVideoMode(WINDOW_WITH, WINDOW_HEIGHT, 32,  /*SDL_FULLSCREEN | */SDL_OPENGL );
    SDL_ShowCursor(0);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
    }
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    resources.program = loadShaderProgram("test.vp","test.fp", 1,0,"position");
    glUseProgram(resources.program);
    resources.uniforms.modelMatrix = glGetUniformLocation(resources.program, "modelMatrix");
    resources.uniforms.viewMatrix = glGetUniformLocation(resources.program, "viewMatrix");
    resources.uniforms.projectionMatrix = glGetUniformLocation(resources.program, "projectionMatrix");
    game.matrixManager.setUniforms(resources.uniforms.modelMatrix,resources.uniforms.viewMatrix,resources.uniforms.projectionMatrix);

    camera->onInit();
    terrain->onInit();
    return 0;
}

void Game::onRender()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    terrain->onRender();

    SDL_GL_SwapBuffers();
}

void Game::run()
{
    int lastTick, now;
    now = SDL_GetTicks();
    lastTick = now-1;

    while(running)
    {
        now = SDL_GetTicks();

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            onEvent(&event);
        }
        onUpdate(now-lastTick);
        onRender();

        lastTick = now;
    }
}
void Game::onUpdate(int delta)
{
    mouseManager.onUpdate();

    camera->onUpdate(delta);
    terrain->onUpdate(delta);
}

void Game::onEvent(SDL_Event* event)
{
    camera->onEvent(event);
    terrain->onEvent(event);

    switch(event->type)
    {
        case SDL_KEYDOWN:
        {
            if(event->key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
        }
        case SDL_MOUSEMOTION:
        {
            mouseManager.onMotion(event->motion.x,event->motion.y,event->motion.xrel,event->motion.yrel);
            break;
        }
        case SDL_QUIT:
        {
            running = false;
            break;
        }
    }
}

GLuint Game::getProgram()
{
    return resources.program;
}

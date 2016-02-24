#include <cstdio>
#include <string>
#include <iostream>

#include "MainGame.h"
#include "Errors.h"
#include "GLSLProgram.h"

MainGame::MainGame()
{
    _window = nullptr; //Set to nullptr to handle exception of window not being created
    _screenWidth = 1024; //Temporarily hard-coded
    _screenHeight = 768; //Temporarily hard-coded
    _gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
    //dtor
}

void MainGame::run()
{
    initSystems();

    _sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

    gameLoop();
}

void MainGame::initSystems()
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize SDL
    _window = SDL_CreateWindow("Obake Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL); //Creates SDL window

    if(!_window)
    {
        fatalError("SDL_Window could not be created!");
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window); //Attach the SDL_GLContext to the SDL_Window
    if(!glContext)
    {
        fatalError("SDL_GLContext could not be created!");
    }

    GLenum error = glewInit(); //Initialize GLEW, fetching all of the necessary extensions
    if(error != GLEW_OK)
    {
        fatalError("Could not initialize GLEW!");
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Initializes the Double Buffer pattern

    glClearColor(0.0f, 0.0f, 1.0f, 1.0); //Set the color to be switched to with glClear() in drawGame()

    initShaders();
}

void MainGame::initShaders()
{
    _colorShaderProgram.compileShaders("shaders/colorShading.vert", "shaders/colorShading.frag");
    _colorShaderProgram.addAttribute("vertexPosition");
    _colorShaderProgram.linkShaders();
}

void MainGame::gameLoop()
{
    Uint32 previousTicks = SDL_GetTicks();
    Uint32 lag = 0;

    while(_gameState != GameState::EXIT)
    {
        Uint32 currentTicks = SDL_GetTicks();
        Uint32 elapsed = currentTicks - previousTicks;
        previousTicks = currentTicks;
        lag += elapsed;

        processInput();

        /*
        while(lag >= MS_PER_UPDATE)
        {
            update();
            lag -= MS_PER_UPDATE;
        }
        */

        render();
    }
}

void MainGame::processInput()
{
    SDL_Event inputEvent;
    while(SDL_PollEvent(&inputEvent))
    {
        switch(inputEvent.type)
        {
        case SDL_QUIT:
            {
                _gameState = GameState::EXIT;
                break;
            }
        case SDL_MOUSEMOTION:
            {
                printf("(%i, %i)\n", inputEvent.motion.x, inputEvent.motion.y); //Print the mouse coordinates (relative to the SDL_Window) to the console
                break;
            }
        }
    }
}

void MainGame::render()
{
    glClearDepth(1.0); //Sets OpenGL's clear depth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Each time the game is draw, the buffer is cleared

    _colorShaderProgram.use();

    _sprite.renderSprite();

    _colorShaderProgram.unuse();

    SDL_GL_SwapWindow(_window);
}

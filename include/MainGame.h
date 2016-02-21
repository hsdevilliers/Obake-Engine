#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <GL/glew.h>

/** \enum Various game states
 */
enum class GameState
{
    PLAY,
    EXIT
};

class MainGame
{
    public:
        MainGame();
        ~MainGame();

        /** \fn void run()
         *  Runs the initSystems() function.
         */
        void run();

    protected:

    private:
        /** \fn void initSystems()
         *  Initializes the various systems used in the game engine.
         */
        void initSystems();
        void gameLoop();
        void processInput();
        void drawGame();

        SDL_Window* _window; /**< Pointer to SDL_Window object that is initialized in the initSystems() function. */
        int _screenWidth; /**< Screen width of the window. */
        int _screenHeight; /**< Screen height of the window. */

        GameState _gameState;

};

#endif // MAINGAME_H

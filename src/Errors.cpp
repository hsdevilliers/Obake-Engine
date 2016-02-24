#include "Errors.h"

#include <cstdlib>

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdio>

void fatalError(std::string errorString)
{
    printf("%s\n", errorString.c_str());
    printf("A fatal error occurred!\nEnter any key to quit...\n");
    int tmp;
    std::cin >> tmp;

    SDL_Quit(); //SDL function that can quits all SDL functionality
    exit(1); //Exits the program with error code 1
}

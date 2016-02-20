#include <iostream>
#include <cstdio>

#include <MainGame.h>

int main(int argc, char** argv)
{
    MainGame mainGame;
    mainGame.run();

    printf("Enter any key to quit...\n");

    int tmp;
    std::cin >> tmp;

    return 0;
}

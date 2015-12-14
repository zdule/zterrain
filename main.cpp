#include "include/Game.h"
#include "Global.h"

int main(int argc, char* argv[])
{
    if(game.onInit())
        return 1;
    game.run();

    return 0;
}

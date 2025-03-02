#include "Game.h"   
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <glm/glm.hpp>
using namespace std;
int main()
{
    Player p(glm::vec2(5, 8),60);
    Game game(p);
    game.Start();

    return 0;
}


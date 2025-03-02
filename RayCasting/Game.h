#pragma once
#include "Player.h"
#include "Map.h"
#include <GLFW/glfw3.h>
#include "Renderer.h"

const int WIDTH = 2450;
const int HEIGHT = 1300;


class Game
{
public:
    Game(const Player& player);
    ~Game();
    void Start();
	void InputHandle();
private:
    Player player;
    GLFWwindow* window;
	Map map;
    Renderer renderer;
};
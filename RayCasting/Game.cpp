#include "Game.h"
#include <stdexcept>
Game::Game(const Player& player) : player(player), map("map.txt")
{
    if(!glfwInit())
    {
        throw std::runtime_error("cannot initialize glfw");
    }
    this->window =   glfwCreateWindow(WIDTH,HEIGHT,"Ray Casting", NULL, NULL);
    glfwMakeContextCurrent(this->window);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
   
}

Game::~Game()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::Start()
{
	
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		InputHandle();
		renderer.RenderGame(player, map);
        glfwSwapBuffers(window);
    }
    
}

void Game::InputHandle()
{
	glm::vec2 newPosition;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		newPosition = player.MoveForeward();
		if (!map.CheckColision(newPosition))
		{
			player.SetPosition(newPosition);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		newPosition =  player.MoveBackward();
		if (!map.CheckColision(newPosition))
		{
			player.SetPosition(newPosition);
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		player.MoveCameraLeft();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		player.MoveCameraRight();
	}
	
}

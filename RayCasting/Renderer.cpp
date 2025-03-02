#include "Renderer.h"
#include <cmath>
#include "Game.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
Renderer::Renderer()
{

}

void Renderer::RenderGame(Player& player, const Map& map)
{
	auto player_position = player.GetPosition();
	
	for (size_t x = 0; x < WIDTH; x++)
	{
		
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = player.GetDirection().x + player.GetPlane().x * cameraX;
		double rayDirY = player.GetDirection().y + player.GetPlane().y * cameraX;
		int mapX = int(player_position.x);
		int mapY = int(player_position.y);


		double sideDistX;
		double sideDistY;
		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
		int stepX;
		int stepY;
		bool hit = false;
		int side;


		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player_position.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player_position.x) * deltaDistX;

		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player_position.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player_position.y) * deltaDistY;

		}

		while (!hit)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY +=deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (map.GetAt(mapX,mapY) != 0 )
			{
				hit = true;
			}
		}
		double perpWallDist;
		if (side == 0)
		{
			perpWallDist = (mapX - player_position.x + (1 - stepX) / 2) / rayDirX; 
		}
		else
		{
			perpWallDist = (mapY - player_position.y + (1 - stepY) / 2) / rayDirY;  
		}
		float maxDistance = 30.0f; 
		float brightness = 1.0f - (perpWallDist / maxDistance);

		brightness = std::max(0.1f, std::min(brightness,1.0f));

		float r = 0, g = 0, b = 1;
		if (side == 0)
		{
			float finalR = r * brightness;
			float finalG = g * brightness;
			float finalB = b * brightness;
			glColor3f(finalR, finalG, finalB);
		}
		else
		{
			float shadow = 0.7f;
			glColor3f(r * brightness * shadow, g * brightness * shadow, b * brightness * shadow);
		}
		int lineHeight = (int)(HEIGHT / perpWallDist);
		
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
		glBegin(GL_LINES);
		glVertex2f(x,drawStart);
		glVertex2f(x, drawEnd);
		glEnd();
	}
	RenderMiniMap(player, map);
	
}

void Renderer::RenderMiniMap(Player& player,const Map& map)
{
	int cellSize = map.GetCellSize();
	auto position = player.GetPosition();
	auto direction = player.GetDirection();
	

	//grids
	for (int  y = 0; y < map.GetHeight(); y++)
	{
		for (int x = 0; x < map.GetWidth();x++) 
		{
			glColor3f(0.2, 0.8, 0.3);
			if (map.GetAt(x,y) == 0)
			{
				glColor3f(0, 0, 0);
			}
			
			glBegin(GL_QUADS);
			glVertex2f(x*cellSize,(y*cellSize) + cellSize);
			glVertex2f(x * cellSize + cellSize, (y * cellSize) + cellSize);
			glVertex2f(x * cellSize + cellSize, y * cellSize);
			glVertex2f(x * cellSize , y * cellSize);
			glEnd();
		}
	}
	//player
	glPointSize(cellSize / 4);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);

	glVertex2f(position.x * cellSize, position.y * cellSize);
	glEnd();

	float directionLength = 2.0f;
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(cellSize / 4);
	glBegin(GL_LINES);
	glVertex2f(position.x * cellSize, position.y * cellSize);
	glVertex2f((position.x + player.GetDirection().x * directionLength) * cellSize, (position.y + player.GetDirection().y * directionLength) * cellSize);
	glEnd();
	//mesh
	glLineWidth(2);
	for (size_t i = 0; i <= map.GetWidth(); i++)
	{
		glColor3f(0.5, 0.5, 0.5);
		glBegin(GL_LINES);
		glVertex2f(i*cellSize,0);
		glVertex2f(i * cellSize, map.GetHeight() * cellSize);
		glEnd();
	}
	for (size_t i = 0; i < map.GetHeight(); i++)
	{
		glBegin(GL_LINES);
		glVertex2f(0, i * cellSize);
		glVertex2f(map.GetWidth() * cellSize, i * cellSize);
		glEnd();
	}
}

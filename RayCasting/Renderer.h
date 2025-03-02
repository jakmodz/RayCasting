#pragma once
#include "Map.h"
#include "Player.h"
class Renderer
{
public:
	Renderer();
	void RenderGame(Player& player,const Map& map);
private:
	void RenderMiniMap(Player& player,const Map& map);
};


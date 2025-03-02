#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
Map::Map(const std::string& filePath)
{
	FILE* f;
	fopen_s(&f, filePath.c_str(), "r");
	if (f == NULL)
	{
		throw std::runtime_error("cannot open file map");
	}
	int width;
	int height;
	if (fscanf_s(f, "%d %d", &width, &height) != 2)
	{
		fclose(f);
		throw std::runtime_error("Invalid file format: Cannot read width and height");
	}
	this->height = height;
	this->width = width;
	this->map = new int[width * height];
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (fscanf_s(f,"%d",&map[y*width+x])!= 1)
			{

				fclose(f);
				throw std::runtime_error("Invalid file format: Not enough map values");
			}
		}
	}
}

Map::~Map()
{
	delete[] map;
}

int Map::GetCellSize()  const
{
	const float MAX_MINIMAP_SIZE = 1000.0f; 

	
	int maxDimension = std::max(width, height);

	return MAX_MINIMAP_SIZE / maxDimension;
}

int Map::GetWidth()const
{
	return width;
}

int Map::GetHeight() const
{
	return height;
}

int Map::GetAt(int x, int y) const
{
	return map[y*width+x];
}

bool Map::CheckColision(const glm::vec2& Position)
{
	if (GetAt(Position.x, Position.y) > 0)
	{
		return true;
	}
	return false;
}

#pragma once
#include <string>
#include <glm/glm.hpp>
class Map
{
public:
	Map(const std::string& filePath);
	~Map();
	int GetCellSize() const;
	int GetWidth()const ;
	int GetHeight() const;
	int GetAt(int x, int y)const ;
	bool CheckColision(const glm::vec2& newPosition);
private:
	int* map;
	int width;
	int height;

};


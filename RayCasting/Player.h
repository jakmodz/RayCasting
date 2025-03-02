#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Map.h"

const float ROTATION_SPEED = 0.01f;
const float MOVE_SPEED = 0.01f;
class Player
{
public:
    Player(glm::vec2 position,float angle = 0);

    const glm::vec2& GetPosition();
    const glm::vec2& GetDirection();
    const glm::vec2& GetPlane();

	void SetPosition(const glm::vec2& position);
	void SetDirection(const glm::vec2& direction);
	void SetPlane(const glm::vec2& plane);


    glm::vec2 MoveForeward();
    glm::vec2 MoveBackward();
    void MoveCameraLeft();
    void MoveCameraRight();

 
private:
    glm::vec2 position;
    glm::vec2 direction;
    glm::vec2 plane;
    
};
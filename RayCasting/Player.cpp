#include "Player.h"



Player::Player(glm::vec2 position, float angle): position(position)
{
	direction = glm::vec2(cos(angle), sin(angle));
	plane = glm::vec2(direction.y * 0.66, -direction.x * 0.66);
    
}

const glm::vec2& Player::GetPosition()
{
    return position;
}

const glm::vec2& Player::GetDirection()
{
    return direction;
}

const glm::vec2& Player::GetPlane()
{
	return plane;
}

void Player::SetPosition(const glm::vec2& position)
{
	this->position = position;
}

void Player::SetDirection(const glm::vec2& direction)
{
	this->direction = direction;
}

void Player::SetPlane(const glm::vec2& plane)
{
	this->plane = plane;
}

glm::vec2 Player::MoveForeward()
{
	glm::vec2 newPosition(position.x + (direction.x * MOVE_SPEED), position.y + (direction.y * MOVE_SPEED));
	return newPosition;
}

glm::vec2 Player::MoveBackward()
{
	glm::vec2 newPosition(position.x - (direction.x * MOVE_SPEED), position.y - (direction.y * MOVE_SPEED));
	return newPosition;
}

void Player::MoveCameraLeft()
{
	float oldDirX = direction.x;
	direction.x = direction.x * cos(ROTATION_SPEED) - direction.y * sin(ROTATION_SPEED);
	direction.y = oldDirX * sin(ROTATION_SPEED) + direction.y * cos(ROTATION_SPEED);

	float oldPlaneX = plane.x;
	plane.x = plane.x * cos(ROTATION_SPEED) - plane.y * sin(ROTATION_SPEED);
	plane.y = oldPlaneX * sin(ROTATION_SPEED) + plane.y * cos(ROTATION_SPEED);
}

void Player::MoveCameraRight()
{
	float oldDirX = direction.x;
	direction.x = direction.x * cos(-ROTATION_SPEED) - direction.y * sin(-ROTATION_SPEED);
	direction.y = oldDirX * sin(-ROTATION_SPEED) + direction.y * cos(-ROTATION_SPEED);

	float oldPlaneX = plane.x;
	plane.x = plane.x * cos(-ROTATION_SPEED) - plane.y * sin(-ROTATION_SPEED);
	plane.y = oldPlaneX * sin(-ROTATION_SPEED) + plane.y * cos(-ROTATION_SPEED);
	
}



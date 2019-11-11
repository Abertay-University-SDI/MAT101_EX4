#include "CollisionDetection.h"


bool Collision::CirclePoint(float circleRadius, const sf::Vector2f & circlePosition, const sf::Vector2f & pointPosition)
{
	sf::Vector2f circlePointVector = circlePosition - pointPosition;
	float distSquared = circlePointVector.x*circlePointVector.x + circlePointVector.y*circlePointVector.y;

	if (distSquared < circleRadius*circleRadius)
	{
		return true;
	}
	return false;
}
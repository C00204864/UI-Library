#include "MathUtility.h"

sf::Vector2f lerp(sf::Vector2f &startPos, sf::Vector2f &endPos, float interpolate)
{
	return sf::Vector2f((1.0f - interpolate) * startPos.x + (interpolate * endPos.x),
		(1.0f - interpolate) * startPos.y + (interpolate * endPos.y));
}
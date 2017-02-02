#include "MathUtility.h"

sf::Vector2f lerp(sf::Vector2f &startPos, sf::Vector2f &endPos, float interpolate)
{
	return sf::Vector2f(startPos.x + (endPos.x - startPos.x) * interpolate,
		startPos.y + (endPos.y - startPos.y) * interpolate);
}
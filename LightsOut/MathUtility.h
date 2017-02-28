/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef MATH_UTIL
#define MATH_UTIL

#include <SFML\Graphics.hpp>

/// <summary>
/// Simple utility for using a LERP function
/// </summary>
sf::Vector2f lerp(sf::Vector2f &startPos, sf::Vector2f &endPos, float interpolate);

#endif
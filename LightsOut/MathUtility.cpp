#include "MathUtility.h"

/// <summary>
/// Returns a position that is between start position and end position
/// based on the interpolate value form [0, 1]
/// </summary>
/// <param name="startPos">The inital start position</param>
/// <param name="endPos">The final target position</param>
/// <param name="interpolate">Number from [0, 1] of far along the transition is</param>
/// <returns>A position between start and end based on the interpolate value</returns>
sf::Vector2f lerp(sf::Vector2f &startPos, sf::Vector2f &endPos, float interpolate)
{
	return sf::Vector2f((1.0f - interpolate) * startPos.x + (interpolate * endPos.x),
		(1.0f - interpolate) * startPos.y + (interpolate * endPos.y));
}
/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <SFML\Graphics.hpp>

class ResourceManager
{
public:
	ResourceManager();

	sf::Font* getGameFont();

private:
	// The font used in our game Lights Out.
	sf::Font gameFont;
};

extern ResourceManager g_resourceMgr;

#endif
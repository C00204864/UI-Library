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
	sf::Texture* getStudioTexture();

private:
	// The font used in our game Lights Out.
	sf::Font m_gameFont;
	sf::Texture m_studioLogo;
};

extern ResourceManager g_resourceMgr;

#endif
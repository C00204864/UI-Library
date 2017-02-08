/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class ResourceManager
{
public:
	ResourceManager();

	sf::Font* getGameFont();
	sf::SoundBuffer* getBackingTrackBuffer();

private:
	// The font used in our game Lights Out.
	sf::Font gameFont;
	sf::SoundBuffer backingSoundBuffer;
};

extern ResourceManager g_resourceMgr;

#endif
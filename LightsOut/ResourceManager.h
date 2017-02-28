/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
/// <summary>
/// Brief: Loads all game assets
/// 
/// Detail: Loads game assets that are used in the game and provides
/// a method to return a pointer to the location in memory 
/// it's loaded
/// </summary>
class ResourceManager
{
public:
	ResourceManager();

	sf::Font* getGameFont();
	sf::Texture* getStudioTexture();
	sf::Texture* getBackgroundTexture();
	sf::SoundBuffer* getBackingTrackBuffer();
	sf::SoundBuffer* getSelectSoundBuffer();

private:
	sf::Font m_gameFont; // The font used in our game Lights Out
	sf::Texture m_studioLogo; // The logo used by the splash screen
	sf::Texture m_backgroundTexture; // The background texture of the game
	sf::SoundBuffer backingSoundBuffer; // The backing track used in the game
	sf::SoundBuffer selectSoundBuffer; // The button sound used in the game
};

extern ResourceManager g_resourceMgr;

#endif
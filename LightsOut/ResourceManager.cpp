#include "ResourceManager.h"

ResourceManager g_resourceMgr;

/// <summary>
/// Loads the asset resources.
/// </summary>
ResourceManager::ResourceManager()
{
	if (!gameFont.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		std::cout << "ResourceManager:: gameFont failed to load!" << std::endl;
	}
	if (!backingSoundBuffer.loadFromFile("Assets/Sounds/BackingTrack.wav"))
	{
		std::cout << "ResourceManager:: backingSoundBuffer failed to load!" << std::endl;
	}
}

/// <summary>
/// Gets the font loaded in memory
/// </summary>
/// <returns>Returns a pointer to the loaded font in memory</returns>
sf::Font* ResourceManager::getGameFont()
{
	return &gameFont;
}

/// <summary>
/// Gets the sound buffer loaded in memory
/// </summary>
/// <returns>Returns a pointer to the loaded sound buffer in memory</returns>
sf::SoundBuffer* ResourceManager::getBackingTrackBuffer()
{
	return &backingSoundBuffer;
}
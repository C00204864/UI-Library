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
}

/// <summary>
/// Gets the font loaded in memory
/// </summary>
/// <returns>Returns a pointer to the loaded font in memory</returns>
sf::Font* ResourceManager::getGameFont()
{
	return &gameFont;
}
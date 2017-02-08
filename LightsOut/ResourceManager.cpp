#include "ResourceManager.h"

ResourceManager g_resourceMgr;

/// <summary>
/// Loads the asset resources.
/// </summary>
ResourceManager::ResourceManager()
{
	if (!m_gameFont.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		std::cout << "ResourceManager:: gameFont failed to load!" << std::endl;
	}

	if (!m_studioLogo.loadFromFile("Assets/StudioLogo/StudioLogo.png"))
	{
		std::cout << "ResourceManager:: StudioLogo.png failed to load!" << std::endl;
	}
}

/// <summary>
/// Gets the font loaded in memory
/// </summary>
/// <returns>Returns a pointer to the loaded font in memory</returns>
sf::Font* ResourceManager::getGameFont()
{
	return &m_gameFont;
}

/// <summary>
/// Gets the studio logo image loaded in memory
/// </summary>
/// <returns>Returns a pointer to the loaded image in memory</returns>
sf::Texture* ResourceManager::getStudioTexture()
{
	return &m_studioLogo;
}
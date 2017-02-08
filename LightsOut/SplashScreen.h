/// <summary>
/// @author Darren Sweeney
/// @version 1.0
/// </summary>

#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"

/// <summary>
/// Handles all the functionality of the splash screen
/// 
/// Updates the fade in and out of the splash screen and renders
/// the assets. When the fade is finished the state is changed
/// </summary>
class SplashScreen
{
public:
	SplashScreen();

	void update(float dt);
	void render(sf::RenderWindow &window);
	bool splashOverState();

private:
	sf::Sprite m_studioLogoSprite;
	sf::Font *m_splashScreenFont;
	sf::Text m_legalText;
	sf::RectangleShape m_fadeCover;
	float m_fadeCoverAlpha;
	bool isSplashOver;
	float timer;
};

#endif // !SPLASH_SCREEN_H
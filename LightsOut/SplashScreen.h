/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "Input\XboxController.h"
#include "Screen.h"

/// <summary>
/// Brief: Handles all the functionality of the splash screen
/// 
/// Detail: Updates the fade in and out of the splash screen and
/// renders the assets. When the fade is finished the state is 
/// changed
/// </summary>
class SplashScreen : public Screen
{
public:
	SplashScreen();

	void update(XboxController &xboxController) override;
	void render(sf::RenderWindow &window) override;
	bool splashOverState();
	void reset() override;

private:
	sf::Sprite m_studioLogoSprite; // Logo sprite
	sf::Font *m_splashScreenFont; // Font used by the splash screen
	sf::Text m_legalText; // Text drawn by the splash screen
	sf::RectangleShape m_fadeCover; // Rectangle drawn and used for fading
	float m_fadeCoverAlpha; // Alpha value of the fade rectangle
	float timer;
	const float FADE_RATE = 1.5f;
	bool isSplashOver; // bool determines if the splash animation has ben completed
};

#endif // !SPLASH_SCREEN_H
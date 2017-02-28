#include "SplashScreen.h"

/// <summary>
/// Gets the font and texture from the resource manangers and inialises them
/// both along with the fade rectangle
/// </summary>
SplashScreen::SplashScreen()
	: Screen(GameState::SplashScreen),
	m_fadeCoverAlpha(255)
{
	sf::Texture *studioTexture = g_resourceMgr.getStudioTexture();

	m_studioLogoSprite.setTexture(*studioTexture);
	m_studioLogoSprite.setOrigin(sf::Vector2f(m_studioLogoSprite.getLocalBounds().width / 2, 
							m_studioLogoSprite.getLocalBounds().height / 2));
	m_studioLogoSprite.setPosition(sf::Vector2f(400.0f, 350.0f));

	m_splashScreenFont = g_resourceMgr.getGameFont();
	m_legalText.setFont(*m_splashScreenFont);
	m_legalText.setCharacterSize(15);
	m_legalText.setString("Copyright (c) 2017 Peter Lowe Studios. All rights reserved");
	m_legalText.setPosition(sf::Vector2f(10.0f, 770.0f));

	m_fadeCover.setSize(sf::Vector2f(800.0f, 800.0));
}

/// <summary>
/// Checks if the splash screen is over so we can move to the main menu
/// </summary>
/// <returns>Returns the state of the splash screen</returns>
bool SplashScreen::splashOverState()
{
	return isSplashOver;
}

/// <summary>
/// The update method for the splash screen
/// </summary>
/// <param name="dt">Delta time</param>
void SplashScreen::update(XboxController &xboxController)
{
	timer += 20; // Increment the timer

	m_fadeCover.setFillColor(sf::Color(0, 0, 0, m_fadeCoverAlpha)); // Set the fade cover's alpha value

	if (timer < 6000.0f)
	{
		if (m_fadeCoverAlpha >= FADE_RATE)
		{
			m_fadeCoverAlpha -= FADE_RATE; // Decrementing thye fade alpha
			if (m_fadeCoverAlpha < 0)
			{
				m_fadeCoverAlpha = 0; // We do not want this value to go under 0
			}
		}
	}
	else
	{
		if (m_fadeCoverAlpha < 255)
		{
			m_fadeCoverAlpha += FADE_RATE; // Incrementing the fade alpha
			if (m_fadeCoverAlpha > 255)
			{
				m_fadeCoverAlpha = 255; // We do not want this value to go over 255
			}
		}
		else
		{
			m_nextGameState = GameState::MainMenu; // Change the game state
		}
	}

	// Skip the splash screen is the player presses start on the controller
	if (xboxController.isButtonPressed(XBOX360_START))
	{
		m_nextGameState = GameState::MainMenu;
	}
}

/// <summary>
/// Renders the splash screen logo and text along with the fade rectangle
/// </summary>
/// <param name="window">The window to render all splash screen objects</param>
void SplashScreen::render(sf::RenderWindow &window)
{
	window.draw(m_studioLogoSprite); // Draw the logo sprite
	window.draw(m_legalText); // Draw the legal Text
	window.draw(m_fadeCover); // Draw the alpha fade cover
}

/// <summary>
/// Function used to reset the screen if it to be used again after the game state has been changed
/// </summary>
void SplashScreen::reset()
{
	m_fadeCoverAlpha = 255; // Reset the fade cover
}
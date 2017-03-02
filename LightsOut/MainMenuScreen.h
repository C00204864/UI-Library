/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include <SFML\Graphics.hpp>
#include "Input\XboxController.h"
#include "Gui\Gui.h"
#include "Gui\Button.h"
#include "Gui\Label.h"
#include "Screen.h"

/// <summary>
/// Brief: class represents the screen for the main menu of the game
///
/// Detail: Class is used to decide what happens in the main menu state
/// of the game
/// </summary>
class MainMenuScreen : public Screen
{
public:
	MainMenuScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSound);
	void update(XboxController& controller) override;
	void render(sf::RenderWindow & window) override;
	void reset() override;

private:
	void playButtonSelected();
	void optionsButtonSelected();
	void quitButtonSelected();

	// GUI elements
	Label *m_gameTitle;
	Button *m_playButton;
	Button *m_optionsButton;
	Button *m_quitButton;

	// Rectangle and variables used for screen fading
	sf::RectangleShape m_fadeRectangle;
	float m_alphaFadeValue;
	const float FADE_RATE = 1.5f;

	// Linked to Callbacks
	bool playButtonPressed;
	bool optionsButtonPressed;
	bool quitButtonPressed;

	// Used in the transition of the screen
	bool transitionIn;
	float interpolation;

	// Assets
	sf::Sound &selectSound;
	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;
};

#endif
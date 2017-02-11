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
#include <iostream>

class MainMenuScreen
{
public:
	MainMenuScreen(sf::Sound &selectSound);

	void initialise();
	void update(XboxController& controller);
	void render(sf::RenderWindow& window);
	bool getChangeStateGamePlay();
	bool getChangeStateOptions();
	bool getChangeStateQuit();
	void reset();

private:
	void playButtonSelected();
	void optionsButtonSelected();
	void quitButtonSelected();

	Gui m_gui;
	Label *m_gameTitle;
	Button *m_playButton;
	Button *m_optionsButton;
	Button *m_quitButton;
	sf::RectangleShape m_fadeRectangle;
	float m_alphaFadeValue;
	const float FADE_RATE = 1.5f;

	bool playButtonPressed;
	bool optionsButtonPressed;
	bool quitButtonPressed;
	bool m_changeToGamePlayState;
	bool changeToOptionsState;
	bool changeToQuitState;

	bool transitionIn;
	float interpolation;

	sf::Sound &selectSound;
};

#endif
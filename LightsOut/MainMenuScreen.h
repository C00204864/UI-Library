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
	MainMenuScreen();

	void initialise();
	void update(XboxController& controller);
	void render(sf::RenderWindow& window);
	bool getChangeStateOptions();
	void reset();

	Gui m_gui;
	Label *m_gameTitle;
	Button *m_playButton;
	Button *m_optionsButton;
	Button *m_quitButton;

private:
	void playButtonSelected();
	void optionsButtonSelected();
	void quitButtonSelected();

	bool playButtonPressed;
	bool optionsButtonPressed;
	bool quitButtonPressed;
	bool changeToOptionsState;

	bool transitionIn;
	float interpolation;
};

#endif
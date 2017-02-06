/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef QUIT_SCREEN_H
#define QUIT_SCREEN_H

#include <SFML\Graphics.hpp>
#include "Input\XboxController.h"
#include "Gui\Gui.h"
#include "Gui\Button.h"
#include "Gui\Label.h"
#include <iostream>

class QuitScreen
{
public:
	QuitScreen();

	void initialise();
	void update(XboxController& controller);
	void render(sf::RenderWindow& window);
	bool getChangeStateMenu();
	bool getExitGameState();
	void reset();

private:
	void noButtonSelected();
	void yesButtonSelected();

	Gui m_gui;
	Label *m_quitTitle;
	Button *m_yesButton;
	Button *m_noButton;

	bool m_noButtonSelected;
	bool m_yesButtonSelected;
	bool m_changeToMenuState;
	bool m_exitGame;

	bool transitionIn;
	float interpolation;
};

#endif
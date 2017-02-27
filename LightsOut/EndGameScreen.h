/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef ENDGAMESCREEN_H
#define ENDGAMESCREEN_H

#include "Input\XboxController.h"
#include "Gui\Gui.h"
#include "Gui\Button.h"
#include "Gui\Label.h"
#include "Screen.h"

/// <summary>
/// Brief: class represents the screen for the win state of the game
/// 
/// Detail: class used to decide what happens after the game has been
/// beaten
/// </summary>
class EndGameScreen : public Screen
{
public:
	EndGameScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSound);
	void update(XboxController& controller) override;
	void reset() override;
private:
	bool transitionIn;
	float interpolation;
	void toMenu();
	void toQuit();
	bool transitionOut();
	bool m_changeStateMenu;
	bool m_changeStateQuit;

	// GUI Objects
	Label * m_gameOverLabel;
	Button * m_menuButton;
	Button * m_quitButton;
};

#endif

/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <sstream>
#include <SFML\Graphics.hpp>
#include "Input\XboxController.h"
#include "Gui\Gui.h"
#include "Gui\Slider.h"
#include "Gui\Button.h"
#include "Gui\RadioButton.h"
#include "Gui\CheckBox.h"
#include "Screen.h"

/// Brief: Class represents the Game Play Screen
/// 
/// Detail: Class provides an update and a render for the Lights Out(tm) game
class GamePlay : public Screen
{
public:
	GamePlay(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSound, int &difficultyIn);
	~GamePlay();
	void init(int gridSize);
	void update(XboxController& controller) override;
	void reset();

	Label *m_timeLabel;
	Label *m_movesLabel;
	CheckBox **m_pcheckBoxArray;
private:
	//Private Functions
	void initArray(int gridSize);
	void switchArea();
	void selectedUp();
	void selectedDown();
	void selectedLeft();
	void selectedRight();
	sf::Vector2f posCalc(float gridSize, int i);
	bool checkWin();

	// Constants and Variables
	const std::string MOVES = "Moves: ";
	const std::string TIME = "Time: ";
	const int SPACING = 60;
	const int INIT_X = 225;
	const int INIT_Y = 120;
	const int BUTTON_SIZE_NUMERATOR = 300;
	int selectedIndex;
	int arrayLength;
	int gridSize;
	int m_moves;
	int m_timeInSeconds;
	sf::Clock timeTotal;
	bool m_playerWon;
	bool transitionIn;
	float interpolation;

	// References to sounds, colors and game difficulty
	sf::Sound &selectSound;
	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;
	int &m_difficulty;
};

#endif
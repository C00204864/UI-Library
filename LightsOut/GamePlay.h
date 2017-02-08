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


class GamePlay {
public:
	GamePlay();
	~GamePlay();
	void init(int gridSize);
	void update(XboxController& controller);
	void render(sf::RenderWindow& window);
	Gui m_gui;
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

	float interpolation;
	bool transitionIn;
};

#endif

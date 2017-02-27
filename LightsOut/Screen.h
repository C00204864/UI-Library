#ifndef SCREEN_H
#define SCREEN_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Input\XboxController.h"
#include "Gui\Gui.h"
#include "Gui\Slider.h"
#include "Gui\Button.h"
#include "Gui\RadioButton.h"
#include "Gui\CheckBox.h"

///  General screen class inherited by all objects of type screen
///
/// Handles general functionality of the in game screens like drawing etc.
enum class GameState
{
	SplashScreen,
	MainMenu,
	Options,
	Quit,
	GamePlay,
	EndGameState
};

/// <summary>
/// Screen class is an abstarction for all of the screen objects eg: OptionsScreen
/// </summary>
class Screen
{
public:
	Screen(GameState gameStateIn);
	virtual void update(XboxController& controller) = 0;
	virtual void render(sf::RenderWindow& window);
	GameState getGameState();
	GameState getNextGameState();
	void resetNextGameState();
	void setColors();
	virtual void reset() = 0;
protected:
	GameState m_gameState;
	GameState m_nextGameState;
	Gui m_gui;
};

#endif


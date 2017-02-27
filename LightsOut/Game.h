/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "ResourceManager.h"
#include "MainMenuScreen.h"
#include "OpitionsScreen.h"
#include "QuitScreen.h"
#include "GamePlay.h"
#include "EndGameScreen.h"
#include "SplashScreen.h"
#include "ScreenManager.h"

/// <summary>
/// Brief: Game class used to run the game
/// 
/// Detail: Game class used to regulate the
/// update and render functions of the game
/// </summary>
class Game
{
public:
	Game(); // Constructor
	void run();
protected:
	// Protected Functions
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	sf::RenderWindow m_window; // Window used for rendering
	XboxController xboxController; // Controller used to process game input
	
	// Game Colors
	sf::Color m_focusColor;
	sf::Color m_noFocusColor;
	sf::Color m_fillColor;

	// Game Difficulty
	int m_difficulty;

	// Screens used in the game
	SplashScreen  * splashScreen;
	MainMenuScreen * mainMenuScreen;
	OptionsScreen * optionsScreen;
	QuitScreen * quitScreen;
	GamePlay * gamePlayScreen;
	EndGameScreen * endScreen;
	ScreenManager m_screenManager;

	// Sound Assets
	sf::Sound m_backingTrack;
	sf::Sound m_selectSound;
};

#endif
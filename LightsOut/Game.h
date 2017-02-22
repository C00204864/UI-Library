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
#include "SplashScreen.h"

/// 
/// 
/// 
class Game
{
public:
	Game();
	void run();

protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	sf::RenderWindow m_window;

	enum class GameState
	{
		SplashScreen,
		MainMenu,
		Options,
		Quit,
		GamePlay,
		EndGameState
	};
	GameState currentGameState = GameState::SplashScreen;

	XboxController xboxController;
	

	sf::Color m_focusColor;
	sf::Color m_noFocusColor;
	sf::Color m_fillColor;

	SplashScreen splashScreen;
	MainMenuScreen mainMenuScreen;
	OptionsScreen optionsScreen;
	QuitScreen quitScreen;
	GamePlay gamePlayScreen;

	sf::Sound m_backingTrack;
	sf::Sound m_selectSound;
};

#endif
/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "ResourceManager.h"
#include "MainMenuScreen.h"
#include "OpitionsScreen.h"
#include "GamePlay.h"

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
		MainMenu,
		Options,
		GamePlay
	};
	GameState currentGameState = GameState::GamePlay;

	XboxController xboxController;
	
	MainMenuScreen mainMenuScreen;
	OptionsScreen optionsScreen;
	GamePlay gamePlayScreen;
};

#endif
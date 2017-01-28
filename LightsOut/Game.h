#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "OpitionsScreen.h"

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
		Options,
		GamePlay
	};
	GameState currentGameState = GameState::Options;

	XboxController xboxController;
	OptionsScreen optionsScreen;
};

#endif
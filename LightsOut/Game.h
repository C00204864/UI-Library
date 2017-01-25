#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>

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
		GamePlay
	};

	GameState currentGameState = GameState::GamePlay;
};

#endif
#include "Game.h"
#include <iostream>

/// <summary>
/// 
/// </summary>
Game::Game()
	: m_window(sf::VideoMode(800, 800, 32), "Lights Out!", sf::Style::Default),
	xboxController(CONTROLLER_ONE)
{
	mainMenuScreen.initialise();
	optionsScreen.initialise();
	gamePlayScreen.init(7);
}

/// <summary>
/// 
/// </summary>
void Game::run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Clock clock;
	timeSinceLastUpdate = clock.restart();

	while (m_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds());
			timeSinceLastUpdate = sf::Time::Zero;
		}
		render();
	}
}

/// <summary>
/// 
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="event"></param>
void Game::processGameEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_window.close();
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void Game::update(double dt)
{
	switch (currentGameState)
	{
		case GameState::MainMenu:
		{
			mainMenuScreen.update(xboxController);

			if (mainMenuScreen.getChangeStateOptions())
			{
				currentGameState = GameState::Options;
				mainMenuScreen.reset();
			}

			break;
		}

		case GameState::Options:
		{
			optionsScreen.update(xboxController);

			if (optionsScreen.getChangeStateMenu())
			{
				currentGameState = GameState::MainMenu;
				optionsScreen.reset();
			}

			break;
		}

		case GameState::GamePlay:
		{
			
			gamePlayScreen.update(xboxController);
			break;
		}

		default:
			break;
	}
}

/// <summary>
/// 
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	switch (currentGameState)
	{
		case GameState::MainMenu:
		{
			mainMenuScreen.render(m_window);

			break;
		}

		case GameState::Options:
		{
			optionsScreen.render(m_window);

			break;
		}

		case GameState::GamePlay:
		{
			gamePlayScreen.render(m_window);

			break;
		}

		default:
			break;
	}

	m_window.display();
}
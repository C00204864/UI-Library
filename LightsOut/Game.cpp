#include "Game.h"
#include <iostream>

/// <summary>
/// 
/// </summary>
Game::Game()
	: m_window(sf::VideoMode(800, 800, 32), "Lights Out!", sf::Style::Close),
	xboxController(CONTROLLER_ONE),
	m_focusColor(sf::Color::Red),
	m_noFocusColor(sf::Color::Blue),
	m_fillColor(sf::Color::Green),
	mainMenuScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound),
	optionsScreen(m_focusColor, m_noFocusColor, m_fillColor, m_backingTrack, m_selectSound),
	quiteScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound),
	gamePlayScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound)

{
	m_backingTrack.setBuffer(*g_resourceMgr.getBackingTrackBuffer());
	m_selectSound.setBuffer(*g_resourceMgr.getSelectSoundBuffer());

	mainMenuScreen.initialise();
	optionsScreen.initialise();
	quiteScreen.initialise();
	gamePlayScreen.init(10);
	m_backingTrack.setLoop(true);
	m_backingTrack.play();
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
		case GameState::SplashScreen:
		{
			splashScreen.update(dt, xboxController);

			if (splashScreen.splashOverState())
			{
				currentGameState = GameState::MainMenu;
			}

			break;
		}

		case GameState::MainMenu:
		{
			mainMenuScreen.update(xboxController);

			if (mainMenuScreen.getChangeStateGamePlay())
			{
				currentGameState = GameState::GamePlay;
				mainMenuScreen.reset();
			}
			else if (mainMenuScreen.getChangeStateOptions())
			{
				currentGameState = GameState::Options;
				mainMenuScreen.reset();
			}
			else if (mainMenuScreen.getChangeStateQuit())
			{
				currentGameState = GameState::Quit;
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

		case GameState::Quit:
		{
			quiteScreen.update(xboxController);

			if (quiteScreen.getChangeStateMenu())
			{
				currentGameState = GameState::MainMenu;
				quiteScreen.reset();
			}
			else if (quiteScreen.getExitGameState())
			{
				m_window.close();
			}

			break;
		}

		case GameState::GamePlay:
		{
			gamePlayScreen.update(xboxController);

			if(xboxController.isButtonPressed(XBOX360_BACK))
			{
				currentGameState = GameState::MainMenu;
			}

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
		case GameState::SplashScreen:
		{
			splashScreen.render(m_window);

			break;
		}

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

		case GameState::Quit:
		{
			quiteScreen.render(m_window);

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
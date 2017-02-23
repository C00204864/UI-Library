#include "Game.h"
#include <iostream>

/// <summary>
/// 
/// </summary>
Game::Game()
	: m_window(sf::VideoMode(800, 800, 32), "Lights Out!", sf::Style::Close),
	xboxController(CONTROLLER_ONE),
	m_focusColor(sf::Color(166, 98, 75, 255)),
	m_noFocusColor(sf::Color(114, 53, 68, 255)),
	m_fillColor(sf::Color(65, 138, 108, 155)),
	mainMenuScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound),
	optionsScreen(m_focusColor, m_noFocusColor, m_fillColor, m_backingTrack, m_selectSound),
	quitScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound),
	gamePlayScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound)

{
	m_backingTrack.setBuffer(*g_resourceMgr.getBackingTrackBuffer());
	m_selectSound.setBuffer(*g_resourceMgr.getSelectSoundBuffer());
	m_backgroundSprite.setTexture(*g_resourceMgr.getBackgroundTexture());

	mainMenuScreen.initialise();
	optionsScreen.initialise();
	quitScreen.initialise();
	gamePlayScreen.init(3);
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
/// Updates the screen state bassed on the current game state
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
				std::cout << optionsScreen.getDifficulty();
				gamePlayScreen.reset(optionsScreen.getDifficulty());
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
			quitScreen.update(xboxController);

			if (quitScreen.getChangeStateMenu())
			{
				currentGameState = GameState::MainMenu;
				quitScreen.reset();
			}
			else if (quitScreen.getExitGameState())
			{
				m_window.close();
			}

			break;
		}

		case GameState::GamePlay:
		{
			if(xboxController.isButtonPressed(XBOX360_BACK))
			{
				currentGameState = GameState::MainMenu;
				gamePlayScreen.reset(optionsScreen.getDifficulty());
			}

			gamePlayScreen.update(xboxController);

			if (gamePlayScreen.hasPlayerWon())
			{
				currentGameState = GameState::EndGameState;
			}

			break;
		}

		case GameState::EndGameState:
		{
			break;
		}

		default:
			break;
	}
}

/// <summary>
/// Renders the current game screen based on the current game state
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
			m_window.draw(m_backgroundSprite);
			mainMenuScreen.render(m_window);

			break;
		}

		case GameState::Options:
		{
			m_window.draw(m_backgroundSprite);
			optionsScreen.render(m_window);

			break;
		}

		case GameState::Quit:
		{
			m_window.draw(m_backgroundSprite);
			quitScreen.render(m_window);

			break;
		}

		case GameState::GamePlay:
		{
			m_window.draw(m_backgroundSprite);
			gamePlayScreen.render(m_window);

			break;
		}

		case GameState::EndGameState:
		{
			break;
		}

		default:
			break;
	}

	m_window.display();
}
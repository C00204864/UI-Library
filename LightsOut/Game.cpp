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
	m_difficulty(3),
	mainMenuScreen(new MainMenuScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound)),
	optionsScreen(new OptionsScreen(m_focusColor, m_noFocusColor, m_fillColor, m_backingTrack, m_selectSound, m_difficulty)),
	quitScreen(new QuitScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound)),
	gamePlayScreen(new GamePlay(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound, m_difficulty)),
	splashScreen(new SplashScreen())

{
	m_backingTrack.setBuffer(*g_resourceMgr.getBackingTrackBuffer());
	m_selectSound.setBuffer(*g_resourceMgr.getSelectSoundBuffer());
	m_backgroundSprite.setTexture(*g_resourceMgr.getBackgroundTexture());

	mainMenuScreen->initialise();
	optionsScreen->initialise();
	quitScreen->initialise();
	gamePlayScreen->init(3);
	m_backingTrack.setLoop(true);
	m_backingTrack.play();
	m_screenManager.add(mainMenuScreen);
	m_screenManager.add(optionsScreen);
	m_screenManager.add(gamePlayScreen);
	m_screenManager.add(quitScreen);
	m_screenManager.add(splashScreen);
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
	m_screenManager.update(xboxController);
}

/// <summary>
/// Renders the current game screen based on the current game state
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_screenManager.render(m_window);
	m_window.display();
}
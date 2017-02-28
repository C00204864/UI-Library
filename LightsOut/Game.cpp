#include "Game.h"
#include <iostream>

/// <summary>
/// Default constructor function for the Game class
/// </summary>
Game::Game()
	: m_window(sf::VideoMode(800, 800, 32), "Lights Out!", sf::Style::Close), // Set up the render window
	xboxController(CONTROLLER_ONE), // Set up the xbox controller for input
	// Set up the colors
	m_focusColor(sf::Color(166, 98, 75, 255)),
	m_noFocusColor(sf::Color(114, 53, 68, 255)),
	m_fillColor(sf::Color(65, 138, 108, 155)),
	m_difficulty(3), // Set the difficulty
	// Set the screns
	mainMenuScreen(new MainMenuScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound)),
	optionsScreen(new OptionsScreen(m_focusColor, m_noFocusColor, m_fillColor, m_backingTrack, m_selectSound, m_difficulty)),
	quitScreen(new QuitScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound, m_window)),
	gamePlayScreen(new GamePlay(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound, m_difficulty)),
	endScreen(new EndGameScreen(m_focusColor, m_noFocusColor, m_fillColor, m_selectSound)),
	splashScreen(new SplashScreen())

{
	// Set up the sounds to be played
	m_backingTrack.setBuffer(*g_resourceMgr.getBackingTrackBuffer());
	m_selectSound.setBuffer(*g_resourceMgr.getSelectSoundBuffer());
	m_backingTrack.setLoop(true);
	m_backingTrack.play();

	// Initialise the game play screen with difficulty
	gamePlayScreen->init(m_difficulty);

	// Add the screens to the screen manager
	m_screenManager.add(mainMenuScreen);
	m_screenManager.add(optionsScreen);
	m_screenManager.add(gamePlayScreen);
	m_screenManager.add(quitScreen);
	m_screenManager.add(splashScreen);
	m_screenManager.add(endScreen);
}

/// <summary>
/// run function handles the update and render cycles of the game
/// </summary>
void Game::run()
{
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f); // Set to 60fps
	sf::Clock clock;
	timeSinceLastUpdate = clock.restart();

	// Game Loop
	while (m_window.isOpen())
	{
		processEvents();

		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			update(timeSinceLastUpdate.asMilliseconds()); // Call an update
			timeSinceLastUpdate = sf::Time::Zero; // Reset the time since last update
		}
		render(); // Call a render
	}
}

/// <summary>
/// Functionused to handle any in game events
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) // Check for any events
	{
		if (event.type == sf::Event::Closed) // If there was a close event
		{
			m_window.close(); // Close the window
		}
		processGameEvents(event);
	}
}

/// <summary>
/// Processes other in game events
/// </summary>
/// <param name="event">sfml event</param>
void Game::processGameEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) // If the escape key was pressed
	{
		m_window.close(); // Close the window
	}
}

/// <summary>
/// Updates the screen state bassed on the current game state
/// </summary>
/// <param name="dt"></param>
void Game::update(double dt)
{
	m_screenManager.update(xboxController); // Update the scren manager
}

/// <summary>
/// Renders the current game screen based on the current game state
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0)); // Clear the window
	m_screenManager.render(m_window); // Render the screen manager
	m_window.display(); // Display all draw calls
}
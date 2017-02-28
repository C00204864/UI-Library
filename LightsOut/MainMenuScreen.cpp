#include "MainMenuScreen.h"

/// <summary>
/// Constructor function for the Main Menu class
/// </summary>
/// <param name="focusColorIn">Focus color for the GUI element</param>
/// <param name="noFocusColorIn">No focus color for the GUI elements</param>
/// <param name="fillColorIn">Fill color for the GUI elements</param>
/// <param name="selectSoundIn">Sound used by the GUI elements</param>
MainMenuScreen::MainMenuScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn) 
	: Screen(GameState::MainMenu),
	selectSound(selectSoundIn), 
	m_alphaFadeValue(255),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{
	// Initialise GUI elements
	m_gameTitle = new Label("Lights Out!", nullptr, 80, sf::Vector2f(400.0f, 80.0f), sf::Vector2f(400.0f, 900.0f));
	m_gameTitle->setPosition(sf::Vector2f(400.0f, 80.0f));
	m_gameTitle->setTextColor(sf::Color(255, 255, 255, 255));
	m_playButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Play", nullptr, sf::Vector2f(400.0f, 250.0f), 50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 250.0f), sf::Vector2f(400.0f, 900.0f));
	m_optionsButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Options", nullptr, sf::Vector2f(400.0f, 450.0f),50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 450.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Quit", nullptr, sf::Vector2f(400.0f, 650.0f), 50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 650.0f), sf::Vector2f(400.0f, 900.0f));

	// Promote the focus of one play button
	m_playButton->promoteFocus();

	// Set the actions for each GUI element
	m_playButton->m_down = m_optionsButton;
	m_optionsButton->m_up = m_playButton;
	m_optionsButton->m_down = m_quitButton;
	m_quitButton->m_up = m_optionsButton;
	m_playButton->select = std::bind(&MainMenuScreen::playButtonSelected, this);
	m_optionsButton->select = std::bind(&MainMenuScreen::optionsButtonSelected, this);
	m_quitButton->select = std::bind(&MainMenuScreen::quitButtonSelected, this);

	// Set the fade rectangle
	m_fadeRectangle.setSize(sf::Vector2f(800.0f, 800.0f));
	m_fadeRectangle.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaFadeValue));
	
	// Add elements to the GUI object
	m_gui.add(m_gameTitle);
	m_gui.add(m_playButton);
	m_gui.add(m_optionsButton);
	m_gui.add(m_quitButton);
}

/// <summary>
/// Reset function used to reset the main menu after the game state has been changed
/// </summary>
void MainMenuScreen::reset()
{
	optionsButtonPressed = false;
	quitButtonPressed = false;
	playButtonPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}

/// <summary>
/// update function updates the main menu and its GUI
/// </summary>
/// <param name="controller">Controller used for processing input</param>
void MainMenuScreen::update(XboxController &controller)
{
	m_fadeRectangle.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaFadeValue)); // Set the fill color of the fade rectangle
	if (m_alphaFadeValue >= FADE_RATE)
	{
		m_alphaFadeValue -= FADE_RATE;
	}

	m_gui.processInput(controller); // Update the GUI object

	if (playButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation); // Run transition Out cycle
		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::GamePlay; // Change the next game state
			interpolation = 0.0f; // Reset the interpolation
			reset(); // Reset the main menu
		}
	}
	else if (optionsButtonPressed) // Functions the same as the first if statement
	{
		m_gui.transitionOut(0.05f, interpolation);
		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::Options;
			interpolation = 0.0f;
			reset();
		}
	}
	else if (quitButtonPressed)  // Functions the same as the first if statement
	{
		m_gui.transitionOut(0.05f, interpolation);
		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::Quit;
			interpolation = 0.0f;
			reset();
		}
	}
	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation); // Run the transition in cycle
		if (interpolation >= 1.0f)
		{
			interpolation = 0.0f;
			transitionIn = false;
		}
	}
}

/// <summary>
/// Render function used to draw the main menu and its GUI
/// </summary>
/// <param name="window">window usd to render the GUI and fade rectangle</param>
void MainMenuScreen::render(sf::RenderWindow & window)
{
	window.draw(m_gui);
	window.draw(m_fadeRectangle);
}

/// <summary>
/// Function linked to a callback function for the play button
/// </summary>
void MainMenuScreen::playButtonSelected()
{
	playButtonPressed = true;
}

/// <summary>
/// Function linked to a callback function for the options button
/// </summary>
void MainMenuScreen::optionsButtonSelected()
{
	optionsButtonPressed = true;
}

/// <summary>
/// Function linked to a callback function for the quit button
/// </summary>
void MainMenuScreen::quitButtonSelected()
{
	quitButtonPressed = true;
}
#include "QuitScreen.h"

/// <summary>
/// Constructor function for the quit screen class
/// </summary>
/// <param name="focusColorIn">Focus color for the GUI elements</param>
/// <param name="noFocusColorIn">No focus color for the GUI elements</param>
/// <param name="fillColorIn">Fill color for the GUI elements</param>
/// <param name="selectSoundIn">Sound for the GUI elements</param>
/// <param name="windowIn">window used to end the game if the player chooses to do so</param>
QuitScreen::QuitScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn, sf::RenderWindow &windowIn)
	: Screen(GameState::Quit),
	transitionIn(true), 
	selectSound(selectSoundIn),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn),
	window(windowIn)
{
	// Initialise the GUI elements
	m_quitTitle = new Label("Are you sure?", nullptr, 80, sf::Vector2f(400.0f, 320.0f), sf::Vector2f(400.0f, 900.0f));
	m_yesButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Yes", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(550.0f, 450.0f), sf::Vector2f(400.0f, 900.0f));
	m_noButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "No", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(250.0f, 450.0f), sf::Vector2f(400.0f, 900.0f));

	// Promote the focus of one of the elements
	m_noButton->promoteFocus();

	// Assign what each GUI element does
	m_yesButton->m_left = m_noButton;
	m_noButton->m_right = m_yesButton;
	m_yesButton->select = std::bind(&QuitScreen::yesButtonSelected, this);
	m_noButton->select = std::bind(&QuitScreen::noButtonSelected, this);

	// Add the widgets to the GUI
	m_gui.add(m_quitTitle);
	m_gui.add(m_yesButton);
	m_gui.add(m_noButton);
}

/// <summary>
/// update function used to update the quit screen and process input
/// </summary>
/// <param name="controller">controller used for processing input</param>
void QuitScreen::update(XboxController &controller)
{
	m_gui.processInput(controller); // process input for the GUI

	if (controller.isButtonPressed(XBOX360_BACK))
	{
		m_noButtonSelected = true;
	}

	if (m_noButtonSelected)
	{
		m_gui.transitionOut(0.05f, interpolation); // Run the transition out cycle

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::MainMenu; // Change the game state
			reset(); // Reset the quit screen
			interpolation = 0.0f;  // Reset the interpolation
		}
	}
	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation); // Run the transition in cycle

		if (interpolation >= 1.0f)
		{
			interpolation = 0.0f; // Reset the interpolation
			transitionIn = false;
		}
	}
}

/// <summary>
/// Reset function used to reset the quit screen after the game state has been changed
/// </summary>
void QuitScreen::reset()
{
	m_noButtonSelected = false;
	m_yesButtonSelected = false;
	m_noButton->promoteFocus();
	m_yesButton->demoteFocus();
	transitionIn = true;
	interpolation = 0.0f;
}

/// <summary>
/// Function is linked to a callback function for the No button
/// </summary>
void QuitScreen::noButtonSelected()
{
	m_noButtonSelected = true; // Sets the boolean to true
}

/// <summary>
/// Function is linked to a callback function for the Yes button
/// </summary>
void QuitScreen::yesButtonSelected()
{
	window.close(); // Ends the game
}
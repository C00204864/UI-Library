#include "EndGameScreen.h"

/// <summary>
/// Constructor function for the EndGameScreen class
/// </summary>
/// <param name="focusColorIn">The in focus color passed to the GUI objects</param>
/// <param name="noFocusColorIn">The out of focus color passed to the GUI objects</param>
/// <param name="fillColorIn">The fill color passed to the GUI objects</param>
/// <param name="selectSound">The sound passed to the GUI obbjects</param>
EndGameScreen::EndGameScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSound)
	: Screen(GameState::EndGameState),
	transitionIn(true)
{
	// Initialise GUI elements on the heap
	m_gameOverLabel = new Label("You Win!", nullptr, 80, sf::Vector2f(400.0f, 240.0f), sf::Vector2f(400.0f, 900.0f));
	m_menuButton = new Button(focusColorIn, noFocusColorIn, fillColorIn, selectSound, "Menu", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(300.0f, 400.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitButton = new Button(focusColorIn, noFocusColorIn, fillColorIn, selectSound, "Quit", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(500.0f, 400.0f), sf::Vector2f(400.0f, 900.0f));

	// Set up what happens when you interact with a GUI element
	m_menuButton->m_right = m_quitButton;
	m_quitButton->m_left = m_menuButton;
	m_menuButton->select = std::bind(&EndGameScreen::toMenu, this);
	m_quitButton->select = std::bind(&EndGameScreen::toQuit, this);

	// Add the elements to the GUI object
	m_gui.add(m_gameOverLabel);
	m_gui.add(m_menuButton);
	m_gui.add(m_quitButton);

	// Set one element to have focus
	m_menuButton->promoteFocus();
}

/// <summary>
/// Update function used to update the end game screen
/// </summary>
/// <param name="controller">Controller used for processing input</param>
void EndGameScreen::update(XboxController& controller)
{
	m_gui.processInput(controller); // Process the GUI elements
	if (m_changeStateMenu) // If we must change to a menu
	{
		if (transitionOut()) // carry out a cycle of transition out
		{
			m_nextGameState = GameState::MainMenu; // If it returns true then change the game state
			reset(); // Reset this
		}
	}
	else if (m_changeStateQuit) // Functions in the eact same way as the change to menu statement
	{
		if (transitionOut())
		{
			m_nextGameState = GameState::Quit; // In this statement we change the state to quit
			reset();
		}
	}
	else if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation); // Carry out a transition in cycle

		if (interpolation >= 1.0f)
		{
			std::cout << "Transition play finished" << std::endl;
			interpolation = 0.0f; // Reset the interpolation
			transitionIn = false; // End the transition cycles
		}
	}
}

/// <summary>
/// Reset function used to reset the end game screen after
/// a changed game state
/// </summary>
void EndGameScreen::reset()
{
	transitionIn = true;
	m_menuButton->promoteFocus(); // Set the menu button to have focus
	m_quitButton->demoteFocus();
	m_changeStateMenu = false;
	m_changeStateQuit = false;
}

/// <summary>
/// allow the class to begin the transition to a menu
/// </summary>
void EndGameScreen::toMenu()
{
	m_changeStateMenu = true;
}

/// <summary>
/// allow the object to begin a transition to the quit screen
/// </summary>
void EndGameScreen::toQuit()
{
	m_changeStateQuit = true;
}

/// <summary>
/// transition out function used to move the end game screen out of view
/// </summary>
/// <returns>bollean: true if the transition is complete, otherwise false</returns>
bool EndGameScreen::transitionOut()
{
	m_gui.transitionOut(0.05f, interpolation); // Carry out a transition out cycle

	if (interpolation >= 1.0f)
	{
		std::cout << "Transition play finished" << std::endl;
		reset(); // Reset this
		interpolation = 0.0f; // Reset the interpolation
		return true; // Return true if te cycle is complete
	}
	return false; // Otherwise return false
}
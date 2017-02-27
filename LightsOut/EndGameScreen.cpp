#include "EndGameScreen.h"

EndGameScreen::EndGameScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSound)
	: Screen(GameState::EndGameState),
	transitionIn(true)
{
	m_gameOverLabel = new Label("You Win!", nullptr, 80, sf::Vector2f(400.0f, 240.0f), sf::Vector2f(400.0f, 900.0f));
	m_menuButton = new Button(focusColorIn, noFocusColorIn, fillColorIn, selectSound, "Menu", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(300.0f, 400.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitButton = new Button(focusColorIn, noFocusColorIn, fillColorIn, selectSound, "Quit", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(500.0f, 400.0f), sf::Vector2f(400.0f, 900.0f));

	m_menuButton->m_right = m_quitButton;
	m_quitButton->m_left = m_menuButton;

	m_menuButton->select = std::bind(&EndGameScreen::toMenu, this);
	m_quitButton->select = std::bind(&EndGameScreen::toQuit, this);

	m_gui.add(m_gameOverLabel);
	m_gui.add(m_menuButton);
	m_gui.add(m_quitButton);

	m_menuButton->promoteFocus();
}

void EndGameScreen::update(XboxController& controller)
{
	m_gui.processInput(controller);
	if (m_changeStateMenu)
	{
		if (transitionOut())
		{
			m_nextGameState = GameState::MainMenu;
			reset();
		}
	}
	else if (m_changeStateQuit)
	{
		if (transitionOut())
		{
			m_nextGameState = GameState::Quit;
			reset();
		}
	}
	else if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			std::cout << "Transition play finished" << std::endl;
			interpolation = 0.0f;
			transitionIn = false;
		}
	}
}

void EndGameScreen::reset()
{
	transitionIn = true;
	m_menuButton->promoteFocus();
	m_quitButton->demoteFocus();
	m_changeStateMenu = false;
	m_changeStateQuit = false;
}

void EndGameScreen::toMenu()
{
	m_changeStateMenu = true;
}

void EndGameScreen::toQuit()
{
	m_changeStateQuit = true;
}

bool EndGameScreen::transitionOut()
{
	m_gui.transitionOut(0.05f, interpolation);

	if (interpolation >= 1.0f)
	{
		std::cout << "Transition play finished" << std::endl;
		reset();
		interpolation = 0.0f;
		return true;
	}
	return false;
}
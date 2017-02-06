#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
{
	m_gameTitle = new Label("Lights Out!", nullptr, 80, sf::Vector2f(400.0f, 50.0f), sf::Vector2f(400.0f, 900.0f));
	m_gameTitle->setPosition(sf::Vector2f(400.0f, 50.0f));

	m_playButton = new Button("Play", nullptr, sf::Vector2f(400.0f, 200.0f), 50, 500.0f, 60.0f, 
		sf::Vector2f(400.0f, 200.0f), sf::Vector2f(400.0f, 900.0f));
	m_optionsButton = new Button("Options", nullptr, sf::Vector2f(400.0f, 400.0f),50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 400.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitButton = new Button("Quit", nullptr, sf::Vector2f(400.0f, 600.0f), 50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 600.0f), sf::Vector2f(400.0f, 900.0f));

	m_playButton->promoteFocus();

	m_playButton->m_down = m_optionsButton;
	m_optionsButton->m_up = m_playButton;
	m_optionsButton->m_down = m_quitButton;
	m_quitButton->m_up = m_optionsButton;

	m_playButton->select = std::bind(&MainMenuScreen::playButtonSelected, this);
	m_optionsButton->select = std::bind(&MainMenuScreen::optionsButtonSelected, this);
	m_quitButton->select = std::bind(&MainMenuScreen::quitButtonSelected, this);
}

void MainMenuScreen::initialise()
{
	m_gui.add(m_gameTitle);
	m_gui.add(m_playButton);
	m_gui.add(m_optionsButton);
	m_gui.add(m_quitButton);
}

void MainMenuScreen::reset()
{
	m_gameTitle->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_playButton->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_optionsButton->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_quitButton->setPosition(sf::Vector2f(400.0f, 900.0f));

	changeToOptionsState = false;
	optionsButtonPressed = false;
	playButtonPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}

void MainMenuScreen::update(XboxController &controller)
{
	m_gui.processInput(controller);

	if (playButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);
	}
	else if (optionsButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			changeToOptionsState = true;
			interpolation = 0.0f;
		}
	}
	else if (quitButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			changeToQuitState = true;
			interpolation = 0.0f;
		}
	}

	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			interpolation = 0.0f;
			transitionIn = false;
		}
	}
}

bool MainMenuScreen::getChangeStateOptions()
{
	return changeToOptionsState;
}

bool MainMenuScreen::getChangeStateQuit()
{
	return changeToQuitState;
}

void MainMenuScreen::render(sf::RenderWindow &window)
{
	window.draw(m_gui);
}

void MainMenuScreen::playButtonSelected()
{
	std::cout << "Play button has been pressed" << std::endl;
	playButtonPressed = true;
}

void MainMenuScreen::optionsButtonSelected()
{
	std::cout << "Options button has been pressed" << std::endl;
	optionsButtonPressed = true;
}

void MainMenuScreen::quitButtonSelected()
{
	std::cout << "Quit button has been pressed" << std::endl;
	quitButtonPressed = true;
}
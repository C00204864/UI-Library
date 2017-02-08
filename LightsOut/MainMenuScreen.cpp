#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(sf::Sound &selectSoundIn) : 
	selectSound(selectSoundIn)
{
	m_gameTitle = new Label("Lights Out!", nullptr, 80, sf::Vector2f(400.0f, 80.0f), sf::Vector2f(400.0f, 900.0f));
	m_gameTitle->setPosition(sf::Vector2f(400.0f, 80.0f));

	m_playButton = new Button(selectSound, "Play", nullptr, sf::Vector2f(400.0f, 250.0f), 50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 250.0f), sf::Vector2f(400.0f, 900.0f));
	m_optionsButton = new Button(selectSound, "Options", nullptr, sf::Vector2f(400.0f, 450.0f),50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 450.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitButton = new Button(selectSound, "Quit", nullptr, sf::Vector2f(400.0f, 650.0f), 50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 650.0f), sf::Vector2f(400.0f, 900.0f));

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
	changeToQuitState = false;
	optionsButtonPressed = false;
	quitButtonPressed = false;
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

		if (interpolation >= 1.0f)
		{
			m_changeToGamePlayState = true;
			interpolation = 0.0f;
		}
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

bool MainMenuScreen::getChangeStateGamePlay()
{
	return m_changeToGamePlayState;
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
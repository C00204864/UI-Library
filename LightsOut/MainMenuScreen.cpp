#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
{
	m_gameTitle = new Label("Lights Out!", nullptr, 80);
	m_gameTitle->setPosition(sf::Vector2f(400.0f, 50.0f));
	m_gameTitle->setStartPosition(sf::Vector2f(400.0f, 50.0f));
	m_gameTitle->setEndPosition(sf::Vector2f(400.0f, 900.0f));
	m_playButton = new Button("Play", nullptr, sf::Vector2f(400.0f, 200.0f), 50, 500.0f, 60.0f);
	m_playButton->setStartPosition(sf::Vector2f(400.0f, 200.0f));
	m_playButton->setEndPosition(sf::Vector2f(400.0f, 900.0f));
	m_optionsButton = new Button("Options", nullptr, sf::Vector2f(400.0f, 400.0f),50, 500.0f, 60.0f);
	m_optionsButton->setStartPosition(sf::Vector2f(400.0f, 400.0f));
	m_optionsButton->setEndPosition(sf::Vector2f(400.0f, 900.0f));
	m_quitButton = new Button("Quit", nullptr, sf::Vector2f(400.0f, 600.0f), 50, 500.0f, 60.0f);
	m_quitButton->setStartPosition(sf::Vector2f(400.0f, 600.0f));
	m_quitButton->setEndPosition(sf::Vector2f(400.0f, 900.0f));

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

bool go_back = false;
void MainMenuScreen::update(XboxController &controller)
{
	m_gui.processInput(controller);

	if (playButtonPressed)
	{
		m_gui.transitionOut(0.05f);
	}
	else if (optionsButtonPressed)
	{
		m_gui.transitionOut(0.05f);

		if (m_gui.isTranstionFinished())
		{
			std::cout << "Transition play finished" << std::endl;
			changeToOptionsState = true;
		}
	}
	else if (quitButtonPressed)
	{
		m_gui.transitionOut(0.05f);
	}

	if (go_back)
	{
		m_gui.transitionIn(0.05f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		go_back = true;
		optionsButtonPressed = false;
		playButtonPressed = false;
	}
}

bool MainMenuScreen::getChangeStateOptions()
{
	return changeToOptionsState;
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
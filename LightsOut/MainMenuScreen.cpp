#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen()
{
	m_gameTitle = new Label("Lights Out!", nullptr, 80);
	m_gameTitle->setPosition(sf::Vector2f(400.0f, 50.0f));
	m_playButton = new Button("Play", nullptr, sf::Vector2f(400.0f, 200.0f), 50, 500.0f, 60.0f);
	m_optionsButton = new Button("Options", nullptr, sf::Vector2f(400.0f, 400.0f),50, 500.0f, 60.0f);
	m_quitButton = new Button("Quit", nullptr, sf::Vector2f(400.0f, 600.0f), 50, 500.0f, 60.0f);

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

void MainMenuScreen::update(XboxController &controller)
{
	m_gui.processInput(controller);

	if (playButtonPressed)
	{
		m_gui.transition(sf::Vector2f(400.0f, 200.0f), sf::Vector2f(800.0f, 2.0f), 0.005f);
	}
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
}

void MainMenuScreen::quitButtonSelected()
{
	std::cout << "Quit button has been pressed" << std::endl;
}
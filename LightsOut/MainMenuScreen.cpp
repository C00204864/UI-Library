#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn) 
	: Screen(GameState::MainMenu),
	selectSound(selectSoundIn), m_alphaFadeValue(255),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{
	m_gameTitle = new Label("Lights Out!", nullptr, 80, sf::Vector2f(400.0f, 80.0f), sf::Vector2f(400.0f, 900.0f));
	m_gameTitle->setPosition(sf::Vector2f(400.0f, 80.0f));
	m_gameTitle->setTextColor(sf::Color(255, 255, 255, 255));

	m_playButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Play", nullptr, sf::Vector2f(400.0f, 250.0f), 50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 250.0f), sf::Vector2f(400.0f, 900.0f));
	m_optionsButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Options", nullptr, sf::Vector2f(400.0f, 450.0f),50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 450.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Quit", nullptr, sf::Vector2f(400.0f, 650.0f), 50, 500.0f, 60.0f,
		sf::Vector2f(400.0f, 650.0f), sf::Vector2f(400.0f, 900.0f));

	m_playButton->promoteFocus();

	m_playButton->m_down = m_optionsButton;
	m_optionsButton->m_up = m_playButton;
	m_optionsButton->m_down = m_quitButton;
	m_quitButton->m_up = m_optionsButton;

	m_playButton->select = std::bind(&MainMenuScreen::playButtonSelected, this);
	m_optionsButton->select = std::bind(&MainMenuScreen::optionsButtonSelected, this);
	m_quitButton->select = std::bind(&MainMenuScreen::quitButtonSelected, this);

	m_fadeRectangle.setSize(sf::Vector2f(800.0f, 800.0f));
	m_fadeRectangle.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaFadeValue));
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
	changeToOptionsState = false;
	changeToQuitState = false;
	m_changeToGamePlayState = false;
	optionsButtonPressed = false;
	quitButtonPressed = false;
	playButtonPressed = false;
	transitionIn = true;
	interpolation = 0.0f;
}

void MainMenuScreen::update(XboxController &controller)
{
	m_fadeRectangle.setFillColor(sf::Color(0.0f, 0.0f, 0.0f, m_alphaFadeValue));

	if (m_alphaFadeValue >= FADE_RATE)
		m_alphaFadeValue -= FADE_RATE;

	m_gui.processInput(controller);

	if (playButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			m_changeToGamePlayState = true; // TODO : GET RID
			m_nextGameState = GameState::GamePlay;
			interpolation = 0.0f;
			reset();
		}
	}
	else if (optionsButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			changeToOptionsState = true; // TODO : GET RID
			m_nextGameState = GameState::Options;
			interpolation = 0.0f;
			reset();
		}
	}
	else if (quitButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			changeToQuitState = true; // TODO : GET RID
			m_nextGameState = GameState::Quit;
			interpolation = 0.0f;
			reset();
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

void MainMenuScreen::render(sf::RenderWindow & window)
{
	window.draw(m_gui);
	window.draw(m_fadeRectangle);
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
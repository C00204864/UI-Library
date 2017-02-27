#include "QuitScreen.h"

QuitScreen::QuitScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn, sf::RenderWindow &windowIn)
	: Screen(GameState::Quit),
	transitionIn(true), 
	selectSound(selectSoundIn),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn),
	window(windowIn)
{
	m_quitTitle = new Label("Are you sure?", nullptr, 80, sf::Vector2f(400.0f, 320.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitTitle->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_yesButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Yes", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(550.0f, 450.0f), sf::Vector2f(400.0f, 900.0f));
	m_noButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "No", nullptr, sf::Vector2f(400.0f, 900.0f), 40, 180.0f, 60.0f, sf::Vector2f(250.0f, 450.0f), sf::Vector2f(400.0f, 900.0f));

	m_noButton->promoteFocus();

	m_yesButton->m_left = m_noButton;
	m_noButton->m_right = m_yesButton;

	m_yesButton->select = std::bind(&QuitScreen::yesButtonSelected, this);
	m_noButton->select = std::bind(&QuitScreen::noButtonSelected, this);
}

void QuitScreen::initialise()
{
	m_gui.add(m_quitTitle);
	m_gui.add(m_yesButton);
	m_gui.add(m_noButton);
}

void QuitScreen::update(XboxController &controller)
{
	m_gui.processInput(controller);

	if (controller.isButtonPressed(XBOX360_BACK))
	{
		m_noButtonSelected = true;
	}

	if (m_noButtonSelected)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			std::cout << "Transition play finished" << std::endl;
			m_changeToMenuState = true; // TODO : GET RID
			m_nextGameState = GameState::MainMenu;
			reset();
			interpolation = 0.0f;
		}
	}
	if (transitionIn)
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

bool QuitScreen::getChangeStateMenu()
{
	return m_changeToMenuState;
}

bool QuitScreen::getExitGameState()
{
	return m_exitGame;
}

void QuitScreen::reset()
{
	m_noButtonSelected = false;
	m_yesButtonSelected = false;
	m_changeToMenuState = false;
	m_noButton->promoteFocus();
	transitionIn = true;
	interpolation = 0.0f;
}

void QuitScreen::noButtonSelected()
{
	m_noButtonSelected = true;
}

void QuitScreen::yesButtonSelected()
{
	window.close();
}
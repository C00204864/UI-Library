#include "QuitScreen.h"

QuitScreen::QuitScreen()
	: transitionIn(true)
{
	m_quitTitle = new Label("Are you sure?", nullptr, 50, sf::Vector2f(400.0f, 50.0f), sf::Vector2f(400.0f, 900.0f));
	m_quitTitle->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_yesButton = new Button("Yes", nullptr, sf::Vector2f(400.0f, 900.0f), 18, 100.0f, 40.0f, sf::Vector2f(550.0f, 600.0f), sf::Vector2f(400.0f, 900.0f));
	m_noButton = new Button("No", nullptr, sf::Vector2f(400.0f, 900.0f), 18, 100.0f, 40.0f, sf::Vector2f(250.0f, 600.0f), sf::Vector2f(400.0f, 900.0f));

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

	if (m_changeToMenuState)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			std::cout << "Transition play finished" << std::endl;
			m_changeToMenuState = true;
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

void QuitScreen::render(sf::RenderWindow &window)
{
	window.draw(m_gui);
}

bool QuitScreen::getChangeStateOptions()
{
	return m_changeToMenuState;
}

void QuitScreen::reset()
{
	m_changeToMenuState = true;
	m_noButton->promoteFocus();
	transitionIn = true;
	interpolation = 0.0f;

	m_quitTitle->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_yesButton->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_noButton->setPosition(sf::Vector2f(400.0f, 900.0f));
}

void QuitScreen::noButtonSelected()
{
	m_changeToMenuState = true;
}

void QuitScreen::yesButtonSelected()
{
	// Exit Game
}
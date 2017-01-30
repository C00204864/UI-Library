#include "Button.h"

Button::Button(const std::string & textIn, Widget * parent, sf::Vector2f & positionIn,
	int characterSize, float buttonWidth, float buttonHeight) :
	Label(textIn, parent)
{
	widgetPos = positionIn;
	m_front.setPosition(widgetPos);
	m_front.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_front.setFillColor(sf::Color::Blue);
	Label::setPosition(widgetPos);
}

bool Button::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		return false;
	}
	else if (controller.isButtonPressed(XBOX360_UP)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_up != nullptr)
		{
			m_up->promoteFocus();
			demoteFocus();
			return true;
		}
	}
	else if (controller.isButtonPressed(XBOX360_DOWN)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_down != nullptr)
		{
			m_down->promoteFocus();
			demoteFocus();
			return true;
		}
	}
	else if (controller.isButtonPressed(XBOX360_A)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		select();
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_front);
	Label::draw(target, states);
}
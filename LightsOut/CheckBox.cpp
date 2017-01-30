#include "CheckBox.h"

CheckBox::CheckBox(const std::string & textIn, Widget * parent, sf::Vector2f & positionIn,
	int characterSize, float boxWidth, float boxHeight) : Label(textIn, parent)
{
	widgetPos = positionIn;
	m_box.setPosition(widgetPos);
	m_box.setSize(sf::Vector2f(boxWidth, boxHeight));
	m_box.setFillColor(sf::Color::White);
	m_box.setOutlineColor(sf::Color::White);
	m_box.setOutlineThickness(2.f);
	sf::Vector2f textOffset(widgetPos.x + boxWidth, widgetPos.y);
	Label::setPosition(textOffset);
	Label::setCharacterSize(characterSize);
}

bool CheckBox::processInput(XboxController & controller)
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
	else if (controller.isButtonPressed(XBOX360_LEFT)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (m_left != nullptr)
		{
			m_left->promoteFocus();
			demoteFocus();
			return true;
		}
	}
	else if (controller.isButtonPressed(XBOX360_RIGHT)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_right != nullptr)
		{
			m_right->promoteFocus();
			demoteFocus();
			return true;
		}
	}
	else if (controller.isButtonPressed(XBOX360_A)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		m_state = !m_state;
		if (m_state)
		{
			m_box.setFillColor(sf::Color::Red);
		}
		else
		{
			m_box.setFillColor(sf::Color::White);
		}
	}
}

void CheckBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_box);
	Label::draw(target, states);
}
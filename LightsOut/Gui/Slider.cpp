#include "Slider.h"

/// <summary>
/// 
/// </summary>
/// <param name="text"></param>
/// <param name="parent"></param>
/// <param name="position"></param>
/// <param name="characterSize"></param>
/// <param name="sliderWidth"></param>
/// <param name="sliderHeight"></param>
Slider::Slider(const std::string& text, Widget* parent, sf::Vector2f &position,
	int characterSize, float sliderWidth, float sliderHeight)
	: Label(text, parent), m_barBaseWidth(sliderWidth), m_barSize(m_barBaseWidth), m_barBaseHeight(sliderHeight)
{
	widgetPos = position;

	// Base under the moving slider bar
	m_base.setSize(sf::Vector2f(m_barBaseWidth, m_barBaseHeight));
	m_base.setOutlineColor(sf::Color::Red);
	m_base.setFillColor(sf::Color::Blue);
	m_base.setOutlineThickness(2);
	m_base.setPosition(widgetPos);

	// The slider bar the player changes
	m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
	m_bar.setOutlineColor(sf::Color::Red);
	m_bar.setPosition(widgetPos);

	Label::setPosition(position - sf::Vector2f(0.0f, 30.0f));
	Label::setCharacterSize(characterSize);
}

/// <summary>
/// 
/// </summary>
/// <param name="controller"></param>
/// <returns></returns>
bool Slider::processInput(XboxController &controller)
{
	if (!m_hasFocus)
		return false;

	else if (m_hasFocus)
	{
		if (controller.isButtonHeldDown(XBOX360_RIGHT) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if(m_barSize < m_barBaseWidth)
				m_barSize += 1.0f;
			increase();
			m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
			return true;
		}
		else if (controller.isButtonHeldDown(XBOX360_LEFT)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_barSize > 0)
				m_barSize -= 1.0f;
			decrease();
			m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
			return true;
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
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Call the super class overridden draw function.
	Label::draw(target, states);

	// Draw the slider.
	target.draw(m_base);
	target.draw(m_bar, states);
}
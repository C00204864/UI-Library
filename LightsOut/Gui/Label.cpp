#include "Label.h"

Label::Label(const std::string& text, Widget* parent) :
	Widget(parent)
{
	// TODO(Darren): Remove this (loads for every widget)
	if (!font.loadFromFile("Assets/Fonts/arial.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	// NOTE(Darren): Will create a global resource manager
	m_text.setFont(font); // Configuration::fonts.get(Configuration::Fonts::Gui));
	setText(text);
	setTextColor(sf::Color(180, 93, 23));
}

void Label::setText(const std::string& text)
{
	m_text.setString(text);
	updateShape();
}

void Label::setPosition(sf::Vector2f &relativePosition)
{
	m_text.setPosition(relativePosition);
}

void Label::setCharacterSize(unsigned int size)
{
	m_text.setCharacterSize(size);
	updateShape();
}

unsigned int Label::getCharacterSize() const
{
	return m_text.getCharacterSize();
}

void Label::setTextColor(const sf::Color& color)
{
	m_text.setColor(color);
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}
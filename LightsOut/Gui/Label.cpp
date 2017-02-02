#include "Label.h"

Label::Label(const std::string& text, Widget* parent, unsigned int size) :
	Widget(parent)
{
	m_text.setFont(*g_resourceMgr.getGameFont());
	setText(text);
	setTextColor(sf::Color(180, 93, 23));
	m_text.setCharacterSize(size);
	textRect = m_text.getGlobalBounds();
	updateShape();
	sf::Text fontCheck;
	fontCheck.setFont(*m_text.getFont());
	fontCheck.setCharacterSize(size);
	fontCheck.setString("ph|");
	m_trueTextHeight = fontCheck.getGlobalBounds().height;
	m_text.setOrigin(textRect.width / 2.0f,
		m_trueTextHeight / 2.f);
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
	//sf::RectangleShape s(sf::Vector2f(textRect.width, textRect.height));
	//s.setFillColor(sf::Color::White);
	//s.setOrigin(sf::Vector2f(textRect.width / 2.f, textRect.height / 2.f));
	//s.setPosition(m_text.getPosition());
	//target.draw(s, states);
	target.draw(m_text, states);
	
}

sf::Text Label::getText()
{
	return m_text;
}

float Label::getTextHeight()
{
	return m_trueTextHeight;
}
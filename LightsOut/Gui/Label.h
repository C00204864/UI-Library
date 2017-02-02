#ifndef LABEL_H
#define LABEL_H

#include <SFML\Graphics.hpp>
#include "Widget.h"
#include "../ResourceManager.h"

/// <summary>
/// Label class used to draw Labels (Text) to the screen
/// Class inherits from Widget and thus is a widget.
/// </summary>
class Label : public Widget
{
public:
	Label(const std::string& text, Widget* parent = nullptr, unsigned int size = 18);
	virtual void setPosition(sf::Vector2f &position) override;
	void setText(const std::string &text);
	unsigned int getCharacterSize() const;
	void setTextColor(const sf::Color& color);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Text getText();
	float getTextHeight();
private:
	sf::FloatRect textRect;
	sf::Text m_text;
	float m_trueTextHeight;
};

#endif
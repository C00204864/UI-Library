#ifndef LABEL_H
#define LABEL_H

#include <SFML\Graphics.hpp>
#include "Widget.h"
#include "../ResourceManager.h"

/// 
/// 
/// 
class Label : public Widget
{
public:
	Label(const std::string& text, Widget* parent = nullptr, unsigned int size = 18);

	void setText(const std::string &text);
	void setPosition(sf::Vector2f &relativePosition);
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
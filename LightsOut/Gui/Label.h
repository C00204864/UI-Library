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
	Label(const std::string& text, Widget* parent = nullptr);

	void setText(const std::string &text);
	void setPosition(sf::Vector2f &relativePosition);
	void setCharacterSize(unsigned int size);
	unsigned int getCharacterSize() const;
	void setTextColor(const sf::Color& color);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::Text m_text;

};

#endif
/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef SLIDER_H
#define SLIDER_H

#include "Label.h"
#include <functional>

/// <summary>
/// Slider class used for creating Sliders onscreen
/// Class inherits from Label and thus is a widget.
/// </summary>
class Slider : public Label
{
public:
	Slider(sf::Sound &selectSoundIn,  std::string& text, Widget* parent, sf::Vector2f &position, int characerSize = 18.0f, float sliderWidth = 100.0f, 
		float sliderHeight = 15.0f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	typedef std::function<void()> Callback;
	Callback increase, decrease;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float getPercentageFull();

private:
	sf::RectangleShape m_bar, m_base;
	float m_barBaseWidth;
	float m_barBaseHeight;
	float m_barSize;
	sf::Sound &selectSound;
};

#endif
#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Label.h"
#include <functional>

/// <summary>
/// CheckBox Class used for creating Check Boxes onscreen
/// Class inherits from Label and thus is a widget
/// </summary>
class CheckBox : public Label {
public:
	CheckBox(const std::string & textIn, Widget * parent, sf::Vector2f & positionIn,
		int characterSize = 22.f, float boxWidth = 40.f, float boxHeight = 40.f);
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback stateSwitch;
private:
	bool m_state = false;
	sf::RectangleShape m_checkBoxRect;
};

#endif
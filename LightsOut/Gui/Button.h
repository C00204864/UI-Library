/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include <functional>

/// <summary>
/// Button Class used for creating buttons onscreen.
/// Class inherits from Label and thus is a widget.
/// </summary>
class Button : public Label 
{
public:
	Button(const std::string & textIn, Widget * parent, sf::Vector2f & positionIn, int characterSize = 18.f, float buttonWidth = 100.f, float buttonHeight = 40.f, 
		sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & xboxController);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;
private:
	sf::RectangleShape m_buttonRect;
	const int BUTTON_BUFFER = 15; // Buffer for increasing the edge of the button slightly
};
#endif

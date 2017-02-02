#ifndef BUTTON_H
#define BUTTON_H

#include "Label.h"
#include <functional>

class Button : public Label {
public:
	Button(const std::string & textIn, Widget * parent, sf::Vector2f & positionIn, 
		int characterSize = 18.f, float buttonWidth = 100.f, float buttonHeight = 40.f);
	bool processInput(XboxController & xboxController);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	typedef std::function<void()> Callback;
	Callback select;
private:
	sf::RectangleShape m_buttonRect;
	const int BUTTON_BUFFER = 15;
};
#endif

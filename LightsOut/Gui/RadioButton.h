/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>


#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "Label.h"
#include <functional>

/// <summary>
/// RadioButton class used for creating radioButtons (similar to CheckBox class)
/// Class inherits from Label and thus is a widget.
/// </summary>
class RadioButton : public Label {
public:
	RadioButton(sf::Sound &selectSoundIn, const std::string & textIn, Widget * parent, sf::Vector2f & positionIn, std::vector<RadioButton *> & radGroup,
		sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f(), 
		int characterSize = 22.f, float boxWidth = 40.f, float boxHeight = 40.f);
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	//void add(RadioButton * radioButtonIn); <---> NOTE <---> IM LEAVING THIS FUNCTION FOR NOW BUT TAKE IT OUT(!!!)
	void deActivate();
	bool getState();
private:
	bool m_state = false;
	sf::RectangleShape m_radioButtonRect;
	std::vector<RadioButton *> & m_otherButtons;
	sf::Sound &selectSound;
};

#endif

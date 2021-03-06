/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>


#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "Label.h"
#include <functional>

/// <summary>
/// Brief: RadioButton class used for creating radioButtons (similar to CheckBox class)
/// 
/// Detail: Class inherits from Label and thus is a widget.
/// </summary>
class RadioButton : public Label {
public:
	RadioButton(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, 
		sf::Sound &selectSoundIn, const std::string & textIn, Widget * parent, 
		sf::Vector2f & positionIn, std::vector<RadioButton *> & radGroup,
		sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f(), 
		int characterSize = 22.f, float boxWidth = 40.f, float boxHeight = 40.f);
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void deActivate();
	bool getState() const;
	void activate();
	void setColors() override;

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;
private:
	bool m_state = false; // State of the radio button
	sf::RectangleShape m_radioButtonRect; // Rectangle displayed by the radio button
	std::vector<RadioButton *> & m_otherButtons; // A reference to a vector containing the radio button group (used to interact with all radio buttons at once)

	// Sound and Color references
	sf::Sound &selectSound;
	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;
};

#endif

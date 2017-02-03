/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>
#include "Widget.h"
#include "..\MathUtility.h"

/// Handles all Gui elements added to it
///
/// Updates and renders all Gui elements that was added to it 
/// through the use of the add(...) method
class Gui : public Widget
{
public:
	Gui(Widget* parent = nullptr);
	~Gui();
	bool processInput(XboxController &controller);
	void add(Widget* widget);
	void transitionOut(float transitionSpeed);
	void transitionIn(float transitionSpeed);
	bool isTranstionFinished();
	
	// A vector of all the widgets this Gui handles
	std::vector<Widget*> m_widgets;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// NOTE(Darren): This if for testing, remove it
	bool do_transition;
	float speed;
	float interpolationOut, interpolationIn;
};

#endif
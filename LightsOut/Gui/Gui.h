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
	void transition(sf::Vector2f &startPos, sf::Vector2f &targetPos, float transitionSpeed);
	void processAnimation();
	
private:
	// A vector of all the widgets this Gui handles
	std::vector<Widget*> m_widgets;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	// Testing
	bool do_transition;
	float speed;
	float inter = 0.0f;
};

#endif
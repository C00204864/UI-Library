/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef WIDGET_H
#define WIDGET_H

#include <SFML\Graphics.hpp>
#include "..\XboxController.h"

/// Provides a base class for objects that are a widget.
///
/// Allows the subclasses to overload the how the player will control a
/// widget, render it and how it's updated. Provides pointers to other widgets
/// which hold the relative location of the next gui the player can move to.
class Widget : public sf::Drawable
{
public:
	Widget(Widget *parent = nullptr);

	virtual bool processInput(XboxController &controller);
	virtual void update(int numFrames);
	virtual void updateShape();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Widget *m_parent;

	Widget *m_left;
	Widget *m_right;
	Widget *m_up;
	Widget *m_down;

	void promoteFocus();
	void demoteFocus();

protected:
	// The widget the player is currenly on and can interact with.
	bool m_hasFocus;
	sf::Vector2f widgetPos;
};

#endif
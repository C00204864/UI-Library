#include "Gui.h"

/// <summary>
/// 
/// </summary>
/// <param name="parent"></param>
Gui::Gui(Widget *parent) 
	: speed(0.0f) { }

/// <summary>
/// Delets all widgets added to the widgets vector
/// </summary>
Gui::~Gui()
{
	for (Widget* widget : m_widgets)
	{
		if (widget->m_parent == this)
		{
			delete widget;
		}
	}
}

/// <summary>
/// Process all the widgets added and only updates the current widget has current focus
/// </summary>
/// <param name="controller">A refernce to an instance of XboxController class</param>
/// <returns> A bool value, if to process the input
bool Gui::processInput(XboxController &controller)
{
	for (Widget* widget : m_widgets)
	{
		if (!widget->processInput(controller))
		{
			// If the current widget is not in focus continue onto the next
			continue;
		}
	}

	return true;
}

void Gui::processAnimation()
{
	// TODO(Darren): Take this out
}

/// <summary>
/// Adds a widget to the vector for widgets
/// </summary>
/// <param name="widget"></param>
void Gui::add(Widget* widget)
{
	widget->m_parent = this;
	m_widgets.emplace_back(widget);
	updateShape();
}

void Gui::transition(sf::Vector2f &startPos, sf::Vector2f &targetPos, float transitionSpeed)
{
	if (inter < 1.0f)
		inter += transitionSpeed;
	else
		inter = 1.0f;

	for (Widget* widget : m_widgets)
	{
		sf::Vector2f transitionPos = lerp(widget->getPosition(), targetPos, inter);
		widget->setPosition(transitionPos);
	}
}

/// <summary>
/// Draws all widgets contained in the widgets
/// </summary>
/// <param name="target">A refenrence to a RenderTarget</param>
/// <param name="states">RenderState which defines the state for drawing</param>
void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Widget* widget : m_widgets)
	{
		target.draw(*widget, states);
	}
}

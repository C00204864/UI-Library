#include "Widget.h"

/// <summary>
/// The constructor takes in a pointer to a parent widget (if it has one).
/// Sets all realtive pointers that the gui might have to nullptr
/// </summary>
Widget::Widget(Widget *parent)
	: m_parent(parent)
{
	m_left = nullptr;
	m_right = nullptr;
	m_up = nullptr;
	m_down = nullptr;
}

/// <summary>
/// A virtual method sub classes can implement for specific functionality
/// </summary>
/// <returns> A bool value, should this widget be updated
bool Widget::processInput(XboxController &controller)
{
	return false;
}

/// <summary>
/// Sets the widget focus value to true (promotes)
/// </summary>
void Widget::promoteFocus()
{
	m_hasFocus = true;
}

/// <summary>
/// Sets the widget focus value to false (demotes)
/// </summary>
void Widget::demoteFocus()
{
	m_hasFocus = false;
}

void Widget::setPosition(sf::Vector2f &pos)
{
	widgetPos = pos;
}

sf::Vector2f Widget::getPosition()
{
	return widgetPos;
}

/// <summary>
/// Updates the parent update metod.
/// </summary>
void Widget::update(int numFrames)
{
	if (m_parent)
	{
		m_parent->updateShape();
	}
}

/// <summary>
/// Updates the shape of the parent if there is one.
/// </summary>
void Widget::updateShape()
{
	if (m_parent)
	{
		m_parent->updateShape();
	}
}

/// <summary>
/// A virtual function that the sub class can implement.
/// </summary>
void Widget::draw(sf::RenderTarget & target, sf::RenderStates states) const { }
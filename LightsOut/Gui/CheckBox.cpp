#include "CheckBox.h"
 
/// <summary>
/// Constructor function for the CheckBox class
/// </summary>
/// <param name="textIn">Text to be displayed by the check Box object's inherited label</param>
/// <param name="parent">parent widget to the CheckBox object</param>
/// <param name="positionIn">position of the Check Box</param>
/// <param name="characterSize">Size of the Characters to be used by the font when drawing text</param>
/// <param name="boxWidth">Width of the Check Box</param>
/// <param name="boxHeight">Height of the Chec Box</param>
CheckBox::CheckBox(const std::string & textIn, Widget * parent, sf::Vector2f & positionIn, int characterSize, 
		float boxWidth, float boxHeight, sf::Vector2f &startPos, sf::Vector2f &endPos) 
	: Label(textIn, parent, characterSize)
{
	widgetPos = positionIn; // Set the position in the base class
	widgetStartPos = startPos;
	widgetEndPos = endPos;
	//Set the position, size, colours and outlines of the CheckBox
	m_checkBoxRect.setPosition(widgetPos);
	m_checkBoxRect.setSize(sf::Vector2f(boxWidth, boxHeight));
	m_checkBoxRect.setFillColor(sf::Color::White);
	m_checkBoxRect.setOutlineColor(sf::Color::White);
	m_checkBoxRect.setOutlineThickness(3.f);
	// Set the position of the Label object
	sf::Vector2f textOffset(widgetPos.x, widgetPos.y - m_checkBoxRect.getGlobalBounds().height); // We offset the Label to be directly above the CheckBox
	m_checkBoxRect.setOrigin(m_checkBoxRect.getLocalBounds().width / 2.0f, m_checkBoxRect.getLocalBounds().height / 2.0f);
	Label::setPosition(textOffset);
}

void CheckBox::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_checkBoxRect.setPosition(widgetPos);
	// Set the position of the Label object
	sf::Vector2f textOffset(widgetPos.x, widgetPos.y - m_checkBoxRect.getGlobalBounds().height); // We offset the Label to be directly above the CheckBox
	Label::setPosition(textOffset);
}

/// <summary>
/// Processes the input from a controller / keyboard and updates the CheckBox as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool CheckBox::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		m_checkBoxRect.setOutlineColor(sf::Color::Cyan); // Set the outline color to Cyan if the Widget is out of focus
		return false;
	}
	else
	{
		m_checkBoxRect.setOutlineColor(sf::Color::Magenta); // Otherwise set the color to Magenta
		if (controller.isButtonPressed(XBOX360_UP) // Up input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_up != nullptr)
			{
				m_up->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the check box to be out of focus
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN) // Down input (see up input)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_down != nullptr)
			{
				m_down->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_LEFT) // Left input (see up input)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_left != nullptr)
			{
				m_left->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT) // Right input (see up input)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_right != nullptr)
			{
				m_right->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A) // A input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			m_state = !m_state; // Flip the state of the checkbox
			try
			{
				stateSwitch();
			}
			catch (const std::bad_function_call &e)
			{
				std::cout << "CHECKBOX:: Bad function call" << std::endl;
			}
			if (m_state)
			{
				m_checkBoxRect.setFillColor(sf::Color::Blue); // Set the fill color to Blue if the box is checked
			}
			else
			{
				m_checkBoxRect.setFillColor(sf::Color::White); // oTherwise set the color White
			}
		}
	}
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void CheckBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_checkBoxRect); // Draw the checkBoxRect
	Label::draw(target, states); // Draw the inherited Label
}
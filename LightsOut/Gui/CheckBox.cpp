#include "CheckBox.h"
 
CheckBox::CheckBox() : Label("", nullptr), selectSound(sf::Sound()) {}

/// <summary>
/// Constructor function for the CheckBox class
/// </summary>
/// <param name="textIn">Text to be displayed by the check Box object's inherited label</param>
/// <param name="parent">parent widget to the CheckBox object</param>
/// <param name="positionIn">position of the Check Box</param>
/// <param name="characterSize">Size of the Characters to be used by the font when drawing text</param>
/// <param name="boxWidth">Width of the Check Box</param>
/// <param name="boxHeight">Height of the Chec Box</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
CheckBox::CheckBox(sf::Sound &selectSoundIn, const std::string & textIn, Widget * parent, sf::Vector2f & positionIn, int characterSize,
		float boxWidth, float boxHeight, sf::Vector2f &startPos, sf::Vector2f &endPos) 
	: Label(textIn, parent, characterSize),
	selectSound(selectSoundIn)
{
	widgetPos = positionIn; // Set the position in the base class
	widgetStartPos = startPos;
	widgetEndPos = endPos;
	// Set the position, size, colours and outlines of the CheckBox
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

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
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
				selectSound.play();
				m_up->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the check box to be out of focus
				try
				{
					up();
				}
				catch (const std::bad_function_call &e)
				{
					std::cout << "CHECKBOX:: Bad function call" << std::endl;
				}
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN) // Down input (see up input)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_down != nullptr)
			{
				selectSound.play();
				m_down->promoteFocus();
				demoteFocus();
				try
				{
					down();
				}
				catch (const std::bad_function_call &e)
				{
					std::cout << "CHECKBOX:: Bad function call" << std::endl;
				}
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_LEFT) // Left input (see up input)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_left != nullptr)
			{
				selectSound.play();
				m_left->promoteFocus();
				demoteFocus();
				try
				{
					left();
				}
				catch (const std::bad_function_call &e)
				{
					std::cout << "CHECKBOX:: Bad function call" << std::endl;
				}
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT) // Right input (see up input)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_right != nullptr)
			{
				selectSound.play();
				m_right->promoteFocus();
				demoteFocus();
				try
				{
					right();
				}
				catch (const std::bad_function_call &e)
				{
					std::cout << "CHECKBOX:: Bad function call" << std::endl;
				}
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A) // A input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			selectSound.play();
			switchState();
			try
			{
				select();
			}
			catch (const std::bad_function_call &e)
			{
				std::cout << "CHECKBOX:: Bad function call" << std::endl;
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

/// <summary>
/// Gets the state of the focus, if the check is currently
/// been focused on by the player
/// </summary>
/// <returns>The state of m_hasFocus</returns>
bool CheckBox::getFocus()
{
	return m_hasFocus;
}

/// <summary>
/// Switches the state of the current check box
/// </summary>
void CheckBox::switchState()
{
	m_state = !m_state; // Flip the state of the bool
	if (m_state)
	{
		m_checkBoxRect.setFillColor(sf::Color::Blue); // Set the fill color to Blue if the box is checked
	}
	else
	{
		m_checkBoxRect.setFillColor(sf::Color::White); // oTherwise set the color White
	}
}

/// <summary>
/// Sets the state of the checkbox
/// </summary>
/// <param name="stateIn">The state of the checkbox</param>
void CheckBox::setState(bool stateIn)
{
	if (stateIn)
	{
		switchState();
	}
}

/// <summary>
/// Returns the current state of the checkbox
/// </summary>
/// <returns>The current state of the checkbox</returns>
bool CheckBox::getState()
{
	return m_state;
}
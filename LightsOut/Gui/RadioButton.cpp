#include "RadioButton.h"

/// <summary>
/// Constructor function for the RadioButton class
/// </summary>
/// <param name="textIn">Text to be displayed by the RadioButton object's inherited Label</param>
/// <param name="parent">Parent widget to the RadioButton object</param>
/// <param name="positionIn">Position of the RdaioButton</param>
/// <param name="radGroup">A vector containing radio buttons, considered the radio button group and switching one radio button willaffect them all</param>
/// <param name="characterSize">Size of the Font used for drawing the text in the Label</param>
/// <param name="boxWidth">Width of the RadioButton Box</param>
/// <param name="boxHeight">Height of the RadioButton box</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
RadioButton::RadioButton(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn, const std::string & textIn, Widget * parent, sf::Vector2f & positionIn,
	std::vector<RadioButton *> & radGroup, sf::Vector2f &startPos, sf::Vector2f &endPos, 
	int characterSize, float boxWidth, float boxHeight)
		: Label(textIn, parent, characterSize), m_otherButtons(radGroup),
	selectSound(selectSoundIn),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{
	widgetPos = positionIn; // Set the position of the inherited Widget
	widgetStartPos = startPos;
	widgetEndPos = endPos;
	// Set the position, size, colour and outline of the RadioButton Box
	m_radioButtonRect.setPosition(widgetPos);
	m_radioButtonRect.setSize(sf::Vector2f(boxWidth, boxHeight));
	m_radioButtonRect.setFillColor(sf::Color::White);
	m_radioButtonRect.setOutlineColor(sf::Color::White);
	m_radioButtonRect.setOutlineThickness(3.f);
	// Set the position of the Label
	sf::Vector2f textOffset(widgetPos.x, widgetPos.y - m_radioButtonRect.getGlobalBounds().height); // We offset the Label to be directly above the RadioButton
	m_radioButtonRect.setOrigin(m_radioButtonRect.getLocalBounds().width / 2.0f, m_radioButtonRect.getLocalBounds().height / 2.0f);
	Label::setPosition(textOffset);
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void RadioButton::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_radioButtonRect.setPosition(widgetPos);
	// Set the position of the Label
	sf::Vector2f textOffset(widgetPos.x, widgetPos.y - m_radioButtonRect.getGlobalBounds().height); // We offset the Label to be directly above the RadioButton
	Label::setPosition(textOffset);
}

/// <summary>
/// Processes the input from a controller / keyboard and updates the RadioButton as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool RadioButton::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		m_radioButtonRect.setOutlineColor(noFocusColor); // If the RadioButton is out of focus then set the color to Cyan
		return false;
	}
	else
	{
		m_radioButtonRect.setOutlineColor(focusColor); // Otherwise set it to Magenta
		if (controller.isButtonPressed(XBOX360_UP) // Up input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_up != nullptr)
			{
				selectSound.play();
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
				selectSound.play();
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
				selectSound.play();
				m_left->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // Right input (see up input)
		{
			if (m_right != nullptr)
			{
				selectSound.play();
				m_right->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A) // A input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			selectSound.play();
			for (RadioButton * radioButton : m_otherButtons)
			{
				radioButton->deActivate();
			}
			m_state = true;
			m_radioButtonRect.setFillColor(fillColor);
			try
			{
				select();
			}
			catch (std::bad_function_call)
			{
				std::cout << "RADIOBUTTON:: Bad function call" << std::endl;
			}
		}
	}
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void RadioButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_radioButtonRect); // Draw the radioButton Rectangle
	Label::draw(target, states); // Draw the inherited Label
}

/// <summary>
/// Function simply sets the m_state bolean to false and changes the fillcolor
/// </summary>
void RadioButton::deActivate()
{
	m_radioButtonRect.setFillColor(sf::Color::White); // Change the fill color
	m_state = false; // Set the state to false
}

/// <summary>
/// Simple getter method for the m_state member variable
/// </summary>
/// <returns>The state of the RadioButton</returns>
bool RadioButton::getState() const
{
	return m_state;
}

/// <summary>
/// Function used to set the state of a radiobutton
/// </summary>
/// <param name="stateIn">The state you want to set the radioButton to</param>
void RadioButton::activate()
{
	m_radioButtonRect.setFillColor(fillColor);
	m_state = true;
	for (auto & otherRadioButton : m_otherButtons)
	{
		if (otherRadioButton != this)
		{
			otherRadioButton->deActivate(); // This is done so as to ensure that no two radio buttons in a set are ever on similtaneously
		}
	}
}

/// <summary>
/// Function used to reset all of the colours used by the radio button if those colours are changed
/// </summary>
void RadioButton::setColors()
{
	if (m_hasFocus)
	{
		m_radioButtonRect.setOutlineColor(focusColor);
	}
	else
	{
		m_radioButtonRect.setOutlineColor(noFocusColor);
	}
	if (m_state)
	{
		m_radioButtonRect.setFillColor(fillColor);
	}
	else
	{
		m_radioButtonRect.setFillColor(sf::Color::White);
	}
}
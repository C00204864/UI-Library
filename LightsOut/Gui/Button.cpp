#include "Button.h"

/// <summary>
/// Constructor function for the Button Class
/// </summary>
/// <param name="textIn">Text to be displayed by the button object's inherited label</param>
/// <param name="parent">parent widget of the button</param>
/// <param name="positionIn">Position of the Button</param>
/// <param name="characterSize">Size of the font used for the text</param>
/// <param name="buttonWidth">Width of the button rectangle (Maybe overrided in contructor of unsuitable)</param>
/// <param name="buttonHeight">Hidth of the button rectangle (Maybe overrided in contructor of unsuitable)</param>
Button::Button(const std::string & textIn, Widget * parent, sf::Vector2f & positionIn,
	int characterSize, float buttonWidth, float buttonHeight) :
	Label(textIn, parent, characterSize)
{
	widgetPos = positionIn; // Set the position in the base class
	m_buttonRect.setFillColor(sf::Color::Blue);
	/* Set the position of the inherited label which must be moved slightly 
	   due to the variance in size of the text object with respect to the button rectangle */
	Label::setPosition(sf::Vector2f(widgetPos.x - characterSize / 12.f, widgetPos.y - characterSize / 3.5f)); 
	sf::Vector2f textSize(Label::getText().getGlobalBounds().width + BUTTON_BUFFER, Label::getTextHeight() + BUTTON_BUFFER); // Get the size of the Text bounding Box
	if (buttonWidth < textSize.x)
	{
		buttonWidth = textSize.x; // We alter the buttons dimensions if the text is too big for the provided dimensions
	}
	if (buttonHeight < textSize.y)
	{
		buttonHeight = textSize.y;
	}
	// Set other aspects of the button rectangle
	m_buttonRect.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonRect.setOrigin(m_buttonRect.getLocalBounds().width / 2.0f, m_buttonRect.getLocalBounds().height / 2.0f);
	m_buttonRect.setPosition(widgetPos);
}

/// <summary>
/// Processes the input from a controller / keyboard and updates the Button as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool Button::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		m_buttonRect.setFillColor(sf::Color::Cyan); // Set the Button Rectangle Color to Cyan if not in focus
		return false;
	}
	else
	{
		m_buttonRect.setFillColor(sf::Color::Magenta); //  Otherwise set it to Magenta
		// Check inputs
		if (controller.isButtonPressed(XBOX360_UP) // Up input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_up != nullptr)
			{
				m_up->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the button to be out of focus
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

		try
		{
			if (controller.isButtonPressed(XBOX360_A) // A input
				|| sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				select(); // Call the callback function
				return true;
			}
		}
		catch (std::bad_function_call &e)
		{
			std::cout << "BUTTON:: Bad function call" << std::endl;
		}
	}
}

void Button::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_buttonRect.setPosition(widgetPos);

	Label::setPosition(sf::Vector2f(widgetPos.x - Label::getCharacterSize() / 12.f, 
		widgetPos.y - Label::getCharacterSize() / 3.5f));
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_buttonRect); // Draw the button rectangle
	Label::draw(target, states); // Draw the inherited Label
}
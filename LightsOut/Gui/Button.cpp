#include "Button.h"

/// <summary>
/// 
/// </summary>
/// <param name="textIn"></param>
/// <param name="parent"></param>
/// <param name="positionIn"></param>
/// <param name="characterSize"></param>
/// <param name="buttonWidth"></param>
/// <param name="buttonHeight"></param>


/// <summary>
/// Constructor function for the Button Class
/// </summary>
/// <param name="focusColorIn">The colour of the button when in focus</param>
/// <param name="noFocusColorIn">The colour of the button when not in focus</param>
/// <param name="fillColorIn">not currently used</param>
/// <param name="selectSoundIn">The sound played by the button</param>
/// <param name="textIn">Text to be displayed by the button object's inherited label</param>
/// <param name="parent">parent widget of the button</param>
/// <param name="positionIn">Position of the Button</param>
/// <param name="characterSize">Size of the font used for the text</param>
/// <param name="buttonWidth">Width of the button rectangle (Maybe overrided in contructor of unsuitable)</param>
/// <param name="buttonHeight">Height of the button rectangle (Maybe overrided in contructor of unsuitable)</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
Button::Button(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn, const std::string & textIn, Widget * parent, sf::Vector2f &positionIn, int characterSize, float buttonWidth, float buttonHeight, sf::Vector2f &startPos, sf::Vector2f &endPos)
	: Label(textIn, parent, characterSize),
	selectSound(selectSoundIn),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{
	widgetPos = positionIn; // Set the position in the base class
	widgetStartPos = startPos;
	widgetEndPos = endPos;
	m_buttonRect.setFillColor(sf::Color::Blue);
	/* 
		Set the position of the inherited label which must be moved slightly 
	    due to the variance in size of the text object with respect to the button rectangle 
	*/
	m_buttonRect.setPosition(widgetPos); // Set the position now as the base widgets position will be reset by setting the Label position
	Label::setPosition(sf::Vector2f(getPosition().x - characterSize / 12.f, getPosition().y - characterSize / 3.5f));
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
	sf::Vector2f pos = getStartPos();
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
		m_buttonRect.setFillColor(noFocusColor); // Set the Button Rectangle Color to Cyan if not in focus
		return false;
	}
	else
	{
		m_buttonRect.setFillColor(focusColor); //  Otherwise set it to Magenta
		// Check inputs
		if (controller.isButtonPressed(XBOX360_UP) // Up input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_up != nullptr)
			{
				selectSound.play();
				m_up->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the button to be out of focus
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN) // Down input
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
		if (controller.isButtonPressed(XBOX360_LEFT) // Left input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_left != nullptr)
			{
				selectSound.play();
				m_left->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the button to be out of focus
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT) // Right input 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_right != nullptr)
			{
				selectSound.play();
				m_right->promoteFocus();
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
		{// The callback function may not be assinged here.
		}
	}
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void Button::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_buttonRect.setPosition(widgetPos); // Set the rectangle
	Label::setPosition(sf::Vector2f(getPosition().x - Label::getCharacterSize() / 12.f,
		getPosition().y - Label::getCharacterSize() / 3.5f)); // Set the label
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

/// <summary>
/// Function used to set the colors of the button depending on whether 
/// it is in focus or not (buttons only use two colors)
/// </summary>
void Button::setColors()
{
	if (m_hasFocus)
	{
		m_buttonRect.setFillColor(focusColor);
	}
	else
	{
		m_buttonRect.setFillColor(noFocusColor);
	}
}
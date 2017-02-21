#include "GamePlay.h"

/// <summary>
/// Default constructor function for the GamePlay class
/// </summary>
GamePlay::GamePlay(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &selectSoundIn)
	: transitionIn(true),
	selectSound(selectSoundIn),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{}

/// <summary>
/// Default destructor function for the GamePlay class
/// </summary>
GamePlay::~GamePlay() {}

/// <summary>
/// Initialize function allows each GUI element and member variable to be initialised
/// </summary>
/// <param name="gridSizeIn">The width / length of the grid of check boxes used in the game</param>
void GamePlay::init(int gridSizeIn)
{
	// Initialise member variables and objects
	gridSize = gridSizeIn;
	initArray(gridSizeIn); // Initials=ise the array of checkboxes
	selectedIndex = 0;
	m_moves = 0;
	m_timeInSeconds = 0;
	m_movesLabel = new Label("", nullptr, 30, sf::Vector2f(sf::Vector2f(260, 650)), sf::Vector2f(400.0f, 900.0f));
	m_timeLabel = new Label("", nullptr, 30, sf::Vector2f(sf::Vector2f(460, 650)), sf::Vector2f(400.0f, 900.0f));
	m_gui.add(m_movesLabel);
	m_gui.add(m_timeLabel);
	m_pcheckBoxArray[0]->promoteFocus();
}

/// <summary>
/// Function simply specialises the initialisation of the array of checkBoxes used as the play field
/// </summary>
/// <param name="gridSize">The width / length of the grid used for the play field</param>
void GamePlay::initArray(int gridSize)
{
	srand(time(NULL));
	arrayLength = gridSize * gridSize;
	float buttonSize = BUTTON_SIZE_NUMERATOR / (gridSize - 1);
	m_pcheckBoxArray = new CheckBox*[arrayLength];
	for (int i = 0; i < arrayLength; i++)
	{
		m_pcheckBoxArray[i] = new CheckBox(focusColor, noFocusColor, fillColor, selectSound, "", nullptr, sf::Vector2f(400.0f - rand() % 1400, 900.0f + rand() % 1900),
			10, buttonSize, buttonSize, posCalc(gridSize, i), sf::Vector2f(400.0f - rand() % 1400, 900.0f + rand() % 1900)); // Create the check box
		// Bind callback functions
		m_pcheckBoxArray[i]->select = std::bind(&GamePlay::switchArea, this);
		m_pcheckBoxArray[i]->up = std::bind(&GamePlay::selectedUp, this);
		m_pcheckBoxArray[i]->down = std::bind(&GamePlay::selectedDown, this);
		m_pcheckBoxArray[i]->left = std::bind(&GamePlay::selectedLeft, this);
		m_pcheckBoxArray[i]->right = std::bind(&GamePlay::selectedRight, this);
		m_pcheckBoxArray[i]->setState(rand() % 2); // Randomise the state, Booleans will accept 1's or 0's as values
		m_gui.add(m_pcheckBoxArray[i]); // Add the check box to the GUI object
	}
	// Assign the directional counterparts of the relevant check box
	for (int i = 0; i < arrayLength; i++)
	{
		if (i % gridSize != 0) // Check if the element exists
		{
			m_pcheckBoxArray[i]->m_left = m_pcheckBoxArray[i - 1]; // -1 for left
		}
		if (i % gridSize != gridSize - 1)
		{
			m_pcheckBoxArray[i]->m_right = m_pcheckBoxArray[i + 1]; // +1 for right
		}
		if (i - gridSize >= 0)
		{
			m_pcheckBoxArray[i]->m_up = m_pcheckBoxArray[i - gridSize]; // -gridSize for up
		}
		if (i + gridSize < arrayLength)
		{
			m_pcheckBoxArray[i]->m_down = m_pcheckBoxArray[i + gridSize]; // +gridSize for down
		}
	}
}

/// <summary>
/// Update function simply updates the GUI and text of the Labels (time and moves completed)
/// </summary>
/// <param name="controller">XboxController object used for cheecking the controller input</param>
void GamePlay::update(XboxController & controller)
{
	m_gui.processInput(controller); // Update the GUI based on controller input
	// Update the texts of the Labels
	m_timeInSeconds = timeTotal.getElapsedTime().asSeconds();
	std::stringstream ss;
	ss << MOVES << m_moves;
	m_movesLabel->setText(ss.str());
	ss.str(std::string());
	ss << TIME << m_timeInSeconds;
	m_timeLabel->setText(ss.str());

	if (transitionIn)
	{
		if (interpolation >= 1.0f)
		{
			interpolation = 1.0f;
			transitionIn = false;
			timeTotal.restart(); // Start the clock
		}

		m_gui.transitionIn(0.010f, interpolation);
	}
}

/// <summary>
/// Draw the GamePlay Screen
/// </summary>
/// <param name="window">window used for drawing the GUI</param>
void GamePlay::render(sf::RenderWindow &window)
{
	window.draw(m_gui);
}

/// <summary>
/// Private Function used to calculate the position of a che3ckbox in the grid based on
/// the gridsize, constants associated as well as the iteration passed into the function
/// </summary>
/// <param name="gridSize">size (width) ogf the game field</param>
/// <param name="i">iteration</param>
/// <returns>sf::Vector2f position of the check box</returns>
sf::Vector2f GamePlay::posCalc(float gridSize, int i)
{
	float xPos = INIT_X + (((BUTTON_SIZE_NUMERATOR / (gridSize - 1)) + (SPACING / (gridSize - 1)))) * (i % static_cast<int>(gridSize));
	float yPos = INIT_Y + (((BUTTON_SIZE_NUMERATOR / (gridSize - 1)) + (SPACING / (gridSize - 1)))) * (i / static_cast<int>(gridSize));
	return sf::Vector2f(xPos, yPos);
}

/// <summary>
/// Function used to switch the states all of the adjacent check boxes as well as the selected checkbox
/// </summary>
void GamePlay::switchArea()
{
	m_moves++; // Increment the amount of moves taken
	// Use dynamic_cast to convert the Widget *'s to CheckBox *'s
	CheckBox * left = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_left);
	CheckBox * right = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_right);
	CheckBox * up = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_up);
	CheckBox * down = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_down);
	// Switch the states of each adjacent if the adjacent isn't null
	if (left != nullptr)
	{
		left->switchState();
	}
	if (right != nullptr)
	{
		right->switchState();
	}
	if (up != nullptr)
	{
		up->switchState();
	}
	if (down != nullptr)
	{
		down->switchState();
	}
	if (checkWin())
	{
		std::cout << "winner winner chicken dinner"; // Do Nothing... Insert code for switching Game state here (Liam wuz here 2k17) <--->
		m_playerWon = true;
	}
}

/// <summary>
/// Function used to check whether the game has been beaten
/// </summary>
/// <returns>boolean win state of the game</returns>
bool GamePlay::checkWin()
{
	for (int i = 0; i < arrayLength; i++)
	{
		if (m_pcheckBoxArray[i]->getState())
		{
			return false; // Return false if a square is on
		}
	}
	return true; // Otherwise return true;
}

bool GamePlay::hasPlayerWon()
{
	return m_playerWon;
}

/// <summary>
/// changes the selected index to the index of the check box above it
/// </summary>
void GamePlay::selectedUp()
{
	selectedIndex -= gridSize;
}

/// <summary>
/// changes the selected index to the index of the check box below it
/// </summary>
void GamePlay::selectedDown()
{
	selectedIndex += gridSize;
}

/// <summary>
/// changes the selected index to the index of the check box to the left of it
/// </summary>
void GamePlay::selectedLeft()
{
	selectedIndex--;
}

/// <summary>
/// changes the selected index to the index of the check box to the right of it
/// </summary>
void GamePlay::selectedRight()
{
	selectedIndex++;
}

void GamePlay::reset(int gridSize)
{
	transitionIn = true;
	interpolation = 0.0f;
	m_playerWon = false;
}
#include "GamePlay.h"

/// <summary>
/// 
/// </summary>
GamePlay::GamePlay() {}

GamePlay::~GamePlay() {}

void GamePlay::init(int gridSizeIn)
{
	gridSize = gridSizeIn;
	initArray(gridSizeIn);
	selectedIndex = 0;
	m_moves = 0;
	m_timeInSeconds = 0;
	m_movesLabel = new Label("", nullptr, 30);
	m_timeLabel = new Label("", nullptr, 30);
	m_gui.add(m_movesLabel);
	m_gui.add(m_timeLabel);
	m_movesLabel->setPosition(sf::Vector2f(260, 650));
	m_timeLabel->setPosition(sf::Vector2f(460, 650));
	m_pcheckBoxArray[0]->promoteFocus();
	timeTotal.restart();
}

void GamePlay::initArray(int gridSize)
{
	srand(time(NULL));
	arrayLength = gridSize * gridSize;
	float buttonSize = BUTTON_SIZE_NUMERATOR / (gridSize - 1);
	m_pcheckBoxArray = new CheckBox*[arrayLength];
	for (int i = 0; i < arrayLength; i++)
	{
		m_pcheckBoxArray[i] = new CheckBox("", nullptr, posCalc(gridSize, i), 10, buttonSize, buttonSize);
		m_pcheckBoxArray[i]->select = std::bind(&GamePlay::switchArea, this);
		m_pcheckBoxArray[i]->up = std::bind(&GamePlay::selectedUp, this);
		m_pcheckBoxArray[i]->down = std::bind(&GamePlay::selectedDown, this);
		m_pcheckBoxArray[i]->left = std::bind(&GamePlay::selectedLeft, this);
		m_pcheckBoxArray[i]->right = std::bind(&GamePlay::selectedRight, this);
		m_pcheckBoxArray[i]->setState(rand() % 2); // Booleans will accept 1's or 0's as values
		m_gui.add(m_pcheckBoxArray[i]);
	}
	for (int i = 0; i < arrayLength; i++)
	{
		if (i % gridSize != 0)
		{
			m_pcheckBoxArray[i]->m_left = m_pcheckBoxArray[i - 1];
		}
		if (i % gridSize != gridSize - 1)
		{
			m_pcheckBoxArray[i]->m_right = m_pcheckBoxArray[i + 1];
		}
		if (i - gridSize >= 0)
		{
			m_pcheckBoxArray[i]->m_up = m_pcheckBoxArray[i - gridSize];
		}
		if (i + gridSize < arrayLength)
		{
			m_pcheckBoxArray[i]->m_down = m_pcheckBoxArray[i + gridSize];
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="controller"></param>
void GamePlay::update(XboxController & controller)
{
	m_gui.processInput(controller);
	m_timeInSeconds = timeTotal.getElapsedTime().asSeconds();
	std::stringstream ss;
	ss << MOVES << m_moves;
	m_movesLabel->setText(ss.str());
	ss.str(std::string());
	ss << TIME << m_timeInSeconds;
	m_timeLabel->setText(ss.str());

}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void GamePlay::render(sf::RenderWindow &window)
{
	window.draw(m_gui);
}

sf::Vector2f GamePlay::posCalc(float gridSize, int i)
{
	float xPos = INIT_X + (((BUTTON_SIZE_NUMERATOR / (gridSize - 1)) + (SPACING / (gridSize - 1)))) * (i % static_cast<int>(gridSize));
	float yPos = INIT_Y + (((BUTTON_SIZE_NUMERATOR / (gridSize - 1)) + (SPACING / (gridSize - 1)))) * (i / static_cast<int>(gridSize));
	return sf::Vector2f(xPos, yPos);
}

void GamePlay::switchArea()
{
	m_moves++;
	CheckBox * left = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_left);
	CheckBox * right = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_right);
	CheckBox * up = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_up);
	CheckBox * down = dynamic_cast<CheckBox *>(m_pcheckBoxArray[selectedIndex]->m_down);
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
		std::cout << "winner winner chicken dinner"; // Do Nothing... Insert code for switching Game state here (Liam wuz here 2k17)
	}
}

bool GamePlay::checkWin()
{
	for (int i = 0; i < arrayLength; i++)
	{
		if (m_pcheckBoxArray[i]->getState())
		{
			return false;
		}
	}
	return true;
}

void GamePlay::selectedUp()
{
	selectedIndex -= gridSize;
}
void GamePlay::selectedDown()
{
	selectedIndex += gridSize;
}
void GamePlay::selectedLeft()
{
	selectedIndex--;
}
void GamePlay::selectedRight()
{
	selectedIndex++;
}
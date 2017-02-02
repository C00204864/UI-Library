#include "OpitionsScreen.h"

/// <summary>
/// 
/// </summary>
OptionsScreen::OptionsScreen()
{
	volume = new Slider("Music Volume", nullptr, sf::Vector2f(250.0f, 50.0f), 18, 200.0f);
	effects = new Slider("Effects Volume", nullptr, sf::Vector2f(250.0f, 150.0f), 18, 200.0f);
	other_1 = new Slider("other_1", nullptr, sf::Vector2f(250.0f, 250.0f), 18, 200.0f);
	other_2 = new Slider("other_2", nullptr, sf::Vector2f(250.0f, 350.0f), 18, 200.0f);
	applyButton = new Button("Apply", nullptr, sf::Vector2f(250.0f, 450.0f), 30);
	//radioButton = new RadioButton("Radio button 1", nullptr, sf::Vector2f(250.0f, 500.0f),);
	radioButtons.push_back(new RadioButton("Clinton", nullptr, sf::Vector2f(250.0f, 550.0f), radioButtons));
	radioButtons.push_back(new RadioButton("Trump", nullptr, sf::Vector2f(350.0f, 550.0f), radioButtons));
	checkBox = new CheckBox("Sanders", nullptr, sf::Vector2f(250.0f, 700.0f));

	volume->m_down = effects;
	effects->m_up = volume;
	effects->m_down = other_1;

	// NOTE(Darren): This is for testing only
	other_1->m_up = effects;
	other_1->m_down = other_2;
	other_2->m_up = other_1;
	other_2->m_down = applyButton;
	applyButton->m_up = other_2;
	radioButtons.at(0)->m_up = applyButton;
	applyButton->m_down = radioButtons.at(0);
	radioButtons.at(0)->m_right = radioButtons.at(1);
	radioButtons.at(1)->m_left = radioButtons.at(0);
	radioButtons.at(1)->m_up = applyButton;
	radioButtons.at(0)->m_down = checkBox;
	radioButtons.at(1)->m_down = checkBox;
	checkBox->m_up = radioButtons.at(0);

	// Set the first UI element the user has control over to the volume
	volume->promoteFocus();

	// Assingn call back function here
	volume->increase = std::bind(&OptionsScreen::volumeUpSliderMusic, this);
	volume->decrease = std::bind(&OptionsScreen::volumeDownSliderMusic, this);
	effects->increase = std::bind(&OptionsScreen::volumeUpSliderEffects, this);
	effects->decrease = std::bind(&OptionsScreen::volumeDownSliderEffects, this);

	// NOTE(Darren): Again, all for testing
	other_1->increase = std::bind(&OptionsScreen::volumeUpSliderMusic, this);
	other_1->decrease = std::bind(&OptionsScreen::volumeDownSliderMusic, this);
	other_2->increase = std::bind(&OptionsScreen::volumeUpSliderEffects, this);
	other_2->decrease = std::bind(&OptionsScreen::volumeDownSliderEffects, this);
	// NOTE(Darren): Testing apply button callback
	applyButton->select = std::bind(&OptionsScreen::volumeDownSliderEffects, this);
}

/// <summary>
/// 
/// </summary>
OptionsScreen::~OptionsScreen() { }

/// <summary>
/// Initalises all Gui elements
/// </summary>
void OptionsScreen::initialise()
{
	m_gui.add(volume);
	m_gui.add(effects);
	m_gui.add(other_1);
	m_gui.add(other_2);
	m_gui.add(applyButton);
	for (RadioButton * radioButton : radioButtons)
	{
		m_gui.add(radioButton);
	}
	m_gui.add(checkBox);
}

/// <summary>
/// 
/// </summary>
/// <param name="controller"></param>
void OptionsScreen::update(XboxController &controller)
{
	m_gui.processInput(controller);
}

void OptionsScreen::volumeUpSliderMusic()
{
	std::cout << "volumeUpMusic callback" << std::endl;
}

void OptionsScreen::volumeDownSliderMusic()
{
	std::cout << "volumeDownMusic callback" << std::endl;
}

void OptionsScreen::volumeUpSliderEffects()
{
	std::cout << "volumeUpEffects callback" << std::endl;
}

void OptionsScreen::volumeDownSliderEffects()
{
	std::cout << "volumeDownEffects callback" << std::endl;
}

/// <summary>
/// Draws everything in the opitions menu
/// </summary>
/// <param name="window">A reference to an instacne of RenderWindow</param>
void OptionsScreen::render(sf::RenderWindow& window)
{
	window.draw(m_gui);
}
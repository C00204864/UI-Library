#include "OpitionsScreen.h"

/// <summary>
/// 
/// </summary>
OptionsScreen::OptionsScreen()
{
	volume = new Slider("Music Volume", nullptr, sf::Vector2f(250.0f, 50.0f), 18, 200.0f);
	effects = new Slider("Effects Volume", nullptr, sf::Vector2f(250.0f, 150.0f), 18, 200.0f);

	volume->m_down = effects;
	effects->m_up = volume;

	// Set the first UI element the user has control over to the volume
	volume->promoteFocus();

	// Assingn call back function here
	volume->increase = std::bind(&OptionsScreen::volumeUpSliderMusic, this);
	volume->decrease = std::bind(&OptionsScreen::volumeDownSliderMusic, this);
	effects->increase = std::bind(&OptionsScreen::volumeUpSliderEffects, this);
	effects->decrease = std::bind(&OptionsScreen::volumeDownSliderEffects, this);
}

/// <summary>
/// 
/// </summary>
OptionsScreen::~OptionsScreen()
{
	// NOTE(Darren): Already deleted
	/*delete volume;
	delete effects;*/
}

/// <summary>
/// 
/// </summary>
void OptionsScreen::initialise()
{
	m_gui.add(volume);
	m_gui.add(effects);
}

/// <summary>
/// 
/// </summary>
/// <param name="controller"></param>
void OptionsScreen::update(XboxController &controller)
{
	m_gui.processInput(controller);
	//m_gui.update();
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
/// 
/// </summary>
/// <param name="window"></param>
void OptionsScreen::render(sf::RenderWindow& window)
{
	window.draw(m_gui);
}
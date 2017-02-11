#include "OpitionsScreen.h"

/// <summary>
/// 
/// </summary>
OptionsScreen::OptionsScreen(sf::Sound &backingTrackIn, sf::Sound &selectSoundIn)
	: transitionIn(true),
	backingTrack(backingTrackIn),
	selectSound(selectSoundIn)
{
	// TODO(Darren): Rename these variables
	m_optionsTitle = new Label("Options", nullptr, 80, sf::Vector2f(400.0f, 50.0f), sf::Vector2f(400.0f, 900.0f));
	m_optionsTitle->setPosition(sf::Vector2f(400.0f, 900.0f));
	volume = new Slider(selectSound, std::string("Music Volume"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 180.0f), sf::Vector2f(400.0f, 900.0f));
	effects = new Slider(selectSound, std::string("Effects Volume"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 250.0f), sf::Vector2f(400.0f, 900.0f));
	checkBox = new CheckBox(selectSound, "Mute", nullptr, sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f,
		sf::Vector2f(400.0f, 320.0f), sf::Vector2f(400.0f, 900.0f));
	m_difficultyTitle = new Label("Difficulty", nullptr, 35, sf::Vector2f(400.0f, 370.0f), sf::Vector2f(400.0f, 900.0f));
	radioButtons.push_back(new RadioButton(selectSound, "3 x 3", nullptr, sf::Vector2f(400.0f, 900.0f), radioButtons,
		sf::Vector2f(300.0f, 450.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	radioButtons.push_back(new RadioButton(selectSound, "4 x 4", nullptr, sf::Vector2f(400.0f, 900.0f), radioButtons,
		sf::Vector2f(400.0f, 450.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	radioButtons.push_back(new RadioButton(selectSound, "7 x 7", nullptr, sf::Vector2f(400.0f, 900.0f), radioButtons,
		sf::Vector2f(500.0f, 450.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	m_redSlider = new Slider(selectSound, std::string("Red"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 540.0f), sf::Vector2f(400.0f, 900.0f));
	m_greenSlider = new Slider(selectSound, std::string("Green"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 610.0f), sf::Vector2f(400.0f, 900.0f));
	m_blueSlider = new Slider(selectSound, std::string("Blue"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 680.0f), sf::Vector2f(400.0f, 900.0f));
	applyButton = new Button(selectSound, "Apply", nullptr, sf::Vector2f(400.0f, 900.0f), 30, 100, 40.0f,
		sf::Vector2f(400.0f, 750.0f), sf::Vector2f(400.0f, 900.0f));

	volume->m_up = applyButton;
	volume->m_down = effects;
	effects->m_up = volume;
	effects->m_down = checkBox;
	checkBox->m_down = radioButtons.at(0);
	checkBox->m_up = effects;
	radioButtons.at(0)->m_right = radioButtons.at(1);
	radioButtons.at(1)->m_left = radioButtons.at(0);
	radioButtons.at(1)->m_right = radioButtons.at(2);
	radioButtons.at(2)->m_left = radioButtons.at(1);
	radioButtons.at(0)->m_up = checkBox;
	radioButtons.at(1)->m_up = checkBox;
	radioButtons.at(2)->m_up = checkBox;
	radioButtons.at(0)->m_down = m_redSlider;
	radioButtons.at(1)->m_down = m_redSlider;
	radioButtons.at(2)->m_down = m_redSlider;

	m_redSlider->m_up = radioButtons.at(0);
	m_redSlider->m_down = m_greenSlider;
	m_greenSlider->m_up = m_redSlider;
	m_greenSlider->m_down = m_blueSlider;
	m_blueSlider->m_down = applyButton;
	m_blueSlider->m_up = m_greenSlider;
	applyButton->m_up = m_blueSlider;
	applyButton->m_down = volume;

	// Set the first UI element the user has control over to the volume
	volume->promoteFocus();

	// Assingn call back function here
	volume->increase = std::bind(&OptionsScreen::volumeUpSliderMusic, this);
	volume->decrease = std::bind(&OptionsScreen::volumeDownSliderMusic, this);
	effects->increase = std::bind(&OptionsScreen::volumeUpSliderEffects, this);
	effects->decrease = std::bind(&OptionsScreen::volumeDownSliderEffects, this);
	checkBox->select = std::bind(&OptionsScreen::checkBoxSwitched, this);

	// NOTE(Darren): Again, all for testing
	m_redSlider->increase = std::bind(&OptionsScreen::volumeUpSliderMusic, this);
	m_redSlider->decrease = std::bind(&OptionsScreen::volumeDownSliderMusic, this);
	m_greenSlider->increase = std::bind(&OptionsScreen::volumeUpSliderEffects, this);
	m_greenSlider->decrease = std::bind(&OptionsScreen::volumeDownSliderEffects, this);
	// NOTE(Darren): Testing apply button callback
	applyButton->select = std::bind(&OptionsScreen::applyButtonSelected, this);
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
	m_gui.add(m_optionsTitle);
	m_gui.add(volume);
	m_gui.add(effects);
	m_gui.add(checkBox);
	m_gui.add(m_difficultyTitle);
	for (RadioButton * radioButton : radioButtons)
	{
		m_gui.add(radioButton);
	}
	m_gui.add(m_redSlider);
	m_gui.add(m_greenSlider);
	m_gui.add(m_blueSlider);
	m_gui.add(applyButton);
}

void OptionsScreen::reset()
{
	// Reset the top Gui elements to be in focus
	volume->promoteFocus();

	m_optionsTitle->setPosition(sf::Vector2f(400.0f, 900.0f));
	volume->setPosition(sf::Vector2f(400.0f, 900.0f));
	effects->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_redSlider->setPosition(sf::Vector2f(400.0f, 900.0f));
	m_greenSlider->setPosition(sf::Vector2f(400.0f, 900.0f));
	applyButton->setPosition(sf::Vector2f(400.0f, 900.0f));
	radioButtons.at(0)->setPosition(sf::Vector2f(400.0f, 900.0f));
	radioButtons.at(1)->setPosition(sf::Vector2f(400.0f, 900.0f));
	checkBox->setPosition(sf::Vector2f(400.0f, 900.0f));

	m_backToMenu = false;
	transitionIn = true;
	interpolation = 0.0f;
	m_applyButtonPressed = false;
}

/// <summary>
/// 
/// </summary>
/// <param name="controller"></param>
void OptionsScreen::update(XboxController &controller)
{
	m_gui.processInput(controller);

	if (controller.isButtonPressed(XBOX360_BACK))
	{
		m_applyButtonPressed = true;
	}

	if (m_applyButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			std::cout << "Transition play finished" << std::endl;
			m_backToMenu = true;
			interpolation = 0.0f;
		}
	}

	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation);

		if (interpolation >= 1.0f)
		{
			std::cout << "Transition play finished" << std::endl;
			interpolation = 0.0f;
			transitionIn = false;
		}
	}
}

void OptionsScreen::volumeUpSliderMusic()
{
	if (!checkBox->getState())
	{
		std::cout << "volumeUpMusic callback" << std::endl;
		backingTrack.setVolume(100 * volume->getPercentageFull());
	}
}

void OptionsScreen::volumeDownSliderMusic()
{
	if (!checkBox->getState())
	{
		std::cout << "volumeDownMusic callback" << std::endl;
		backingTrack.setVolume(100 * volume->getPercentageFull());
	}
}

void OptionsScreen::volumeUpSliderEffects()
{
	if (!checkBox->getState())
	{
		std::cout << "volumeUpEffects callback" << std::endl;
		selectSound.setVolume(100 * (effects->getPercentageFull()));
	}	
}

void OptionsScreen::volumeDownSliderEffects()
{
	if (!checkBox->getState())
	{
		std::cout << "volumeDownEffects callback" << std::endl;
		selectSound.setVolume(100 * (effects->getPercentageFull()));
	}
}

void OptionsScreen::applyButtonSelected()
{
	m_applyButtonPressed = true;
	applyButton->demoteFocus();
}

void OptionsScreen::checkBoxSwitched()
{
	if (checkBox->getState())
	{
		backingTrack.setVolume(0);
		selectSound.setVolume(0);
	}
	else
	{
		backingTrack.setVolume(100 * (volume->getPercentageFull()));
		selectSound.setVolume(100 * (effects->getPercentageFull()));
	}
}

bool OptionsScreen::getChangeStateMenu()
{
	return m_backToMenu;
}

/// <summary>
/// Draws everything in the opitions menu
/// </summary>
/// <param name="window">A reference to an instacne of RenderWindow</param>
void OptionsScreen::render(sf::RenderWindow& window)
{
	window.draw(m_gui);
}
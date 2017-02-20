#include "OpitionsScreen.h"

/// <summary>
/// 
/// </summary>
OptionsScreen::OptionsScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &backingTrackIn, sf::Sound &selectSoundIn)
	: transitionIn(true),
	backingTrack(backingTrackIn),
	selectSound(selectSoundIn),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn)
{
	// TODO(Darren): Rename these variables
	m_optionsTitle = new Label("Options", nullptr, 80, sf::Vector2f(400.0f, 30.0f), sf::Vector2f(400.0f, 900.0f));
	m_optionsTitle->setPosition(sf::Vector2f(400.0f, 900.0f));
	volume = new Slider(focusColor, noFocusColor, fillColor, selectSound, std::string("Music Volume"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 140.0f), sf::Vector2f(400.0f, 900.0f));
	effects = new Slider(focusColor, noFocusColor, fillColor, selectSound, std::string("Effects Volume"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 190.0f), sf::Vector2f(400.0f, 900.0f));
	checkBox = new CheckBox(focusColor, noFocusColor, fillColor, selectSound, "Mute", nullptr, sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f,
		sf::Vector2f(400.0f, 260.0f), sf::Vector2f(400.0f, 900.0f));
	m_difficultyTitle = new Label("Difficulty", nullptr, 35, sf::Vector2f(400.0f, 300.0f), sf::Vector2f(400.0f, 900.0f));
	difficultyRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "3 x 3", nullptr, sf::Vector2f(400.0f, 900.0f), difficultyRadioButtons,
		sf::Vector2f(250.0f, 380.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	difficultyRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "5 x 5", nullptr, sf::Vector2f(400.0f, 900.0f), difficultyRadioButtons,
		sf::Vector2f(400.0f, 380.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	difficultyRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "7 x 7", nullptr, sf::Vector2f(400.0f, 900.0f), difficultyRadioButtons,
		sf::Vector2f(550.0f, 380.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	colorRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "Fill", nullptr, sf::Vector2f(400.0f, 900.0f), colorRadioButtons,
		sf::Vector2f(250.0f, 450.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	colorRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "Selected", nullptr, sf::Vector2f(400.0f, 900.0f), colorRadioButtons,
		sf::Vector2f(400.0f, 450.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	colorRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "de-Selected", nullptr, sf::Vector2f(400.0f, 900.0f), colorRadioButtons,
		sf::Vector2f(550.0f, 450.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	m_redSlider = new Slider(focusColor, noFocusColor, fillColor, selectSound, std::string("Red"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 580.0f), sf::Vector2f(400.0f, 900.0f));
	m_greenSlider = new Slider(focusColor, noFocusColor, fillColor, selectSound, std::string("Green"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 630.0f), sf::Vector2f(400.0f, 900.0f));
	m_blueSlider = new Slider(focusColor, noFocusColor, fillColor, selectSound, std::string("Blue"), nullptr, sf::Vector2f(400.0f, 900.0f), 18, 200.0f, 15.0f,
		sf::Vector2f(400.0f, 680.0f), sf::Vector2f(400.0f, 900.0f));
	applyButton = new Button(focusColor, noFocusColor, fillColor, selectSound, "Apply", nullptr, sf::Vector2f(400.0f, 900.0f), 30, 100, 40.0f,
		sf::Vector2f(400.0f, 740.0f), sf::Vector2f(400.0f, 900.0f));

	// Directional Changes
	volume->m_up = applyButton;
	volume->m_down = effects;
	effects->m_up = volume;
	effects->m_down = checkBox;
	checkBox->m_down = difficultyRadioButtons.at(0);
	checkBox->m_up = effects;
	difficultyRadioButtons.at(0)->m_right = difficultyRadioButtons.at(1);
	difficultyRadioButtons.at(1)->m_left = difficultyRadioButtons.at(0);
	difficultyRadioButtons.at(1)->m_right = difficultyRadioButtons.at(2);
	difficultyRadioButtons.at(2)->m_left = difficultyRadioButtons.at(1);
	difficultyRadioButtons.at(0)->m_up = checkBox;
	difficultyRadioButtons.at(1)->m_up = checkBox;
	difficultyRadioButtons.at(2)->m_up = checkBox;
	difficultyRadioButtons.at(0)->m_down = colorRadioButtons.at(0);
	difficultyRadioButtons.at(1)->m_down = colorRadioButtons.at(1);
	difficultyRadioButtons.at(2)->m_down = colorRadioButtons.at(2);
	colorRadioButtons.at(0)->m_right = colorRadioButtons.at(1);
	colorRadioButtons.at(1)->m_left = colorRadioButtons.at(0);
	colorRadioButtons.at(1)->m_right = colorRadioButtons.at(2);
	colorRadioButtons.at(2)->m_left = colorRadioButtons.at(1);
	colorRadioButtons.at(0)->m_up = difficultyRadioButtons.at(0);
	colorRadioButtons.at(1)->m_up = difficultyRadioButtons.at(1);
	colorRadioButtons.at(2)->m_up = difficultyRadioButtons.at(2);
	colorRadioButtons.at(0)->m_down = m_redSlider;
	colorRadioButtons.at(1)->m_down = m_redSlider;
	colorRadioButtons.at(2)->m_down = m_redSlider;
	m_redSlider->m_up = difficultyRadioButtons.at(0);
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
	m_redSlider->increase = std::bind(&OptionsScreen::setColor, this);
	m_redSlider->decrease = std::bind(&OptionsScreen::setColor, this);
	m_greenSlider->increase = std::bind(&OptionsScreen::setColor, this);
	m_greenSlider->decrease = std::bind(&OptionsScreen::setColor, this);
	m_blueSlider->increase = std::bind(&OptionsScreen::setColor, this);
	m_blueSlider->decrease = std::bind(&OptionsScreen::setColor, this);
	applyButton->select = std::bind(&OptionsScreen::applyButtonSelected, this);

	colorRadioButtons.at(0)->select = std::bind(&OptionsScreen::setColorSliders, this);
	colorRadioButtons.at(1)->select = std::bind(&OptionsScreen::setColorSliders, this);
	colorRadioButtons.at(2)->select = std::bind(&OptionsScreen::setColorSliders, this);
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
	for (RadioButton * radioButton : difficultyRadioButtons)
	{
		m_gui.add(radioButton);
	}
	for (RadioButton * radioButton : colorRadioButtons)
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
	difficultyRadioButtons.at(0)->setPosition(sf::Vector2f(400.0f, 900.0f));
	difficultyRadioButtons.at(1)->setPosition(sf::Vector2f(400.0f, 900.0f));
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

void OptionsScreen::setColorSliders()
{
	if (colorRadioButtons.at(0)->getState())
	{
		std::cout << "-1-" << std::endl;
		m_redSlider->setPercentageFull(fillColor.r / 255.f);
		m_greenSlider->setPercentageFull(fillColor.g / 255.f);
		m_blueSlider->setPercentageFull(fillColor.b / 255.f);
	}
	else if (colorRadioButtons.at(1)->getState())
	{
		std::cout << "-2-" << std::endl;
		m_redSlider->setPercentageFull(focusColor.r / 255.f);
		m_greenSlider->setPercentageFull(focusColor.g / 255.f);
		m_blueSlider->setPercentageFull(focusColor.b / 255.f);
	}
	else
	{
		std::cout << "-3-" << std::endl;
		m_redSlider->setPercentageFull(noFocusColor.r / 255.f);
		m_greenSlider->setPercentageFull(noFocusColor.g / 255.f);
		m_blueSlider->setPercentageFull(noFocusColor.b / 255.f);
	}
}

void OptionsScreen::setColor()
{
	sf::Color *color;
	if (colorRadioButtons.at(0)->getState())
	{
		color  = &fillColor;
	}
	else if (colorRadioButtons.at(1)->getState())
	{
		color = &focusColor;
	}
	else
	{
		color = &noFocusColor;
	}
	if (m_redSlider->getFocus())
	{
		color->r = m_redSlider->getPercentageFull() * 255.f;
	}
	else if (m_greenSlider->getFocus())
	{
		color->g = m_greenSlider->getPercentageFull() * 255.f;
	}
	else
	{
		color->b = m_blueSlider->getPercentageFull() * 255.f;
	}
	m_gui.setColors();
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
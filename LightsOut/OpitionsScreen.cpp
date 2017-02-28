#include "OpitionsScreen.h"

/// <summary>
/// 
/// </summary>
/// <param name="focusColorIn">Focus color of the GUI elements</param>
/// <param name="noFocusColorIn">No focus color of the GUI elements</param>
/// <param name="fillColorIn">Fill color of the GUI elements</param>
/// <param name="backingTrackIn">The backing music for the game</param>
/// <param name="selectSoundIn">The sound for the GUI elements</param>
/// <param name="difficultyIn">The game's difficulty</param>
OptionsScreen::OptionsScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &backingTrackIn, sf::Sound &selectSoundIn, int &difficultyIn)
	: Screen(GameState::Options),
	transitionIn(true),
	backingTrack(backingTrackIn),
	selectSound(selectSoundIn),
	focusColor(focusColorIn),
	noFocusColor(noFocusColorIn),
	fillColor(fillColorIn),
	m_difficulty(difficultyIn)
{
	// Initiaise the GUI elements
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
	m_colorTitle = new Label("Colors", nullptr, 35, sf::Vector2f(400.0f, 430.0f), sf::Vector2f(400.0f, 900.0f));
	colorRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "Fill", nullptr, sf::Vector2f(400.0f, 900.0f), colorRadioButtons,
		sf::Vector2f(250.0f, 520.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	colorRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "Selected", nullptr, sf::Vector2f(400.0f, 900.0f), colorRadioButtons,
		sf::Vector2f(400.0f, 520.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
	colorRadioButtons.push_back(new RadioButton(focusColor, noFocusColor, fillColor, selectSound, "de-Selected", nullptr, sf::Vector2f(400.0f, 900.0f), colorRadioButtons,
		sf::Vector2f(550.0f, 520.0f), sf::Vector2f(400.0f, 900.0f), 22, 30.0f, 30.0f));
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
	m_redSlider->m_up = colorRadioButtons.at(0);
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
	difficultyRadioButtons.at(0)->select = std::bind(&OptionsScreen::changeDifficulty, this);
	difficultyRadioButtons.at(1)->select = std::bind(&OptionsScreen::changeDifficulty, this);
	difficultyRadioButtons.at(2)->select = std::bind(&OptionsScreen::changeDifficulty, this);
	
	// Set one of the radio buttons to be true in the radio button set
	colorRadioButtons.at(0)->activate();
	if (m_difficulty == 3)
	{
		difficultyRadioButtons.at(0)->activate();
	}
	else if (m_difficulty == 5)
	{
		difficultyRadioButtons.at(1)->activate();
	}
	else
	{
		difficultyRadioButtons.at(2)->activate();
	}
	setColorSliders();
	initialise(); // Used to add elements to the GUI object
}

/// <summary>
/// Delete function for the Options Screen class
/// </summary>
OptionsScreen::~OptionsScreen() { }

/// <summary>
/// Initalises all Gui elements
/// </summary>
void OptionsScreen::initialise()
{
	// Add all of the GUI elements to the GUI objects
	m_gui.add(m_optionsTitle);
	m_gui.add(volume);
	m_gui.add(effects);
	m_gui.add(checkBox);
	m_gui.add(m_difficultyTitle);
	m_gui.add(m_colorTitle);
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

/// <summary>
/// function resets the Options Screen after the game state has been changed
/// </summary>
void OptionsScreen::reset()
{
	// Reset the top Gui elements to be in focus
	volume->promoteFocus();
	transitionIn = true;
	interpolation = 0.0f;
	m_applyButtonPressed = false;
}

/// <summary>
/// update function processes input for the options screen
/// </summary>
/// <param name="controller">controller used for processing input</param>
void OptionsScreen::update(XboxController &controller)
{
	m_gui.processInput(controller); // Process input for the GUI object

	if (controller.isButtonPressed(XBOX360_BACK))
	{
		m_applyButtonPressed = true;
	}

	if (m_applyButtonPressed)
	{
		m_gui.transitionOut(0.05f, interpolation); // run a transition out cycle

		if (interpolation >= 1.0f)
		{
			m_nextGameState = GameState::MainMenu; // Change the game state
			interpolation = 0.0f; // Reset the interpolation
			reset(); // Reset this
		}
	}

	if (transitionIn)
	{
		m_gui.transitionIn(0.05f, interpolation); // Run a transition in cycle

		if (interpolation >= 1.0f)
		{
			interpolation = 0.0f; // Reset the interpolation
			transitionIn = false;
		}
	}
}

/// <summary>
/// Function linked to a callback function for thhe volume music slider
/// </summary>
void OptionsScreen::volumeUpSliderMusic()
{
	if (!checkBox->getState())
	{
		backingTrack.setVolume(100 * volume->getPercentageFull()); // Set the volume of the sound
	}
}

/// <summary>
///  Function linked to a callback function for thhe volume music slider
/// </summary>
void OptionsScreen::volumeDownSliderMusic()
{
	if (!checkBox->getState())
	{
		backingTrack.setVolume(100 * volume->getPercentageFull()); // Set the volume of the sound
	}
}

/// <summary>
///  Function linked to a callback function for thhe volume effects slider
/// </summary>
void OptionsScreen::volumeUpSliderEffects()
{
	if (!checkBox->getState())
	{
		selectSound.setVolume(100 * (effects->getPercentageFull())); // Set the volume of the sound
	}	
}

/// <summary>
///  Function linked to a callback function for thhe volume effects slider
/// </summary>
void OptionsScreen::volumeDownSliderEffects()
{
	if (!checkBox->getState())
	{
		selectSound.setVolume(100 * (effects->getPercentageFull())); // Set the volume of the sound
	}
}

/// <summary>
/// Function linked to a callback function for the apply button
/// </summary>
void OptionsScreen::applyButtonSelected()
{
	m_applyButtonPressed = true;
	applyButton->demoteFocus();
}

/// <summary>
/// Function linked to a callback function for the mute check box
/// </summary>
void OptionsScreen::checkBoxSwitched()
{
	if (checkBox->getState())
	{
		// No sound if the check box is on
		backingTrack.setVolume(0);
		selectSound.setVolume(0);
	}
	else
	{
		// Otherwise the sound is set by the sliders
		backingTrack.setVolume(100 * (volume->getPercentageFull()));
		selectSound.setVolume(100 * (effects->getPercentageFull()));
	}
}

/// <summary>
/// Function used for determining the starting positions for each RGB
/// when the colour radio buttons are interacted with
/// </summary>
void OptionsScreen::setColorSliders()
{
	// We set the sliders based on what colour we are altering
	if (colorRadioButtons.at(0)->getState())
	{
		m_redSlider->setPercentageFull(fillColor.r / 255.f); // Set the percentage full to be a percentage based off of RGB values
		m_greenSlider->setPercentageFull(fillColor.g / 255.f);
		m_blueSlider->setPercentageFull(fillColor.b / 255.f);
	}
	else if (colorRadioButtons.at(1)->getState())
	{
		m_redSlider->setPercentageFull(focusColor.r / 255.f);
		m_greenSlider->setPercentageFull(focusColor.g / 255.f);
		m_blueSlider->setPercentageFull(focusColor.b / 255.f);
	}
	else
	{
		m_redSlider->setPercentageFull(noFocusColor.r / 255.f);
		m_greenSlider->setPercentageFull(noFocusColor.g / 255.f);
		m_blueSlider->setPercentageFull(noFocusColor.b / 255.f);
	}
}

/// <summary>
/// Function determines which RGB value of which colour should be changed
/// </summary>
void OptionsScreen::setColor()
{
	sf::Color *color;

	// First we check what color we have to change
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

	// Then we change that color based on what slider changed
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

/// <summary>
/// Function is linked to the call back functions for the difficulty
/// radio buttons
/// </summary>
void OptionsScreen::changeDifficulty()
{
	// Change the difficulty based on what radio button is selected
	if (difficultyRadioButtons.at(0)->getState())
	{
		m_difficulty = 3;
		return;
	}
	else if (difficultyRadioButtons.at(1)->getState())
	{
		m_difficulty = 5;
		return;
	}
	else
	{
		m_difficulty = 7;
		return;
	}
}
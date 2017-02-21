/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef OPITIONS_SCREEN_H
#define OPITIONS_SCREEN_H

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Input\XboxController.h"
#include "Gui\Gui.h"
#include "Gui\Slider.h"
#include "Gui\Button.h"
#include "Gui\RadioButton.h"
#include "Gui\CheckBox.h"

/// The Opitions screen that will be displayed in game
/// 
/// Handles all functionality of the opitions menu, Gui elements, 
/// updating and rendering.
class OptionsScreen
{
public:
	OptionsScreen(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Sound &backingTrackIn, sf::Sound &selectSound);
	~OptionsScreen();
	void initialise();
	void update(XboxController& controller);
	void render(sf::RenderWindow& window);
	bool getChangeStateMenu();
	void reset();
	int getDifficulty() const;
private:
	void volumeUpSliderMusic();
	void volumeDownSliderMusic();
	void volumeUpSliderEffects();
	void volumeDownSliderEffects();
	void applyButtonSelected();
	void checkBoxSwitched();
	void setColorSliders();
	void setColor();
	void changeDifficulty();

	Gui m_gui;
	Label *m_optionsTitle;
	Slider *volume;
	Slider *effects;
	Button *applyButton;
	Slider *m_redSlider;
	Slider *m_greenSlider;
	Slider *m_blueSlider;
	Label *m_difficultyTitle;
	RadioButton *radioButton;
	RadioButton *radioButton_2;
	std::vector<RadioButton*> difficultyRadioButtons;
	std::vector<RadioButton*> colorRadioButtons;
	CheckBox *checkBox;

	bool m_applyButtonPressed;
	bool m_backToMenu;

	bool transitionIn;
	float interpolation;

	sf::Sound &backingTrack;
	sf::Sound &selectSound;
	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;

	int m_difficulty = 3;
};

#endif
/// <summary>
/// @author Darren Sweeney and Liam Hickey
/// @version 1.0
/// </summary>

#ifndef OPITIONS_SCREEN_H
#define OPITIONS_SCREEN_H

#include <SFML\Graphics.hpp>
#include "XboxController.h"
#include "Gui\Gui.h"
#include "Gui\Slider.h"

/// The Opitions screen that will be displayed in game
/// 
/// Handles all functionality of the opitions menu, Gui elements, 
/// updating and rendering.
class OptionsScreen
{
public:
	OptionsScreen();
	~OptionsScreen();

	void initialise();
	void update(XboxController& controller);
	void render(sf::RenderWindow& window);

	Gui m_gui;
	Slider *volume;
	Slider *effects;

private:
	void volumeUpSliderMusic();
	void volumeDownSliderMusic();
	void volumeUpSliderEffects();
	void volumeDownSliderEffects();
};

#endif
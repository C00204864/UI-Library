#ifndef  SCRENMANAGER_H
#define SCREENMANAGER_H

#include "Screen.h"

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();
	void update(XboxController &controller);
	void render(sf::RenderWindow& window);
	void add(Screen *Screen);
private:
	std::vector<Screen *> screens;
	GameState m_gameState;
	int m_currentScreen;
	int gamePlayScreen;
};

#endif


/// <summary>
/// @Authors Darren Sweeney and Liam Hickey
/// @version 1.0
/// @brief Group project which showcases a re-usable UI library in a game form called lights out.
/// 
/// A game where the player has to turn off a square set of lights where each
/// toggled light effects adjacent cells.
/// 
/// Contributions from Authors: https://github.com/PeterLowe/button-game-darren-and-liam/graphs/contributors
/// 
/// Time and Commits: https://github.com/PeterLowe/button-game-darren-and-liam/graphs/punch-card
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "Game.h"

int main()
{
	Game game; // Create the game
	game.run(); // Run the game

	return 0;
}
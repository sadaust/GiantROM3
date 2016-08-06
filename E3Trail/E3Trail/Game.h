#pragma once
#include "Engine.h"
#include "MenuSystem.h"

#define WINDOW_TITLE "E3 Trail"

class Game {
private:
	MenuSystem mainMenu;
	camera cam;
	double fps;
	char buffer[256];
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();
};
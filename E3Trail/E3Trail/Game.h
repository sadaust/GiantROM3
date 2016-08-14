#pragma once
#include "Engine.h"
#include "MenuSystem.h"
#include "Trail.h"

#define WINDOW_TITLE "E3 Trail"

class Game {
private:
	MenuSystem mainMenu;
	camera cam;
	double fps;
	char buffer[256];
	Trail trail;
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();

	void buildMenu(bool credits);
};
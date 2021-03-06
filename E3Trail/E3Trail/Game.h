#pragma once
#include "Engine.h"
#include "MenuSystem.h"
#include "Trail.h"

#define WINDOW_TITLE "E3 Trail"
//static soundStruct youwin;

class Game {
private:
	musicStruct menuMusic;
	MenuSystem mainMenu;
	camera cam;
	double fps;
	char buffer[256];
	DWORD bColor;
	DWORD hColor;
	Trail trail;
	bool drawLogo;
	bool restartMusic;
	spriteStruct logo;
public:
	Game();
	~Game();
	void init();
	bool update();
	void shutdown();

	void buildMenu(bool credits);
};
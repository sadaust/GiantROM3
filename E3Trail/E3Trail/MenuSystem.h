/*===========================
=MenuSystem.h/cpp			=
=by Tyler van Gastel		=
=latest update 11/30/2015	=
=buttons for menus			=
=============================*/
//first revision used a cursor changed to selection to solve issues
#pragma once
#include "Engine.h"
#include "Button.h"

class MenuSystem {
private:
	int selection;
	std::vector<Button> buttons;
	bool hold;
	//mouse stuff
	float _mX;
	float _mY;
	int _height;
	int _width;
	spriteStruct cursor;

	// sound stuff
	soundStruct click;
	soundStruct rollover;
	vector soundvec;
public:
	MenuSystem();
	void init();
	void update();
	void clear();
	void render();
	void resetSelection(){selection = 0;}
	void addButton(Button input);
	void addButton(void (*func)(),const char* label,frect rect,DWORD flags,D3DCOLOR color,D3DCOLOR hcolor);
};
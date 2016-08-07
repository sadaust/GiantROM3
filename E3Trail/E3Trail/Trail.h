#pragma once
#include "Engine.h"
#include "Character.h"


#define PARTYSIZE 4

class Trail {
private:
	bool running;
	int food;
	int credits;
	int fuel;
	int speed;
	float distToGo;
	int startDist;
	Character party[PARTYSIZE];
	textStruct partyText[PARTYSIZE][2];
public:
	Trail();
	void init(bool west, Character p1, Character p2, Character p3 , Character p4);
	void init(bool west);
	bool update();
};
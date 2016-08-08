#pragma once
#include "Engine.h"
#include "Character.h"
#include "MenuSystem.h"
#include "Item.h"


#define PARTYSIZE 4
#define NUMRESORCES 6
#define MAXLOCEVENT 100

enum eventType {
	city,
	abandond,
	e3
};

struct locEvent {
	float dist;
	eventType type;
};


class Trail {
private:
	bool running;
	int food;
	int credits;
	int fuel;
	int speed;
	//speed when out of fuel
	int noFuelSpeed;
	//food per hour per party member alive
	int foodConsRate;
	//fuel consumed per mile
	int fuelCosRate;
	float distToGo;
	double time;
	int startDist;
	vector start;
	vector end;
	locEvent events[MAXLOCEVENT];
	int locEventCount;
	Character party[PARTYSIZE];
	textStruct partyText[PARTYSIZE][2];
	textStruct renstats[NUMRESORCES];
	spriteStruct map;
	D3DXVECTOR2 pathVec[2];
	lineStruct path;
	MenuSystem menu;
public:
	Trail();
	void init(bool west, Character p1, Character p2, Character p3 , Character p4);
	void init(bool west);
	int aliveCount();
	bool update();

	void swapItems(int c1,int s1,int c2,int s2);
};
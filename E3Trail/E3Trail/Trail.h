#pragma once
#include "Engine.h"
#include "Character.h"
#include "MenuSystem.h"
#include "Item.h"
#include "TrailEvent.h"


#define PARTYSIZE 4
#define NUMRESORCES 6
#define MAXLOCEVENT 100
#define SPEEDINCRMULTIPLIER .025 
#define ITEMTARGETNOTCHOSEN -1
#define BASEFUELCOST 10
#define RANGEFUELCOST 41
#define BASEFOODCOST 10
#define RANGEFOODCOST 21
#define NUMSHOPITEMS 4




enum eventType {
	city,
	abandoned,
	e3
};

struct locEvent {
	float dist;
	eventType type;
};


enum TrailState {
	charselect,
	vehicleselect,
	pause,
	trail,
	eventscreen,
	itemswapscreen,
	cityscreen,
	shopscreen,
	epilogue

};


class Trail {
private:
	TrailState tstate;
	int targetitems[2][2];
	DWORD bColor;
	DWORD hColor;
	DWORD cColor;
	std::string cityname;
	Item shopitems[NUMSHOPITEMS];

	void createEvents();
	void triggerEvent(int eventId);
	std::vector<TrailEvent> eventList;
	bool pause;
	bool running;
	float food;
	int credits;
	float fuel;
	int speed;
	//speed when out of fuel
	int noFuelSpeed;
	//food per hour per party member alive
	float foodConsRate;
	//fuel consumed per mile
	float fuelCosRate;
	float distToGo;
	double time;
	int startDist;
	vector start;
	vector end;
	locEvent events[MAXLOCEVENT];
	int locEventCount;
	Character party[PARTYSIZE];
	textStruct partyText[PARTYSIZE][3];
	textStruct renstats[NUMRESORCES];
	textStruct eventText;
	textStruct cityText;
	spriteStruct eventBackground;
	float mapScaleX, mapScaleY;
	spriteStruct map;
	D3DXVECTOR2 pathVec[2];
	lineStruct path;
	MenuSystem menu;
	//city store stuff
	int fuelCost;
	int foodCost;
public:
	Trail();
	void init(bool west, Character& p1, Character& p2, Character& p3 , Character& p4);
	void init(bool west);
	int aliveCount();
	bool update();
	void render();
	void setTrailButtons();
	void setItemButtons();
	void startEndScreen();
	void setCityButtons(bool generate);
	void setShopButtons();
	void swapItems(int c1,int s1,int c2,int s2);
};
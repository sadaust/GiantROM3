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

#define BASETRADECOST 1

#define RANGETRADECOST 7

#define TRADEAMOUNT 50

#define NUMSHOPITEMS 4

#define NUMCHARACTERS 10



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
	int targetitems[2][2];  // swap items: 0,0 is char 0. 0,1 is slot 0. 1,0 is char 1. 1,1 is slot 1
							// shop: 0,0 is shop item. 1,0 is character. 1,1 is slot
	DWORD bColor;
	DWORD hColor;
	DWORD cColor;
	std::string cityname;
	std::vector <Item> itemList;
	Item shopitems[NUMSHOPITEMS];
	bool itemsBought[NUMSHOPITEMS];
	textStruct selectText;
	int partychoices[PARTYSIZE];
	
	
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
	Character allcharacters[NUMCHARACTERS];
	textStruct partyText[PARTYSIZE][4];
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
	int resourceCost[PARTYSIZE];
public:
	Trail();
	void init(bool west);
	int aliveCount();
	bool update();
	void render();
	void setTrailButtons();
	void setItemButtons();
	void startEndScreen();
	void setCityButtons(bool generate);
	void setShopButtons(bool generate);
	void setCharSelectButtons();
	void setItems();
	void swapItems(int c1,int s1,int c2,int s2);
	void resetColors();
};
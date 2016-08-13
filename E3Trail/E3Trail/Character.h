#pragma once
#include <string>
#include "Item.h"
#include "Engine.h"

#define NUM_ITEMS 2
#define NUM_STATUS 6
#define STATUS_PIC_SCALE .18f

class Character {
private:
	int hp;
	int maxhp;
	int strength;
	int agility;
	int intelligence;
	float resource;
	float resrate;
	float resclickrate;
	std::string name;
	std::string resName;
	std::string victory;
	Item items[NUM_ITEMS];
	spriteStruct statusPic[NUM_STATUS];
	bool activeitems[NUM_ITEMS];
public:
	void init(std::string a_name, std::string resourceName);
	void Draw(int index);
	int getHP();
	int getMaxHP();
	int getStrength();
	int getAgility();
	int getIntelligence();
	int getResource();
	std::string getResName();
	std::string getName();
	std::string getVictory();
	void resIncer();
	void resClick();
	void modHp(int mod);
	void modMaxHp(int mod);
	void modStrength(int mod);
	void modAgility(int mod);
	void modIntelligence(int mod);
	void modResource(int mod);
	void operator=(Character& in);


	// iTEM STUFF
	Item getItem(int index); // don't you dare ask for an item outside of NUM_ITEMS
	bool getActiveItem(int index);
	std::string getItemName(int index);

	void receiveItem(int index, Item &a_item);
	


};
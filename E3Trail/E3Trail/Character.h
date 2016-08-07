#pragma once
#include <string>
#include "Item.h"

#define NUM_ITEMS 2
#define NUM_STATUS 1

class Character {
private:
	int hp;
	int maxhp;
	int strength;
	int resource;
	float resrate;
	std::string name;
	std::string resName;
	Item items[NUM_ITEMS];
	spriteStruct statusPic[NUM_STATUS];
	bool activeitems[NUM_ITEMS];
public:
	void init(std::string a_name, std::string resourceName) {
		maxhp = 100;
		hp = maxhp;
		strength = 10; // probably change this for balance. Used for minigames and event thresholds
		resource = 0;
		resrate = 1;
		name = a_name;
		resName = resourceName;
	}
	int getHP() { return hp; }
	int getMaxHP() { return maxhp; }
	int getStrength() { return strength; }
	int getResource() { return resource; }
	std::string getResName() { return resName; }
	std::string getName() { return name; }
	void resIncer() { resource += resrate*hp; }
	void modHp(int mod) { hp += mod; }
	void modMaxHp(int mod) { maxhp += mod; }
	void modStrength(int mod) { strength += mod; }
	void modResource(int mod) { resource += mod; if (resource<0){ resource = 0; } }



	// iTEM STUFF
	Item getItem(int index) { return items[index]; } // don't you dare ask for an item outside of NUM_ITEMS
	bool getActiveItem(int index) { return activeitems[index]; }
	std::string getItemName(int index) { return items[index].getName(); }

	void receiveItem(int index, Item a_item) {
		Attribute tempatt;
		if (activeitems[index]) {
			for (int i = 0; i < a_item.numAtt(); ++i) { // Remove the old item if there is one active.
				tempatt = a_item.getAttribute(i);
				if (tempatt == STRENGTH) {
					strength -= a_item.getValue(i);
					if (strength < 0)
						strength = 0;
				}
				else if (tempatt == HP) {
					maxhp -= a_item.getValue(i);
					hp = -a_item.getValue(i);
					if (maxhp < 0)
						maxhp = 0;
					if (hp < 0)
						hp = 0;
				}
				else if (tempatt == RESRATE) {
					resrate -= a_item.getValue(i);
					if (resrate < 0)
						resrate = 0;
				}
			}

		}

		items[index] = a_item; // change the item.

		for (int i = 0; i < a_item.numAtt(); ++i) { // Add the new item's stuff to your stats
			tempatt = a_item.getAttribute(i);
			if (tempatt == STRENGTH) {
				strength += a_item.getValue(i);
				if (strength < 0)
					strength = 0;
			}
			else if (tempatt == HP) {
				maxhp += a_item.getValue(i);
				hp = +a_item.getValue(i);
				if (maxhp < 0)
					maxhp = 0;
				if (hp < 0)
					hp = 0;
			}
			else if (tempatt == RESRATE) {
				resrate += a_item.getValue(i);
				if (resrate < 0)
					resrate = 0;
			}
		}
	}
	// end of receiveItem


};
#include "Trail.h"
#include <cstring>
#include <regex>

#define NUMSTATES 50
std::string stateNames[NUMSTATES] = {"Alabama",
	"Alaska",
	"Arizona",
	"Arkansas",
	"California",
	"Colorado",
	"Connecticut",
	"Delaware",
	"Florida",
	"Georgia",
	"Hawaii",
	"Idaho",
	"Illinois",
	"Indiana",
	"Iowa",
	"Kansas",
	"Kentucky",
	"Louisiana",
	"Maine",
	"Maryland",
	"Massachusetts",
	"Michigan",
	"Minnesota",
	"Mississippi",
	"Missouri",
	"Montana",
	"Nebraska",
	"Nevada",
	"New Hampshire",
	"New Jersey",
	"New Mexico",
	"New York",
	"North Carolina",
	"North Dakota",
	"Ohio",
	"Oklahoma",
	"Oregon",
	"Pennsylvania",
	"Rhode Island",
	"South Carolina",
	"South Dakota",
	"Tennessee",
	"Texas",
	"Utah",
	"Vermont",
	"Virginia",
	"Washington",
	"West Virginia",
	"Wisconsin",
	"Wyoming"};

#define NUMCITYS 5
std::string cityNames[NUMCITYS] = {"San Francisco",
	"Fremont",
	"Phoenix",
	"Seattle",
	"New York"};

#define NUMCITYPREFIX 5
std::string cityPrefix[NUMCITYPREFIX] = {"Neo",
	"Derelict",
	"Abandoned",
	"Cyber",
	"Virtual"};

//update rate in seconds
#define UPDATETIME 0.05f

void clicker0() {
	Engine::instance()->postMessage("Incer0");
}
void clicker1() {
	Engine::instance()->postMessage("Incer1");
}
void clicker2() {
	Engine::instance()->postMessage("Incer2");
}
void clicker3() {
	Engine::instance()->postMessage("Incer3");
}
void itemswap() {
	Engine::instance()->postMessage("ItemSwap");
}
// Char select
void char0() {
	Engine::instance()->postMessage("Char0");
}
void char1() {
	Engine::instance()->postMessage("Char1");
}
void char2() {
	Engine::instance()->postMessage("Char2");
}
void char3() {
	Engine::instance()->postMessage("Char3");
}
void char4() {
	Engine::instance()->postMessage("Char4");
}
void char5() {
	Engine::instance()->postMessage("Char5");
}
void char6() {
	Engine::instance()->postMessage("Char6");
}
void char7() {
	Engine::instance()->postMessage("Char7");
}
void char8() {
	Engine::instance()->postMessage("Char8");
}
void char9() {
	Engine::instance()->postMessage("Char9");
}
// end of char select
// Item swap buttons
void item0() {
	Engine::instance()->postMessage("Item0");
}
void item1() {
	Engine::instance()->postMessage("Item1");
}
void item2() {
	Engine::instance()->postMessage("Item2");
}
void item3() {
	Engine::instance()->postMessage("Item3");
}
void item4() {
	Engine::instance()->postMessage("Item4");
}
void item5() {
	Engine::instance()->postMessage("Item5");
}
void item6() {
	Engine::instance()->postMessage("Item6");
}
void item7() {
	Engine::instance()->postMessage("Item7");
}
void itemcancel() {
	Engine::instance()->postMessage("ItemCancel");
}
// Item swap buttons end
// Shop buttons start
void shop0() {
	Engine::instance()->postMessage("Shop0");
}
void shop1() {
	Engine::instance()->postMessage("Shop1");
}
void shop2() {
	Engine::instance()->postMessage("Shop2");
}
void shop3() {
	Engine::instance()->postMessage("Shop3");
}
// Shop buttons end


void gotoStartScreen() {
	Engine::instance()->postMessage("gotoMM");
}
void closeEvent() {
	Engine::instance()->postMessage("eventDone");
}

void buyFuel() {
	Engine::instance()->postMessage("buyFuel");
}

void buyFood() {
	Engine::instance()->postMessage("buyFood");
}

void buyItems() {
	Engine::instance()->postMessage("buyItems");
}

void Trail::createEvents() {
	TrailEvent tempevent;
	eventList.clear();
	tempevent.reset();
	//taco bell
	tempevent.setText("%s found a tacobell and spent %s credits to buy a taco healing them by %s");
	tempevent.addEventEffect(TEvent::ranParty, 0);
	tempevent.addEventEffect(TEvent::credits, -50);
	tempevent.addEventEffect(TEvent::Hp, 50);
	eventList.push_back(tempevent);

	tempevent.reset();

	//
	tempevent.setText("Gary Busey, responding to a hit out on %s, threw a knife through your open rv window, dealing %s damage");
	tempevent.addEventEffect(TEvent::ranParty, 0);
	tempevent.addEventEffect(TEvent::agi, 9); // testing purposes
	tempevent.addEventEffect(TEvent::Hp, -20, -50);
	eventList.push_back(tempevent);

	tempevent.reset();

	//
	tempevent.setText("Your cybertire pops, causing %s to have to walk back to the nearest cyberautoshop.\nHe loses %s health from the heat and uses %s credits on the cybertire.");
	tempevent.addEventEffect(TEvent::ranParty, 0);
	tempevent.addEventEffect(TEvent::Hp, -5);
	tempevent.addEventEffect(TEvent::credits, -150);
	eventList.push_back(tempevent);

	tempevent.reset();

}

void Trail::setNewGameEvent() {
	menu.clear();
	char buffer[256];
	frect tempRec;
	eventText.flags = DT_LEFT | DT_TOP | DT_WORDBREAK;
	eventText.rect.left = 0.1f;
	eventText.rect.right = 0.9f;
	eventText.rect.top = 0.33f;
	eventText.rect.bottom = 0.66f;
	tempRec.top = 0.7f;
	tempRec.bottom = 0.8f;
	eventBackground.image = 0;
	if (credits < NEWGAMECOST) {
		eventText.text = "A strange man claims to have a machine that will send you back in time, but you don't have enough credits to use it";
		tempRec.left = 0.33f;
		tempRec.right = 0.66f;
		menu.addButton(closeEvent,"Leave",tempRec,DT_CENTER|DT_VCENTER,bColor,hColor);
	} else {
		eventText.text = "A strange man claims to have a machine that will send you back in time";
		sprintf(buffer,"Pay %d Credits to use the machine",NEWGAMECOST);
		tempRec.left = 0.1f;
		tempRec.right = 0.4f;
		menu.addButton(buyItems,buffer,tempRec,DT_CENTER|DT_VCENTER,bColor,hColor);
		tempRec.left = 0.6f;
		tempRec.right = 0.9f;
		menu.addButton(closeEvent,"Leave",tempRec,DT_CENTER|DT_VCENTER,bColor,hColor);
	}
	tstate = newGameScreen;
}

void Trail::triggerEvent() {
	int eventId = 0;
	int targChar = -1;
	std::vector<std::string> temp;
	bool push;
	bool good = true;
	char buffer[256];
	eventId = rand()%eventList.size();
	tstate = eventscreen;
	for (int i = 0; i < eventList[eventId].numEffect(); ++i) {
		push = true;
		switch (eventList[eventId].getEffect(i).targ) {
		case TEvent::str:
			if (targChar >= 0 && targChar < 4) {
				if (party[targChar].getStrength()<eventList[eventId].getEffect(i).value) {
					good = false;
				}
				else {
					good = true;
				}
			}
			push = false;
			break;
		case TEvent::agi:
			if (targChar >= 0 && targChar < 4) {
				if (party[targChar].getAgility()<eventList[eventId].getEffect(i).value) {
					good = false;
				}
				else {
					good = true;
				}
			}
			push = false;
			break;
		case TEvent::intel:
			if (targChar >= 0 && targChar < 4) {
				if (party[targChar].getIntelligence()<eventList[eventId].getEffect(i).value) {
					good = false;
				}
				else {
					good = true;
				}
			}
			push = false;
			break;

		case TEvent::ranParty:
			targChar = rand() % 4;
			sprintf(buffer, "%s", party[targChar].getName().c_str());
			break;
		case TEvent::party0:
			targChar = 0;
			sprintf(buffer, "%s", party[targChar].getName().c_str());
			break;
		case TEvent::party1:
			targChar = 1;
			sprintf(buffer, "%s", party[targChar].getName().c_str());
			break;
		case TEvent::party2:
			targChar = 2;
			sprintf(buffer, "%s", party[targChar].getName().c_str());
			break;
		case TEvent::party3:
			targChar = 3;
			sprintf(buffer, "%s", party[targChar].getName().c_str());
			break;
		case TEvent::Hp:
			if (targChar >= 0) {
				party[targChar].modHp(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal);

			}
			sprintf(buffer, "%d", abs(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal));

			break;
		case TEvent::Res:
			if (targChar >= 0)
				party[targChar].modResource(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal);
			sprintf(buffer, "%d", abs(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal));

			break;
		case TEvent::randResource:
			switch (rand() % 3) {
			case 0:
				credits += good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal;
				break;
			case 1:
				fuel += good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal;
				break;
			case 2:
				food += good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal;
				break;
			}
			sprintf(buffer, "%d", abs(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal));
			break;
		case TEvent::credits:
			credits += good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal;
			sprintf(buffer, "%d", abs(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal));
			break;
		case TEvent::fuel:
			fuel += good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal;
			sprintf(buffer, "%d", abs(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal));
			break;
		case TEvent::food:
			food += good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal;
			sprintf(buffer, "%d", abs(good ? eventList[eventId].getEffect(i).value : eventList[eventId].getEffect(i).failVal));
			break;
		}
		if (push)
			temp.push_back(buffer);
	}
	std::regex matcher;
	matcher = "%s";
	std::string z;
	z = eventList[eventId].getText();
	for (int i = 0; i < temp.size(); ++i) {
		z = std::regex_replace(z, matcher, temp[i], std::regex_constants::format_first_only);
	}
	frect temprec;
	temprec.left = 0;
	temprec.top = 0;
	temprec.right = 1;
	temprec.bottom = 1;
	eventText.text = z;
	eventText.color = 0xFFFFFFFF;
	eventText.flags = DT_CENTER | DT_VCENTER;
	eventText.rect = temprec;
	eventBackground.image = 0;
	pause = true;
	menu.clear();
	temprec.left = 0.25f;
	temprec.right = 0.75f;
	temprec.top = 0.8f;
	temprec.bottom = 0.9f;
	menu.addButton(closeEvent, "Back", temprec, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFF0000FF);
	eventChance = BASEEVENTCHANCE;
}

Trail::Trail() {
	targetitems[0][0] = ITEMTARGETNOTCHOSEN;
	targetitems[0][1] = ITEMTARGETNOTCHOSEN;
	targetitems[1][0] = ITEMTARGETNOTCHOSEN;
	targetitems[1][1] = ITEMTARGETNOTCHOSEN;
	bColor = 0xFF0000FF;
	hColor = 0xFF00FF00;
	cColor = 0xFFFF0000;





	createEvents();
	pause = false;
	mapScaleX = 1;
	mapScaleY = 1;
	frect tempRec;
	running = false;
	path.color = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	path.width = 5;
	path.vecCount = 2;
	path.vec = pathVec;
	for (int i = 0; i < PARTYSIZE; ++i) {
		tempRec.top = 0.7f;
		tempRec.bottom = 0.95f;
		tempRec.left = 0.25*i;
		tempRec.right = tempRec.left + 0.25f;
		// resources and stats
		partyText[i][0].rect = tempRec;
		partyText[i][0].color = 0xFFFFFFFF;
		partyText[i][0].flags = DT_LEFT | DT_TOP;
		partyText[i][0].text = "ERROR";

		// items
		partyText[i][2].rect = tempRec;
		partyText[i][2].color = 0xFFFFFFFF;
		partyText[i][2].flags = DT_LEFT | DT_TOP;
		partyText[i][2].text = "ERROR";

		//names and hp
		tempRec.top = 0.95f;
		tempRec.bottom = 1.0f;
		partyText[i][1].rect = tempRec;
		partyText[i][1].color = 0xFFFFFFFF;
		partyText[i][1].flags = DT_LEFT | DT_BOTTOM;
		partyText[i][1].text = "ERROR";
	}
	tempRec.left = 0.8f;
	tempRec.right = 0.999f;

	for (int i = 0; i < NUMRESORCES; ++i) {
		tempRec.top = 0.01f + 0.05f*i;
		tempRec.bottom = tempRec.top + 0.05f;
		renstats[i].rect = tempRec;
		renstats[i].color = 0xFFFFFFFF;
		renstats[i].flags = DT_LEFT | DT_BOTTOM;
	}
	map.center = D3DXVECTOR3(0, 0, 0);
	map.color = 0xFFFFFFFF;
	map.image = 0;
	map.rec.left = 0;
	map.rec.top = 0;
	locEventCount = 0;

	foodConsRate = 0.25f;
	fuelCosRate = 0.1f;
	noFuelSpeed = 5;


	// testing item swapping
	Engine::instance()->bind(SPACE, "Enter City");
	// end of testing item swapping

	// setting up shop item text rects
	for (int i = 0; i < NUMSHOPITEMS; ++i) {
		tempRec.top = 0.1f;
		tempRec.bottom = 0.6f;
		tempRec.left = (0.2f*i);
		tempRec.right = tempRec.left + 0.2f;
		partyText[i][3].rect = tempRec;
		partyText[i][3].color = 0xFFFFFFFF;
		partyText[i][3].flags = DT_CENTER | DT_BOTTOM;
		partyText[i][3].text = "ERROR";

	}// end of item text rects

	tempRec.top = 0.0f;
	tempRec.bottom = 0.05f;
	tempRec.left = 0.2f;
	tempRec.right = 0.8f;
	selectText.rect = tempRec;
	selectText.color = 0xFFFFFFFF;
	selectText.flags = DT_CENTER | DT_BOTTOM;
	selectText.text = "ERROR";


	

}


void Trail::init(bool west) {
	allcharacters[0].init("Dan", "Amiibos", "Amiibo");
	allcharacters[1].init("Brad", "Dota hats", "Dota hat");
	allcharacters[2].init("Rorie", "Puppies", "Puppy");
	allcharacters[3].init("Austin", "Gunpla", "Gunpla");
	allcharacters[4].init("Alex", "Big Rigs", "Big Rig");
	allcharacters[5].init("Drew", "Soviet Monsters", "Soviet Monster");
	allcharacters[6].init("Jason", "Plushies", "Plushy");
	allcharacters[7].init("Jeff", "Sneak King Copies", "Sneak King Copy");
	allcharacters[8].init("Patrick", "YT Subscribers", "YT Subscriber");
	allcharacters[9].init("Vinny", "Dragon Balls", "Dragon Ball");
	newTrigger = true;


	menu.init();
	pause = false;
	if (west) {
		startDist = 400;
		map.image = (imageAsset*)(Engine::instance()->getResource("SFMap.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		map.rec.bottom = map.image->texInfo.Height;
		map.rec.right = map.image->texInfo.Width;
		start.x = 0.2392f * map.rec.right;
		start.y = 0.6738f * map.rec.bottom;
		start.z = 0;
		end.x = 0.6777f * map.rec.right;
		end.y = 0.8789f * map.rec.bottom;
		end.z = 0;
		locEventCount = 10;
	}
	else {
		startDist = 2800;
		map.image = (imageAsset*)(Engine::instance()->getResource("NYMap.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		map.rec.bottom = map.image->texInfo.Height;
		map.rec.right = map.image->texInfo.Width;
		start.x = 0.8789f * map.rec.right;
		start.y = 0.3906f * map.rec.bottom;
		start.z = 0;
		end.x = 0.1123f * map.rec.right;
		end.y = 0.6445f * map.rec.bottom;
		end.z = 0;
		locEventCount = 50;
	}
	if (locEventCount > MAXLOCEVENT) {
		locEventCount = MAXLOCEVENT;
	}
	mapScaleX = (Engine::instance()->getWidth()*0.8f) / (float)map.rec.right;
	mapScaleY = (Engine::instance()->getHeight()*0.65f) / (float)map.rec.bottom;
	start.x *= mapScaleX;
	start.y *= mapScaleY;
	end.x *= mapScaleX;
	end.y *= mapScaleY;
	//events[locEventCount - 1].type = e3;
	//events[locEventCount - 1].dist = 0;
	time = 0;
	food = 100;
	credits = 5000;
	fuel = 150;
	speed = 10;
	distToGo = startDist;
	//party[0] = p1;
	//party[1] = p2;
	//party[2] = p3;
	//party[3] = p4;
	running = true;
	haventVisitedShop = true;

	setCharSelectButtons();
	setItems();
	for (int i = 0; i < NUMSHOPITEMS; ++i) {
		shopitems[i].Clear();
		itemsBought[i] = false;
	}

	for (int i = 0; i < PARTYSIZE; ++i)
		partychoices[i] = ITEMTARGETNOTCHOSEN;

	tstate = charselect;
	eventChance = BASEEVENTCHANCE;
	cityChance = BASECITYCHANCE;
}

int Trail::aliveCount() {
	int count = 0;
	for (int i = 0; i < PARTYSIZE; ++i) {
		count += (party[i].getHP() > 0);
	}
	return count;
}


void Trail::setCharSelectButtons() {
	frect rec;
	char buffer[256];
	menu.clear();



	rec.bottom = 0.5f;
	rec.top = 0.1f;
	rec.left = 0.0f;
	rec.right = 0.2f;
	sprintf(buffer, "%s", allcharacters[0].getName().c_str());
	menu.addButton(char0, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);

	rec.left = 0.2f;
	rec.right = 0.4f;
	sprintf(buffer, "%s", allcharacters[1].getName().c_str());
	menu.addButton(char1, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);


	rec.left = 0.4f;
	rec.right = 0.6f;
	sprintf(buffer, "%s", allcharacters[2].getName().c_str());
	menu.addButton(char2, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);


	rec.left = 0.6f;
	rec.right = 0.8f;
	sprintf(buffer, "%s", allcharacters[3].getName().c_str());
	menu.addButton(char3, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);


	rec.left = 0.8f;
	rec.right = 1.0f;
	sprintf(buffer, "%s", allcharacters[4].getName().c_str());
	menu.addButton(char4, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);


	rec.bottom = 0.9f;
	rec.top = 0.5f;
	rec.left = 0.0f;
	rec.right = 0.2f;
	sprintf(buffer, "%s", allcharacters[5].getName().c_str());
	menu.addButton(char5, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);

	rec.left = 0.2f;
	rec.right = 0.4f;
	sprintf(buffer, "%s", allcharacters[6].getName().c_str());
	menu.addButton(char6, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);


	rec.left = 0.4f;
	rec.right = 0.6f;
	sprintf(buffer, "%s", allcharacters[7].getName().c_str());
	menu.addButton(char7, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);


	rec.left = 0.6f;
	rec.right = 0.8f;
	sprintf(buffer, "%s", allcharacters[8].getName().c_str());
	menu.addButton(char8, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);


	rec.left = 0.8f;
	rec.right = 1.0f;
	sprintf(buffer, "%s", allcharacters[9].getName().c_str());
	menu.addButton(char9, buffer, rec, DT_CENTER | DT_TOP, bColor, hColor);




}


void Trail::setTrailButtons() {
	frect rec;
	char buffer[256];
	//DWORD bColor = 0xFF0000FF;
	//DWORD hColor = 0xFF00FF00; in constructor
	rec.bottom = 0.7f;
	rec.top = 0.65f;
	menu.clear();
	//party[0] incer
	float temp = 0;
	std::string tempstr;
	for (int i = 0; i < PARTYSIZE; ++i) {
		rec.left = 0.25f*i;
		rec.right = rec.left + 0.25f;
		tempstr = party[i].getName();
		temp = party[i].getItem(0).getValue(RESCLICK) + party[i].getItem(1).getValue(RESCLICK) + 1.0f;
		if (temp == 1) {
			if (tempstr == "Dan") // you buy amiibos and dota hats
				sprintf(buffer, "Buy an %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Brad") // you chomp puppies
				sprintf(buffer, "Buy a %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Rorie") // you chomp puppies
				sprintf(buffer, "Chomp a %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Austin") // you build gunpla
				sprintf(buffer, "Build a %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Alex" || tempstr == "Drew") // you construct big rigs and soviet monsters
				sprintf(buffer, "Construct a %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Jason") // you sew plushies
				sprintf(buffer, "Sew a %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Jeff") // you get sneak king copies (would prefer "Get sent" or "Recieve") but that's pretty long
				sprintf(buffer, "Get a %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Patrick") // you garner youtube subscribers
				sprintf(buffer, "Garner a %s", party[i].getResNameSingular().c_str());
			else if (tempstr == "Vinny") // you find dragon balls
				sprintf(buffer, "Find a %s", party[i].getResNameSingular().c_str());
		}
		else {
			if (tempstr == "Dan" || tempstr == "Brad") // you buy amiibos and dota hats
				sprintf(buffer, "Buy %.0f %s", temp, party[i].getResName().c_str());
			else if (tempstr == "Rorie") // you chomp puppies
				sprintf(buffer, "Chomp %.0f %s", temp, party[i].getResName().c_str());
			else if (tempstr == "Austin") // you build gunpla
				sprintf(buffer, "Build %.0f %s", temp, party[i].getResName().c_str());
			else if (tempstr == "Alex" || tempstr == "Drew") // you construct big rigs and soviet monsters
				sprintf(buffer, "Construct %.0f %s", temp, party[i].getResName().c_str());
			else if (tempstr == "Jason") // you sew plushies
				sprintf(buffer, "Sew %.0f %s", temp, party[i].getResName().c_str());
			else if (tempstr == "Jeff") // you get sneak king copies (would prefer "Get sent" or "Recieve") but that's pretty long
				sprintf(buffer, "Get %.0f %s", temp, party[i].getResName().c_str());
			else if (tempstr == "Patrick") // you garner youtube subscribers
				sprintf(buffer, "Garner %.0f %s", temp, party[i].getResName().c_str());
			else if (tempstr == "Vinny") // you find dragon balls
				sprintf(buffer, "Find %.0f %s", temp, party[i].getResName().c_str());
		}


		if (i == 0)
			menu.addButton(clicker0, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
		else if (i == 1)
			menu.addButton(clicker1, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
		else if (i == 2)
			menu.addButton(clicker2, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
		else if (i == 3)
			menu.addButton(clicker3, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	}









	// swap items button
	rec.bottom = 0.55f;
	rec.top = 0.5f;
	rec.left = 0.81f;
	rec.right = 1.0f;
	sprintf(buffer, "swap items");
	menu.addButton(itemswap, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

}


void Trail::setItemButtons() {
	frect rec;
	char buffer[256];
	rec.bottom = 0.78f;
	rec.top = 0.74f;
	menu.clear();
	//char 0 item 0
	rec.left = 0.0f;
	rec.right = 0.25f;
	sprintf(buffer, "%s", party[0].getItemName(0).c_str());
	menu.addButton(item0, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 0 item 1
	rec.left = 0.0f;
	rec.right = 0.25f;
	sprintf(buffer, "%s", party[0].getItemName(1).c_str());
	menu.addButton(item1, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.78f;
	rec.top = 0.74f;
	//char 1 item 0
	rec.left = 0.25f;
	rec.right = 0.5f;
	sprintf(buffer, "%s", party[1].getItemName(0).c_str());
	menu.addButton(item2, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 1 item 1
	rec.left = 0.25f;
	rec.right = 0.5f;
	sprintf(buffer, "%s", party[1].getItemName(1).c_str());
	menu.addButton(item3, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.78f;
	rec.top = 0.74f;
	//char 2 item 0
	rec.left = 0.5f;
	rec.right = 0.75f;
	sprintf(buffer, "%s", party[2].getItemName(0).c_str());
	menu.addButton(item4, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 2 item 1
	rec.left = 0.5f;
	rec.right = 0.75f;
	sprintf(buffer, "%s", party[2].getItemName(1).c_str());
	menu.addButton(item5, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.78f;
	rec.top = 0.74f;
	//char 3 item 0
	rec.left = 0.75f;
	rec.right = 1.0f;
	sprintf(buffer, "%s", party[3].getItemName(0).c_str());
	menu.addButton(item6, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 3 item 1
	rec.left = 0.75f;
	rec.right = 1.0f;
	sprintf(buffer, "%s", party[3].getItemName(1).c_str());
	menu.addButton(item7, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);


	// cancel button
	rec.bottom = 0.55f;
	rec.top = 0.5f;
	rec.left = 0.81f;
	rec.right = 1.0f;
	sprintf(buffer, "cancel");
	menu.addButton(itemcancel, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);
}


void Trail::setCityButtons(bool generate) {

	char buffer[256];
	frect tempRec;
	
	if (generate) {
		fuelCost = BASEFUELCOST + (rand() % RANGEFUELCOST);
		foodCost = BASEFOODCOST + (rand() % RANGEFOODCOST);

		for (int i = 0; i < NUMSHOPITEMS; ++i) {
			resourceCost[i] = BASETRADECOST + (rand() % RANGETRADECOST);
		}
		sprintf(buffer,"Welcome to %s %s, %s",cityPrefix[rand()%NUMCITYPREFIX].c_str(),cityNames[rand()%NUMCITYS].c_str(),stateNames[rand()%NUMSTATES].c_str());
		cityname = buffer;
		haventVisitedShop = true;
	}
	pause = true;
	menu.clear();

	eventBackground.image = 0;
	eventText.text = cityname;
	eventText.color = 0xFFFFFFFF;
	eventText.flags = DT_CENTER | DT_VCENTER;
	tempRec.top = 0;
	tempRec.bottom = 0.2f;
	tempRec.left = 0.1f;
	tempRec.right = 0.9f;
	eventText.rect = tempRec;

	tempRec.left = 0.0f;
	tempRec.right = 0.25f;

	tempRec.top = 0.05f;
	tempRec.bottom = 0.1f;
	sprintf(buffer, "5 fuel costs: %d", fuelCost);
	menu.addButton(buyFuel, buffer, tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);

	tempRec.top = 0.2f;
	tempRec.bottom = 0.25f;
	sprintf(buffer, "5 food costs: %d", foodCost);
	menu.addButton(buyFood, buffer, tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);

	tempRec.top = 0.35f;
	tempRec.bottom = 0.4f;
	menu.addButton(buyItems, "Buy Items", tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);

	tempRec.top = 0.5f;
	tempRec.bottom = 0.55f;
	menu.addButton(closeEvent, "Leave town", tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);

	tempRec.bottom = 0.7f;
	tempRec.top = 0.60f;
	//party[0] incer
	tempRec.left = 0.0f;
	tempRec.right = 0.25f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[0], party[0].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker0, buffer, tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);
	//party[1] incer
	tempRec.left = 0.25f;
	tempRec.right = 0.5f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[1], party[1].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker1, buffer, tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);
	//party[2] incer
	tempRec.left = 0.5f;
	tempRec.right = 0.75f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[2], party[2].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker2, buffer, tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);
	//party[3] incer
	tempRec.left = 0.75f;
	tempRec.right = 1.0f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[3], party[3].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker3, buffer, tempRec, DT_CENTER | DT_VCENTER, bColor, hColor);



	tstate = cityscreen;
}

void Trail::setShopButtons(bool generate) {
	if (generate) {
		int nonrepeat = ITEMTARGETNOTCHOSEN;
		bool repeat = true;
		for (int i = 0; i < NUMSHOPITEMS; ++i) {
			nonrepeatitems[i] = ITEMTARGETNOTCHOSEN;
		}
		for (int i = 0; i < NUMSHOPITEMS; ++i) {
			shopitems[i].Clear();
			repeat = true;
			while (repeat) {
				nonrepeat = rand() % itemList.size();
				if (nonrepeat != nonrepeatitems[0] && nonrepeat != nonrepeatitems[1] && nonrepeat != nonrepeatitems[2] && nonrepeat != nonrepeatitems[3])
					repeat = false;
			}

			shopitems[i] = itemList[nonrepeat];
			nonrepeatitems[i] = nonrepeat;
			itemsBought[i] = false;
		}



	}


	char buffer[256];
	frect rec;
	menu.clear();

	rec.top = 0.2f;
	rec.bottom = 0.3f;

	if (!itemsBought[0]) {
		rec.left = 0.0f;
		rec.right = rec.left + 0.2f;
		sprintf(buffer, "%s", shopitems[0].getName().c_str());
		menu.addButton(shop0, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	}

	if (!itemsBought[1]) {
		rec.left = 0.2f;
		rec.right = rec.left + 0.2f;
		sprintf(buffer, "%s", shopitems[1].getName().c_str());
		menu.addButton(shop1, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	}

	if (!itemsBought[2]) {
		rec.left = 0.4f;
		rec.right = rec.left + 0.2f;
		sprintf(buffer, "%s", shopitems[2].getName().c_str());
		menu.addButton(shop2, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	}

	if (!itemsBought[3]) {
		rec.left = 0.6f;
		rec.right = rec.left + 0.2f;
		sprintf(buffer, "%s", shopitems[3].getName().c_str());
		menu.addButton(shop3, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	}


	rec.bottom = 0.78f;
	rec.top = 0.74f;
	//char 0 item 0
	rec.left = 0.0f;
	rec.right = 0.25f;
	sprintf(buffer, "%s", party[0].getItemName(0).c_str());
	menu.addButton(item0, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 0 item 1
	rec.left = 0.0f;
	rec.right = 0.25f;
	sprintf(buffer, "%s", party[0].getItemName(1).c_str());
	menu.addButton(item1, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.78f;
	rec.top = 0.74f;
	//char 1 item 0
	rec.left = 0.25f;
	rec.right = 0.5f;
	sprintf(buffer, "%s", party[1].getItemName(0).c_str());
	menu.addButton(item2, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 1 item 1
	rec.left = 0.25f;
	rec.right = 0.5f;
	sprintf(buffer, "%s", party[1].getItemName(1).c_str());
	menu.addButton(item3, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.78f;
	rec.top = 0.74f;
	//char 2 item 0
	rec.left = 0.5f;
	rec.right = 0.75f;
	sprintf(buffer, "%s", party[2].getItemName(0).c_str());
	menu.addButton(item4, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 2 item 1
	rec.left = 0.5f;
	rec.right = 0.75f;
	sprintf(buffer, "%s", party[2].getItemName(1).c_str());
	menu.addButton(item5, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.78f;
	rec.top = 0.74f;
	//char 3 item 0
	rec.left = 0.75f;
	rec.right = 1.0f;
	sprintf(buffer, "%s", party[3].getItemName(0).c_str());
	menu.addButton(item6, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);

	rec.bottom = 0.83f;
	rec.top = 0.78f;
	//char 3 item 1
	rec.left = 0.75f;
	rec.right = 1.0f;
	sprintf(buffer, "%s", party[3].getItemName(1).c_str());
	menu.addButton(item7, buffer, rec, DT_LEFT | DT_VCENTER, bColor, hColor);



	rec.bottom = 0.7f;
	rec.top = 0.60f;
	//party[0] incer
	rec.left = 0.0f;
	rec.right = 0.25f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[0], party[0].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker0, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	//party[1] incer
	rec.left = 0.25f;
	rec.right = 0.5f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[1], party[1].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker1, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	//party[2] incer
	rec.left = 0.5f;
	rec.right = 0.75f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[2], party[2].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker2, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);
	//party[3] incer
	rec.left = 0.75f;
	rec.right = 1.0f;
	sprintf(buffer, "Trade %d %s\nfor %d credits", resourceCost[3], party[3].getResName().c_str(), TRADEAMOUNT);
	menu.addButton(clicker3, buffer, rec, DT_CENTER | DT_VCENTER, bColor, hColor);

	rec.left = 0.0f;
	rec.right = 0.25f;
	rec.top = 0.05f;
	rec.bottom = 0.1f;
	menu.addButton(buyItems, "Leave Shop", rec, DT_CENTER | DT_VCENTER, bColor, hColor);


	tstate = shopscreen;
	haventVisitedShop = false;
}

void Trail::startEndScreen() {
	frect tempRec;
	char buffer[256];
	menu.clear();
	speed = 0;
	tempRec.left = 0.05f;
	tempRec.right = 0.95f;

	tempRec.top = 0.8f;
	tempRec.bottom = 0.9f;
	menu.addButton(closeEvent, "Next", tempRec, DT_CENTER | DT_VCENTER, 0xFF0000FF, 0xFF00FF00);
	tempRec.bottom = 0.7f;
	tempRec.top = 0.2f;
	eventBackground.image = 0;
	eventText.rect = tempRec;
	eventText.color = 0xFFFFFFFF;
	eventText.flags = DT_CENTER | DT_VCENTER;

	if (aliveCount() > 0) {
		eventText.text = "At least one person made it to E3";
	}
	else {
		eventText.text = "No one made it to E3";
	}
	tstate = epilogue;
}

bool Trail::update() {

	if (running) {
		menu.update();




		//return to main menu
		if (Engine::instance()->getBind("Back") || Engine::instance()->getMessage("gotoMM")) {
			running = false;
			return false;
		}
		

		if (tstate == trail){
			/*
			if (Engine::instance()->getBind("Enter City")) {
				//swapItems(0, 0, 1, 0);
				setCityButtons(true);

			}
			*/



			time += Engine::instance()->dt();
			if (Engine::instance()->getMessage("Incer0")) {
				party[0].resClick();
			}
			else if (Engine::instance()->getMessage("Incer1")) {
				party[1].resClick();
			}
			else if (Engine::instance()->getMessage("Incer2")) {
				party[2].resClick();
			}
			else if (Engine::instance()->getMessage("Incer3")) {
				party[3].resClick();
			}
			else if (Engine::instance()->getMessage("ItemSwap")) {
				tstate = itemswapscreen;
				setItemButtons();
			}

			if (time >= UPDATETIME) {
				time -= UPDATETIME;

				if (fuel > 0) {
					distToGo -= speed * SPEEDINCRMULTIPLIER;
					fuel -= speed * fuelCosRate * SPEEDINCRMULTIPLIER;
					if (fuel < 0) {
						fuel = 0;
					}
				}
				else {
					distToGo -= noFuelSpeed * SPEEDINCRMULTIPLIER;
				}

				if (food > 0) {
					food -= aliveCount()*foodConsRate * SPEEDINCRMULTIPLIER;
					if (food <= 0) {
						food = 0;
					}
				}
				else {
					for (int i = 0; i < PARTYSIZE; ++i) {
						party[i].modHp(-5);
					}
				}

				for (int i = 0; i < PARTYSIZE; ++i) {
					party[i].resIncer();
				}
				if (aliveCount() == 0 || distToGo <= 0) {
					startEndScreen();
				}
				if (distToGo <= 10 && newTrigger) {
					setNewGameEvent();
				}
				//if rand()%eventchance == 0 do event
				else if(!(rand()%eventChance)) {
					triggerEvent();
				} else if (!(rand()%cityChance)) {
					setCityButtons(true);
					cityChance = BASECITYCHANCE;
				} else {
					//if no event triggered make them have better odds of happening
					--eventChance;
					cityChance -= speed;
					if(cityChance < 1) {
						cityChance = 1;
					}
				}
			}
		}
		else if (tstate == itemswapscreen) {
			int itemnumber = ITEMTARGETNOTCHOSEN;
			if (Engine::instance()->getMessage("ItemCancel")) {
				tstate = trail;
				targetitems[0][0] = ITEMTARGETNOTCHOSEN;
				targetitems[0][1] = ITEMTARGETNOTCHOSEN;
				targetitems[1][0] = ITEMTARGETNOTCHOSEN;
				targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				setTrailButtons();
			} // start of item swap buttons
			else if (Engine::instance()->getMessage("Item0")) {
				itemnumber = 0;
				if (targetitems[0][0] == 0 && targetitems[0][1] == 0) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 0 && targetitems[1][1] == 0) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 0;
					targetitems[0][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 0;
					targetitems[1][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Item1")) {
				itemnumber = 1;
				if (targetitems[0][0] == 0 && targetitems[0][1] == itemnumber) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 0 && targetitems[1][1] == itemnumber) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 0;
					targetitems[0][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 0;
					targetitems[1][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Item2")) {
				itemnumber = 2;
				if (targetitems[0][0] == 1 && targetitems[0][1] == 0) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 1 && targetitems[1][1] == 0) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 1;
					targetitems[0][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 1;
					targetitems[1][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Item3")) {
				itemnumber = 3;
				if (targetitems[0][0] == 1 && targetitems[0][1] == 1) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 1 && targetitems[1][1] == 1) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 1;
					targetitems[0][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 1;
					targetitems[1][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Item4")) {
				itemnumber = 4;
				if (targetitems[0][0] == 2 && targetitems[0][1] == 0) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 2 && targetitems[1][1] == 0) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 2;
					targetitems[0][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 2;
					targetitems[1][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Item5")) {
				itemnumber = 5;
				if (targetitems[0][0] == 2 && targetitems[0][1] == 1) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 2 && targetitems[1][1] == 1) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 2;
					targetitems[0][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 2;
					targetitems[1][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Item6")) {
				itemnumber = 6;
				if (targetitems[0][0] == 3 && targetitems[0][1] == 0) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 3 && targetitems[1][1] == 0) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 3;
					targetitems[0][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 3;
					targetitems[1][1] = 0;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Item7")) {
				itemnumber = 7;
				if (targetitems[0][0] == 3 && targetitems[0][1] == 1) {
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[1][0] == 3 && targetitems[1][1] == 1) {
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(itemnumber, bColor, hColor);
				}
				else if (targetitems[0][0] < 0) {
					targetitems[0][0] = 3;
					targetitems[0][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
				else if (targetitems[1][0] < 0) {
					targetitems[1][0] = 3;
					targetitems[1][1] = 1;
					menu.ChangeColorJanky(itemnumber, cColor, hColor);
				}
			}
			// end of itemswapbuttons

			if (targetitems[0][0] >= 0 && targetitems[1][0] >= 0) {
				swapItems(targetitems[0][0], targetitems[0][1], targetitems[1][0], targetitems[1][1]);
				targetitems[0][0] = ITEMTARGETNOTCHOSEN;
				targetitems[0][1] = ITEMTARGETNOTCHOSEN;
				targetitems[1][0] = ITEMTARGETNOTCHOSEN;
				targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				for (int i = 0; i < NUM_ITEMS * PARTYSIZE; ++i) {
					menu.ChangeColorJanky(itemnumber, bColor, hColor); // reset colors
				}
				setItemButtons();
			}






		}
		else if (tstate == cityscreen){
			if (Engine::instance()->getMessage("eventDone")) {
				tstate = trail;
				setTrailButtons();
				haventVisitedShop = true;
			}
			else if (Engine::instance()->getMessage("buyFuel")) {
				credits -= fuelCost;
				fuel += 5;
			}
			else if (Engine::instance()->getMessage("buyFood")) {
				credits -= foodCost;
				food += 5;
			}
			else if (Engine::instance()->getMessage("buyItems")) {
				setShopButtons(haventVisitedShop);

			}

			if (Engine::instance()->getMessage("Incer0")) {
				if (party[0].getResource() >= resourceCost[0]) {
					party[0].modResource(-resourceCost[0]);
					credits += TRADEAMOUNT;
				}

			}
			else if (Engine::instance()->getMessage("Incer1")) {
				if (party[1].getResource() >= resourceCost[1]) {
					party[1].modResource(-resourceCost[1]);
					credits += TRADEAMOUNT;
				}
			}
			else if (Engine::instance()->getMessage("Incer2")) {
				if (party[2].getResource() >= resourceCost[2]) {
					party[2].modResource(-resourceCost[2]);
					credits += TRADEAMOUNT;
				}
			}
			else if (Engine::instance()->getMessage("Incer3")) {
				if (party[3].getResource() >= resourceCost[3]) {
					party[3].modResource(-resourceCost[3]);
					credits += TRADEAMOUNT;
				}
			}
		}
		else if (tstate == shopscreen) {
			int shoptemp = 0;
			if (Engine::instance()->getMessage("buyItems")) {
				setCityButtons(false);
				targetitems[0][0] = ITEMTARGETNOTCHOSEN;
				targetitems[0][1] = ITEMTARGETNOTCHOSEN;
				targetitems[1][0] = ITEMTARGETNOTCHOSEN;
				targetitems[1][1] = ITEMTARGETNOTCHOSEN;
			}
			else if (Engine::instance()->getMessage("Shop0")) {
				if (targetitems[0][0] == 0) { // If you're already targeting shop0
					// untarget it
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(0, bColor, hColor);
				}
				else {
					targetitems[0][0] = 0;
					resetColors();
					menu.ChangeColorJanky(0, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Shop1")) {
				if (targetitems[0][0] == 1) { // If you're already targeting shop1
					// untarget it
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(1, bColor, hColor);
				}
				else {
					shoptemp = 0;
					if (itemsBought[0])
						++shoptemp;
					targetitems[0][0] = 1;
					resetColors();
					menu.ChangeColorJanky(1 - shoptemp, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Shop2")) {
				if (targetitems[0][0] == 2) { // If you're already targeting shop2
					// untarget it
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(2, bColor, hColor);
				}
				else {
					shoptemp = 0;
					for (int i = 0; i < 2; ++i) {
						if (itemsBought[i])
							++shoptemp;
					}
					targetitems[0][0] = 2;
					resetColors();
					menu.ChangeColorJanky(2 - shoptemp, cColor, hColor);
				}
			}
			else if (Engine::instance()->getMessage("Shop3")) {
				if (targetitems[0][0] == 3) { // If you're already targeting shop3
					// untarget it
					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					menu.ChangeColorJanky(3, bColor, hColor);
				}
				else {
					shoptemp = 0;
					for (int i = 0; i < 3; ++i) {
						if (itemsBought[i])
							++shoptemp;
					}
					targetitems[0][0] = 3;
					resetColors();
					menu.ChangeColorJanky(3 - shoptemp, cColor, hColor);
				}
			}
			if (targetitems[0][0] >= 0) {
				if (Engine::instance()->getMessage("Item0") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[0].receiveItem(0, shopitems[targetitems[0][0]]);

					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;

					setShopButtons(haventVisitedShop);

					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;

				}
				else if (Engine::instance()->getMessage("Item1") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[0].receiveItem(1, shopitems[targetitems[0][0]]);
					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;
					setShopButtons(haventVisitedShop);


					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				}
				else if (Engine::instance()->getMessage("Item2") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[1].receiveItem(0, shopitems[targetitems[0][0]]);
					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;
					setShopButtons(haventVisitedShop);

					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				}
				else if (Engine::instance()->getMessage("Item3") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[1].receiveItem(1, shopitems[targetitems[0][0]]);
					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;
					setShopButtons(haventVisitedShop);

					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				}
				else if (Engine::instance()->getMessage("Item4") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[2].receiveItem(0, shopitems[targetitems[0][0]]);
					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;
					setShopButtons(haventVisitedShop);

					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				}
				else if (Engine::instance()->getMessage("Item5") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[2].receiveItem(1, shopitems[targetitems[0][0]]);
					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;
					setShopButtons(haventVisitedShop);

					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				}
				else if (Engine::instance()->getMessage("Item6") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[3].receiveItem(0, shopitems[targetitems[0][0]]);
					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;
					setShopButtons(haventVisitedShop);

					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				}
				else if (Engine::instance()->getMessage("Item7") && credits >= shopitems[targetitems[0][0]].getCost()) {
					resetColors();
					party[3].receiveItem(1, shopitems[targetitems[0][0]]);
					credits -= shopitems[targetitems[0][0]].getCost();
					itemsBought[targetitems[0][0]] = true;
					setShopButtons(haventVisitedShop);

					targetitems[0][0] = ITEMTARGETNOTCHOSEN;
					targetitems[0][1] = ITEMTARGETNOTCHOSEN;
					targetitems[1][0] = ITEMTARGETNOTCHOSEN;
					targetitems[1][1] = ITEMTARGETNOTCHOSEN;
				}

			}
			// end of clicking on an item slot with a shop item selected
			// TO DO: empty slot misclick stuff

			if (Engine::instance()->getMessage("Incer0")) {
				if (party[0].getResource() >= resourceCost[0]) {
					party[0].modResource(-resourceCost[0]);
					credits += TRADEAMOUNT;
				}

			}
			else if (Engine::instance()->getMessage("Incer1")) {
				if (party[1].getResource() >= resourceCost[1]) {
					party[1].modResource(-resourceCost[1]);
					credits += TRADEAMOUNT;
				}
			}
			else if (Engine::instance()->getMessage("Incer2")) {
				if (party[2].getResource() >= resourceCost[2]) {
					party[2].modResource(-resourceCost[2]);
					credits += TRADEAMOUNT;
				}
			}
			else if (Engine::instance()->getMessage("Incer3")) {
				if (party[3].getResource() >= resourceCost[3]) {
					party[3].modResource(-resourceCost[3]);
					credits += TRADEAMOUNT;
				}
			}



		}
		else if (tstate == charselect) {
			bool temp = false;
			if (Engine::instance()->getMessage("Char0")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 0) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(0, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) { // if partychoices[i] isn't chosen,
							partychoices[i] = 0; // choose it
							menu.ChangeColorJanky(0, cColor, hColor); // recolor the button
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char1")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 1) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(1, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 1;
							menu.ChangeColorJanky(1, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char2")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 2) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(2, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 2;
							menu.ChangeColorJanky(2, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char3")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 3) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(3, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 3;
							menu.ChangeColorJanky(3, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char4")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 4) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(4, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 4;
							menu.ChangeColorJanky(4, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char5")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 5) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(5, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 5;
							menu.ChangeColorJanky(5, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char6")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 6) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(6, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 6;
							menu.ChangeColorJanky(6, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char7")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 7) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(7, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 7;
							menu.ChangeColorJanky(7, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char8")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 8) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(8, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 8;
							menu.ChangeColorJanky(8, cColor, hColor);
							temp = true;

						}
					}
				}
			}
			else if (Engine::instance()->getMessage("Char9")) {
				for (int i = 0; i < PARTYSIZE; ++i) {
					if (partychoices[i] == 9) {
						partychoices[i] = ITEMTARGETNOTCHOSEN;
						menu.ChangeColorJanky(9, bColor, hColor);
						temp = true;
					}
				}
				if (!temp) { // if you didn't just reverse one of your choices
					// temp is still false, so we're going to use it for this for loop
					for (int i = 0; i < PARTYSIZE && !temp; ++i) {
						if (partychoices[i] == ITEMTARGETNOTCHOSEN) {
							partychoices[i] = 9;
							menu.ChangeColorJanky(9, cColor, hColor);
							temp = true;

						}
					}
				}
			}


			// now we check if all 4 are chosen
			if (partychoices[0] >= 0 && partychoices[1] >= 0 && partychoices[2] >= 0 && partychoices[3] >= 0) {
				resetColors();
				for (int i = 0; i < PARTYSIZE; ++i) {
					party[i] = allcharacters[partychoices[i]]; // CHOOSE DAT CHARACTER

					partychoices[i] = ITEMTARGETNOTCHOSEN; // reset for next time
				}
				setTrailButtons();
				tstate = trail;
			}









		}
		else if (tstate == epilogue) {
			if (Engine::instance()->getMessage("eventDone")) {
				if (speed < 4) {
					eventText.text = party[speed].getVictory();
					++speed;
				}
				else {
					running = false;
					return false;
				}
			}
		}
		else if(tstate == eventscreen) {
			if(Engine::instance()->getMessage("eventDone")) {
				setTrailButtons();
				tstate = trail;
			}
		}
		else if (tstate == newGameScreen) {
			if(Engine::instance()->getMessage("eventDone")) {
				newTrigger = false;
				setTrailButtons();
				tstate = trail;
			} else if(Engine::instance()->getMessage("buyItems")) {
				credits -= NEWGAMECOST;
				distToGo = startDist;
				setTrailButtons();
				tstate = trail;
			}
		}

	}
	return running;
}


void Trail::render() {
	char buffer[256];
	renInfo tempRen;
	D3DXMATRIX tempMat;
	D3DXMatrixIdentity(&tempRen.matrix);
	D3DXMatrixIdentity(&tempMat);
	D3DXMatrixTranslation(&tempRen.matrix, 0, 0, 1);
	if (running) {

		if (tstate == trail || tstate == itemswapscreen || tstate == cityscreen || tstate == shopscreen) {
			//render the main play screen
			tempRen.type = text;
			if (tstate == cityscreen) {
				tempRen.asset = &eventText;
				Engine::instance()->addRender(tempRen);
			}
			if (tstate != itemswapscreen && tstate != shopscreen) { // item names not drawn during item swap screen since buttons replace it
				for (int i = 0; i < PARTYSIZE; ++i) {
					sprintf(buffer, "\n%s\n%s", party[i].getItemName(0).c_str(), party[i].getItemName(1).c_str());
					partyText[i][2].text = buffer;
					tempRen.asset = &partyText[i][2];
					Engine::instance()->addRender(tempRen);
				}
			}
			for (int i = 0; i < PARTYSIZE; ++i) {
				sprintf(buffer, "%s: %d\n\n\nStr: %d\nAgi: %d\nInt: %d", party[i].getResName().c_str(), party[i].getResource(), /*party[i].getItemName(0).c_str(), party[i].getItemName(1).c_str(),*/ party[i].getStrength(), party[i].getAgility(), party[i].getIntelligence());
				partyText[i][0].text = buffer;
				tempRen.asset = &partyText[i][0];
				Engine::instance()->addRender(tempRen);

				sprintf(buffer, "%s HP: %03d/%03d", party[i].getName().c_str(), party[i].getHP(), party[i].getMaxHP());
				partyText[i][1].text = buffer;
				tempRen.asset = &partyText[i][1];
				Engine::instance()->addRender(tempRen);
			}

			sprintf(buffer, "Credits: %d", credits);
			renstats[0].text = buffer;
			sprintf(buffer, "Food: %.0f snacks", food);
			renstats[1].text = buffer;
			sprintf(buffer, "Fuel: %.0f gallons", fuel);
			renstats[2].text = buffer;
			sprintf(buffer, "Speed: %03d Mph", speed);
			renstats[3].text = buffer;
			sprintf(buffer, "Distance: %.0f miles", distToGo);
			renstats[4].text = buffer;
			sprintf(buffer, "Time: %.2f", time);
			renstats[5].text = buffer;
			for (int i = 0; i < NUMRESORCES; ++i) {
				tempRen.asset = &renstats[i];
				Engine::instance()->addRender(tempRen);
			}

			if (tstate != cityscreen && tstate != shopscreen) { // map not drawn during the city screen
				//path line
				pathVec[0].x = start.x;
				pathVec[0].y = start.y;
				pathVec[1].x = start.x + ((end.x - start.x) * (1.0f - (distToGo / (float)startDist)));
				pathVec[1].y = start.y + ((end.y - start.y) * (1.0f - (distToGo / (float)startDist)));
				tempRen.type = line;
				tempRen.asset = &path;
				D3DXMatrixIdentity(&tempRen.matrix);
				Engine::instance()->addRender(tempRen);
				//map
				tempRen.asset = &map;
				tempRen.type = screenSprite;
				D3DXMatrixScaling(&tempRen.matrix, mapScaleX, mapScaleY, 1);
				D3DXMatrixTranslation(&tempMat, 0, 0, 1);
				D3DXMatrixMultiply(&tempRen.matrix, &tempRen.matrix, &tempMat);
				Engine::instance()->addRender(tempRen);
			}

			if (tstate == shopscreen) {
				for (int i = 0; i < NUMSHOPITEMS; ++i) {
					if (!itemsBought[i]) {
						sprintf(buffer, "Cost: %d\nStr: %.0f\nAgi: %.0f\nInt: %.0f\nHP: %.0f\nRes Prod.: %.2f\nRes/Click: %.0f", shopitems[i].getCost(), shopitems[i].getValue(STRENGTH), shopitems[i].getValue(AGILITY), shopitems[i].getValue(INTELLIGENCE), shopitems[i].getValue(HP), shopitems[i].getValue(RESRATE), shopitems[i].getValue(RESCLICK));
						partyText[i][3].text = buffer;
						tempRen.asset = &partyText[i][3];
						Engine::instance()->addRender(tempRen);
					}
				}
			}

			for (int i = 0; i < PARTYSIZE; ++i) {
				party[i].Draw(i);
			}
		}
		else if (tstate == charselect) {
			sprintf(buffer, "Choose your four party members");
			selectText.text = buffer;
			tempRen.type = text;
			tempRen.asset = &selectText;
			Engine::instance()->addRender(tempRen);
			for (int i = 0; i < NUMCHARACTERS; ++i) {
				allcharacters[i].DrawSelect(i);
			}
		}
		else if (tstate == eventscreen || tstate == epilogue || tstate == newGameScreen) { // actually probably an event
			tempRen.type = screenSprite;
			if (eventBackground.image) {
				tempRen.asset = &eventBackground;
				Engine::instance()->addRender(tempRen);
			}
			D3DXMatrixIdentity(&tempRen.matrix);
			tempRen.type = text;
			tempRen.asset = &eventText;
			Engine::instance()->addRender(tempRen);
		}

		menu.render();
	}
}


void Trail::setItems() {
	Item tempitem;
	tempitem.Clear();
	tempitem.setName("Doritos Locos Tacos");
	tempitem.setValue(AGILITY, -5);
	tempitem.setValue(STRENGTH, 35);
	tempitem.setValue(HP, -30);
	tempitem.setCost(150);
	itemList.push_back(tempitem);
	
	tempitem.Clear();
	tempitem.setName("Spaghetti Can");
	tempitem.setValue(AGILITY, 20);
	tempitem.setValue(STRENGTH, 20);
	tempitem.setCost(100);
	itemList.push_back(tempitem);
	
	tempitem.Clear();
	tempitem.setName("Iron Branch");
	tempitem.setValue(AGILITY, 1);
	tempitem.setValue(STRENGTH, 1);
	tempitem.setValue(INTELLIGENCE, 1);
	tempitem.setCost(50);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Ultimate Orb");
	tempitem.setValue(AGILITY, 10);
	tempitem.setValue(STRENGTH, 10);
	tempitem.setValue(INTELLIGENCE, 10);
	tempitem.setCost(2100);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Dagon lvl 5");
	tempitem.setValue(AGILITY, 3);
	tempitem.setValue(STRENGTH, 3);
	tempitem.setValue(INTELLIGENCE, 28);
	tempitem.setCost(7720);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Waluigi Hat");
	tempitem.setValue(RESRATE, 0.15f);
	tempitem.setCost(3000);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Master Sword");
	tempitem.setValue(AGILITY, 10);
	tempitem.setValue(STRENGTH, 20);
	tempitem.setValue(RESCLICK, 4);
	tempitem.setCost(5100);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Ashbringer");
	tempitem.setValue(STRENGTH, 85);
	tempitem.setValue(HP, 750);
	tempitem.setCost(20500);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Doomhammer");
	tempitem.setValue(AGILITY, 35);
	tempitem.setValue(HP, 200);
	tempitem.setCost(15300);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Frostmourne");
	tempitem.setValue(HP, 850);
	tempitem.setValue(INTELLIGENCE, 30);
	tempitem.setValue(AGILITY, 30);
	tempitem.setValue(STRENGTH, 30);
	tempitem.setCost(30000);
	tempitem.setValue(RESCLICK, 15);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Zweihander");
	tempitem.setValue(RESCLICK, 4);
	tempitem.setValue(STRENGTH, 15);
	tempitem.setValue(AGILITY, -5);
	tempitem.setCost(2050);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("AK-47");
	tempitem.setValue(RESRATE, 0.2f);
	tempitem.setCost(2100);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Sneaking Suit");
	tempitem.setValue(AGILITY, 40);
	tempitem.setCost(4000);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Tranq Gun");
	tempitem.setValue(AGILITY, 5);
	tempitem.setValue(RESCLICK, 2);
	tempitem.setCost(800);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Guitar Hero Guitar");
	tempitem.setValue(AGILITY, 15);
	tempitem.setValue(RESCLICK, 1);
	tempitem.setCost(1200);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Power Glove");
	tempitem.setCost(-500);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("N-Gage");
	tempitem.setValue(RESRATE, 0.1f);
	tempitem.setValue(RESCLICK, 3);
	tempitem.setCost(1900);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Oven Mitts");
	tempitem.setValue(AGILITY, -10);
	tempitem.setValue(RESCLICK, -1);
	tempitem.setValue(HP, 150);
	tempitem.setValue(INTELLIGENCE, 20);
	tempitem.setCost(1400);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Magic Boots");
	tempitem.setValue(AGILITY, 20);
	tempitem.setCost(700);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Tracksuit");
	tempitem.setValue(AGILITY, 5);
	tempitem.setValue(STRENGTH, 5);
	tempitem.setValue(INTELLIGENCE, 5);
	tempitem.setValue(HP, 100);
	tempitem.setCost(800);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("American Flag");
	tempitem.setValue(STRENGTH, 10);
	tempitem.setValue(RESRATE, 0.15f);
	tempitem.setCost(1200);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("BFG");
	tempitem.setValue(RESCLICK, 9);
	tempitem.setValue(STRENGTH, 60);
	tempitem.setCost(5550);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Gunblade");
	tempitem.setValue(AGILITY, 10);
	tempitem.setValue(STRENGTH, 10);
	tempitem.setValue(RESCLICK, 1);
	tempitem.setCost(1900);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Crowbar");
	tempitem.setValue(RESCLICK, 1);
	tempitem.setValue(STRENGTH, 20);
	tempitem.setValue(INTELLIGENCE, 10);
	tempitem.setCost(2900);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Thornwhip");
	tempitem.setValue(AGILITY, 10);
	tempitem.setValue(RESCLICK, 4);
	tempitem.setCost(2200);
	itemList.push_back(tempitem);

	tempitem.Clear();
	tempitem.setName("Metal Gear Rex Statue");
	tempitem.setValue(RESCLICK, 15);
	tempitem.setCost(3500);
	itemList.push_back(tempitem);



}


void Trail::swapItems(int c1, int s1, int c2, int s2) {
	Item temp;
	temp = party[c1].getItem(s1);
	party[c1].receiveItem(s1, party[c2].getItem(s2));
	party[c2].receiveItem(s2, temp);
}


void Trail::resetColors() {
	for (int i = 0; i < menu.numButtons(); ++i) {
		menu.ChangeColorJanky(i, bColor, hColor);

	}
}


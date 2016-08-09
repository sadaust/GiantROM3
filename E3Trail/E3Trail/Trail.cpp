#include "Trail.h"
#include <cstring>
#include <regex>
//update rate in seconds
#define UPDATETIME 0.1f

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
void gotoStartScreen() {
	Engine::instance()->postMessage("gotoMM");
}
void closeEvent() {
	Engine::instance()->postMessage("eventDone");
}

void Trail::createEvents() {
	TrailEvent tempevent;
	tempevent.reset();
	//taco bell
	tempevent.setText("%s found a tacobell and spent %s credits to buy a taco healing them by %s");
	tempevent.addEventEffect(TEvent::ranParty,0);
	tempevent.addEventEffect(TEvent::credits, -50);
	tempevent.addEventEffect(TEvent::Hp,50);
	eventList.push_back(tempevent);

	tempevent.reset();
}

void Trail::triggerEvent(int eventId) {
	int targChar = -1;
	std::vector<std::string> temp;
	char buffer[256];
	for(int i = 0; i < eventList[eventId].numEffect(); ++i) {
		switch(eventList[eventId].getEffect(i).targ) {
		case TEvent::ranParty:
			targChar = rand()%4;
			sprintf(buffer,"%s",party[targChar].getName().c_str());
			break;
		case TEvent::party0:
			targChar = 0;
			sprintf(buffer,"%s",party[targChar].getName().c_str());
			break;
		case TEvent::party1:
			targChar = 1;
			sprintf(buffer,"%s",party[targChar].getName().c_str());
			break;
		case TEvent::party2:
			targChar = 2;
			sprintf(buffer,"%s",party[targChar].getName().c_str());
			break;
		case TEvent::party3:
			targChar = 3;
			sprintf(buffer,"%s",party[targChar].getName().c_str());
			break;
		case TEvent::Hp:
			if(targChar>=0)
				party[targChar].modHp(eventList[eventId].getEffect(i).value);
			sprintf(buffer,"%d",abs(eventList[eventId].getEffect(i).value));
			break;
		case TEvent::Res:
			if(targChar>=0)
				party[targChar].modResource(eventList[eventId].getEffect(i).value);
			sprintf(buffer,"%d",abs(eventList[eventId].getEffect(i).value));
			break;
		case TEvent::randResource:
			switch(rand()%3) {
			case 0:
				credits += eventList[eventId].getEffect(i).value;
				break;
			case 1:
				fuel += eventList[eventId].getEffect(i).value;
				break;
			case 2:
				food += eventList[eventId].getEffect(i).value;
				break;
			}
			sprintf(buffer,"%d",abs(eventList[eventId].getEffect(i).value));
			break;
		case TEvent::credits:
			credits += eventList[eventId].getEffect(i).value;
			sprintf(buffer,"%d",abs(eventList[eventId].getEffect(i).value));
			break;
		case TEvent::fuel:
			fuel += eventList[eventId].getEffect(i).value;
			sprintf(buffer,"%d",abs(eventList[eventId].getEffect(i).value));
			break;
		case TEvent::food:
			food += eventList[eventId].getEffect(i).value;
			sprintf(buffer,"%d",abs(eventList[eventId].getEffect(i).value));
			break;
		}
		temp.push_back(buffer);
	}
	std::regex matcher;
	matcher = "%s";
	std::string z;
	z = eventList[eventId].getText();
	for(int i = 0; i < temp.size(); ++i) {
		z = std::regex_replace(z, matcher, temp[i],std::regex_constants::format_first_only);
	}
	frect temprec;
	temprec.left = 0;
	temprec.top = 0;
	temprec.right = 1;
	temprec.bottom = 1;
	eventText.text = z;
	eventText.color = 0xFFFFFFFF;
	eventText.flags = DT_CENTER|DT_VCENTER;
	eventText.rect = temprec;
	eventBackground.image = 0;
	pause = true;
	menu.clear();
	temprec.left = 0.25f;
	temprec.right = 0.75f;
	temprec.top = 0.8f;
	temprec.bottom = 0.9f;
	menu.addButton(closeEvent,"Back",temprec,DT_CENTER|DT_VCENTER,0xFFFFFFFF,0xFF0000FF);
}

Trail::Trail() {
	createEvents();
	pause = false;
	mapScaleX = 1;
	mapScaleY = 1;
	frect tempRec;
	running = false;
	path.color = D3DXCOLOR(0.0f,1,0,1.0f);
	path.width = 5;
	path.vecCount = 2;
	path.vec = pathVec;
	for (int i = 0; i < PARTYSIZE; ++i) {
		tempRec.top = 0.65f;
		tempRec.bottom = 0.9f;
		tempRec.left = 0.25*i;
		tempRec.right = tempRec.left + 0.25f;
		partyText[i][0].rect = tempRec;
		partyText[i][0].color = 0xFFFFFFFF;
		partyText[i][0].flags = DT_LEFT | DT_TOP;
		partyText[i][0].text = "ERROR";
		tempRec.top = 0.9f;
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
	map.center = D3DXVECTOR3(0,0,0);
	map.color = 0xFFFFFFFF;
	map.image = 0;
	map.rec.left = 0;
	map.rec.top = 0;
	locEventCount = 0;

	foodConsRate = 1;
	fuelCosRate = 1;
	noFuelSpeed = 5;


	// testing item swapping
	Engine::instance()->bind(SPACE, "Swap");
	// end of testing item swapping



}

void Trail::init(bool west, Character& p1, Character& p2, Character& p3, Character& p4) {
	menu.init();
	pause = false;
	if (west) {
		startDist = 400;
		map.image = (imageAsset*)(Engine::instance()->getResource("SFMap.png",D3DXCOLOR(0,0,0,255))->resource);
		map.rec.bottom = map.image->texInfo.Height;
		map.rec.right = map.image->texInfo.Width;
		start.x = 0 * map.rec.right;
		start.y = 0 * map.rec.bottom;
		start.z = 0;
		end.x = 1.0f * map.rec.right;
		end.y = 1.0f * map.rec.bottom;
		end.z = 0;
		locEventCount = 10;
	} else {
		startDist = 2800;
		map.image = (imageAsset*)(Engine::instance()->getResource("NYMap.png",D3DXCOLOR(0,0,0,255))->resource);
		map.rec.bottom = map.image->texInfo.Height;
		map.rec.right = map.image->texInfo.Width;
		start.x = 1.0f * map.rec.right;
		start.y = 1.0f * map.rec.bottom;
		start.z = 0;
		end.x = 0 * map.rec.right;
		end.y = 0 * map.rec.bottom;
		end.z = 0;
		locEventCount = 50;
	}
	if(locEventCount > MAXLOCEVENT) {
		locEventCount = MAXLOCEVENT;
	}
	mapScaleX = (Engine::instance()->getWidth()*0.8f)/(float)map.rec.right;
	mapScaleY = (Engine::instance()->getHeight()*0.65f)/(float)map.rec.bottom;
	start.x *= mapScaleX;
	start.y *= mapScaleY;
	end.x *= mapScaleX;
	end.y *= mapScaleY;
	//events[locEventCount - 1].type = e3;
	//events[locEventCount - 1].dist = 0;
	time = 0;
	food = 500;
	credits = 5000;
	fuel = 500;
	speed = 10;
	distToGo = startDist;
	party[0] = p1;
	party[1] = p2;
	party[2] = p3;
	party[3] = p4;
	running = true;

	setClickerButtons();
}

void Trail::init(bool west) {
	Character temp[PARTYSIZE];
	Item tempitem;
	tempitem.setName("Doritos Locos Taco");
	tempitem.setValue(STRENGTH, 10);
	tempitem.setValue(AGILITY, 10);
	tempitem.setValue(INTELLIGENCE, 10);
	tempitem.setValue(RESRATE, 10);
	temp[0].init("Dan", "Amiibo");
	temp[0].receiveItem(0, tempitem);
	tempitem.Clear();
	tempitem.setName("Spaghetti Can");
	tempitem.setValue(HP, 50);
	temp[1].init("Brad", "Dota hats");
	temp[1].receiveItem(0, tempitem);
	temp[2].init("Rorie", "Puppies");
	temp[3].init("Austin", "Gunpla");
	init(west, temp[0], temp[1], temp[2], temp[3]);
}

int Trail::aliveCount() {
	int count = 0;
	for(int i = 0; i < PARTYSIZE; ++i) {
		count += (party[i].getHP() > 0);
	}
	return count;
}

void Trail::setClickerButtons() {
	frect rec;
	char buffer[256];
	DWORD bColor = 0xFF0000FF;
	DWORD hColor = 0xFF00FF00;
	rec.bottom = 0.65f;
	rec.top = 0.60f;
	menu.clear();
	//party[0] incer
	rec.left = 0.0f;
	rec.right = 0.25f;
	sprintf(buffer,"Produce %s",party[0].getResName().c_str());
	menu.addButton(clicker0,buffer,rec,DT_CENTER | DT_VCENTER,bColor,hColor);
	//party[1] incer
	rec.left = 0.25f;
	rec.right = 0.5f;
	sprintf(buffer,"Produce %s",party[1].getResName().c_str());
	menu.addButton(clicker1,buffer,rec,DT_CENTER | DT_VCENTER,bColor,hColor);
	//party[2] incer
	rec.left = 0.5f;
	rec.right = 0.75f;
	sprintf(buffer,"Produce %s",party[2].getResName().c_str());
	menu.addButton(clicker2,buffer,rec,DT_CENTER | DT_VCENTER,bColor,hColor);
	//party[3] incer
	rec.left = 0.75f;
	rec.right = 1.0f;
	sprintf(buffer,"Produce %s",party[3].getResName().c_str());
	menu.addButton(clicker3,buffer,rec,DT_CENTER | DT_VCENTER,bColor,hColor);
}

void Trail::startEndScreen() {
	frect tempRec;
	char buffer[256];
	menu.clear();
	tempRec.left = 0.25f;
	tempRec.right = 0.75f;
	tempRec.top = 0.8f;
	tempRec.bottom = 0.9f;
	menu.addButton(gotoStartScreen,"Return to Main Menu",tempRec,DT_CENTER | DT_VCENTER, 0xFF0000FF, 0xFF00FF00);
	tempRec.bottom = 0.7f;
	tempRec.top = 0.2f;
	eventBackground.image = 0;
	eventText.rect = tempRec;
	eventText.color = 0xFFFFFFFF;
	eventText.flags = DT_LEFT | DT_VCENTER;
	if(aliveCount() > 0) {
		eventText.text = "At least one person made it to E3";
	} else {
		eventText.text = "No one made it to E3";
	}
	pause = true;
}

bool Trail::update() {
	char buffer[256];
	renInfo tempRen;
	D3DXMATRIX tempMat;
	D3DXMatrixIdentity(&tempRen.matrix);
	D3DXMatrixIdentity(&tempMat);
	D3DXMatrixTranslation(&tempRen.matrix,0,0,1);
	if (running) {
		menu.update();
		menu.render();

		//return to main menu
		if (Engine::instance()->getBind("Back")||Engine::instance()->getMessage("gotoMM")) {
			running = false;
			return false;
		}
		//incrementor logic
		if(aliveCount() == 0 || distToGo <= 0) {
			startEndScreen();
		}
		if(!pause){
			// testing item swapping
			if (Engine::instance()->getBind("Swap")) {
				triggerEvent(0);
			}
			// end of testing item swapping
			time += Engine::instance()->dt();
			if(Engine::instance()->getMessage("Incer0")) {
				party[0].resIncer();
			} else if(Engine::instance()->getMessage("Incer1")) {
				party[1].resIncer();
			} else if(Engine::instance()->getMessage("Incer2")) {
				party[2].resIncer();
			} else if(Engine::instance()->getMessage("Incer3")) {
				party[3].resIncer();
			}

			if (time >= UPDATETIME) {
				time -= UPDATETIME;

				if(fuel > 0) {
					distToGo -= speed;
					fuel -= speed * fuelCosRate;
					if(fuel < 0) {
						fuel = 0;
					}
				} else {
					distToGo -= noFuelSpeed;
				}

				if(food > 0) {
					food -= aliveCount()*foodConsRate;
					if(food <= 0) {
						food = 0;
					}
				} else {
					for(int i = 0; i < PARTYSIZE; ++i) {
						party[i].modHp(-5);
					}
				}

				for (int i = 0; i < PARTYSIZE; ++i) {
					party[i].resIncer();
				}
			}
			//render the main play screen
			tempRen.type = text;
			for (int i = 0; i < PARTYSIZE; ++i) {
				sprintf(buffer, "%s: %d\n%s\n%s\nStr: %d\nAgi: %d\nInt: %d", party[i].getResName().c_str(), party[i].getResource(), party[i].getItemName(0).c_str(), party[i].getItemName(1).c_str(), party[i].getStrength(), party[i].getAgility(), party[i].getIntelligence());
				partyText[i][0].text = buffer;
				tempRen.asset = &partyText[i][0];
				Engine::instance()->addRender(tempRen);
				//
				sprintf(buffer, "%s HP: %03d/%03d", party[i].getName().c_str(), party[i].getHP(), party[i].getMaxHP());
				partyText[i][1].text = buffer;
				tempRen.asset = &partyText[i][1];
				Engine::instance()->addRender(tempRen);
			}
			sprintf(buffer, "Credits: %d", credits);
			renstats[0].text = buffer;
			sprintf(buffer, "Food: %d", food);
			renstats[1].text = buffer;
			sprintf(buffer, "Fuel: %d", fuel);
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
			//path line
			pathVec[0].x = start.x;
			pathVec[0].y = start.y;
			pathVec[1].x = start.x+((end.x-start.x) * (1.0f-(distToGo/(float)startDist)));
			pathVec[1].y = start.y+((end.y-start.y) * (1.0f-(distToGo/(float)startDist)));
			tempRen.type = line;
			tempRen.asset = &path;
			D3DXMatrixIdentity(&tempRen.matrix);
			Engine::instance()->addRender(tempRen);
			//map
			tempRen.asset = &map;
			tempRen.type = screenSprite;
			D3DXMatrixScaling(&tempRen.matrix,mapScaleX,mapScaleY,1);
			D3DXMatrixTranslation(&tempMat,0,0,1);
			D3DXMatrixMultiply(&tempRen.matrix,&tempRen.matrix,&tempMat);
			Engine::instance()->addRender(tempRen);
		} else {
			tempRen.type = screenSprite;
			if(eventBackground.image) {
				tempRen.asset = &eventBackground;
				Engine::instance()->addRender(tempRen);
			}
			D3DXMatrixIdentity(&tempRen.matrix);
			tempRen.type = text;
			tempRen.asset = &eventText;
			Engine::instance()->addRender(tempRen);
			if(Engine::instance()->getMessage("eventDone")) {
				pause = false;
				setClickerButtons();
			}
		}
	}
	return running;
}


void Trail::swapItems(int c1, int s1, int c2, int s2) {
	Item temp;
	temp = party[c1].getItem(s1);
	party[c1].receiveItem(s1, party[c2].getItem(s2));
	party[c2].receiveItem(s2, temp);
}





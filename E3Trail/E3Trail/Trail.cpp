#include "Trail.h"

//update rate in seconds
#define UPDATETIME 0.1f

Trail::Trail() {
	frect tempRec;
	running = false;
	path.color = D3DXCOLOR(0.0f,1,0,1.0f);
	path.width = 5;
	path.vecCount = 2;
	path.vec = pathVec;
	for (int i = 0; i < PARTYSIZE; ++i) {
		tempRec.top = 0.65f;
		tempRec.bottom = 0.85f;
		tempRec.left = 0.25*i;
		tempRec.right = tempRec.left + 0.25f;
		partyText[i][0].rect = tempRec;
		partyText[i][0].color = 0xFFFFFFFF;
		partyText[i][0].flags = DT_LEFT | DT_BOTTOM;
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
}

void Trail::init(bool west, Character p1, Character p2, Character p3, Character p4) {
	menu.init();
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
}

void Trail::init(bool west) {
	menu.init();
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
	events[locEventCount - 1].type = e3;
	events[locEventCount - 1].dist = 0;
	time = 0;
	food = 500;
	credits = 5000;
	fuel = 500;
	speed = 10;
	distToGo = startDist;
	Character temp;
	Item tempitem;
	tempitem.setName("Doritos Locos Taco");
	tempitem.setValue(STRENGTH, 10);
	tempitem.setValue(HP, 50);
	temp.init("Dan", "Amiibo");
	party[0] = temp;
	party[0].receiveItem(0, tempitem);
	tempitem.Clear();
	tempitem.setName("Spaghetti Can");
	tempitem.setValue(STRENGTH, 25);
	temp.init("Brad", "Dota hats");
	party[1] = temp;
	party[1].receiveItem(0, tempitem);
	temp.init("Rorie", "Puppies");
	party[2] = temp;
	temp.init("Austin", "Gunpla");
	party[3] = temp;
	running = true;
}

int Trail::aliveCount() {
	int count = 0;
	for(int i = 0; i < PARTYSIZE; ++i) {
		count += (party[i].getHP() >= 0);
	}
	return count;
};

bool Trail::update() {
	char buffer[256];
	renInfo tempRen;
	D3DXMatrixIdentity(&tempRen.matrix);
	D3DXMatrixTranslation(&tempRen.matrix,0,0,1);
	if (running) {
		//return to main menu
		if (Engine::instance()->getBind("Back")) {
			running = false;
			return false;
		}
		//incrementor logic
		time += Engine::instance()->dt();
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
		menu.update();
		menu.render();
		//render the main play screen
		tempRen.type = text;
		for (int i = 0; i < PARTYSIZE; ++i) {
			sprintf(buffer, "%s: %d\n%s\n%s\nStr: %d", party[i].getResName().c_str(), party[i].getResource(), party[i].getItemName(0).c_str(), party[i].getItemName(1).c_str() , party[i].getStrength());
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
		pathVec[1].x = end.x * (1-(distToGo/(float)startDist));
		pathVec[1].y = end.y * (1-(distToGo/(float)startDist));
		tempRen.type = line;
		tempRen.asset = &path;
		D3DXMatrixIdentity(&tempRen.matrix);
		Engine::instance()->addRender(tempRen);
		//map
		tempRen.asset = &map;
		tempRen.type = screenSprite;
		D3DXMatrixTranslation(&tempRen.matrix,0,0,1);
		Engine::instance()->addRender(tempRen);
	}
	return running;
}
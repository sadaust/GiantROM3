#include "Trail.h"

Trail::Trail() {
	frect tempRec;
	running = false;
	for (int i = 0; i < PARTYSIZE; ++i) {
		tempRec.top = 0.75f;
		tempRec.bottom = 0.8f;
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
}

void Trail::init(bool west, Character p1, Character p2, Character p3, Character p4) {
	menu.init();
	if (west) {
		startDist = 400;
	}
	else {
		startDist = 2800;
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
	}
	else {
		startDist = 2800;
	}
	time = 0;
	food = 500;
	credits = 5000;
	fuel = 500;
	speed = 10;
	distToGo = startDist;
	Character temp;
	temp.init("Dan", "Amiibo");
	party[0] = temp;
	temp.init("Brad", "Dota hats");
	party[1] = temp;
	temp.init("Rorie", "Puppies");
	party[2] = temp;
	temp.init("Austin", "Gunpla");
	party[3] = temp;
	running = true;
}

bool Trail::update() {
	char buffer[256];
	renInfo tempRen;
	D3DXMatrixIdentity(&tempRen.matrix);
	if (running) {
		//return to main menu
		if (Engine::instance()->getBind("Back")) {
			running = false;
			return false;
		}
		//incrementor logic
		time += Engine::instance()->dt();
		if (time >= 6) {
			time -= 6;
			distToGo -= speed;
			for (int i = 0; i < PARTYSIZE; ++i) {
				party[i].resIncer();
			}
		}
		menu.update();
		menu.render();
		//render the main play screen
		tempRen.type = text;
		for (int i = 0; i < PARTYSIZE; ++i) {
			sprintf(buffer, "%s: %d", party[i].getResName().c_str(), party[i].getResource());
			partyText[i][0].text = buffer;
			tempRen.asset = &partyText[i][0];
			Engine::instance()->addRender(tempRen);
			//
			sprintf(buffer, "%s HP: %d/%d", party[i].getName().c_str(), party[i].getMaxHP(), party[i].getHP());
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
	}
	return running;
}
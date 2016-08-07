#include "Trail.h"

Trail::Trail() {
	frect tempRec;
	running = false;
	for(int i = 0; i < PARTYSIZE; ++i) {
		tempRec.top = 0.75f;
		tempRec.bottom = 0.85f;
		tempRec.left = 0.25*i;
		tempRec.right = tempRec.left+0.25f;
		partyText[i][0].rect = tempRec;
		partyText[i][0].color = 0xFFFFFFFF;
		partyText[i][0].flags = DT_LEFT | DT_VCENTER;
		partyText[i][0].text = "ERROR";
		tempRec.top = 0.9f;
		tempRec.bottom = 1.0f;
		partyText[i][1].rect = tempRec;
		partyText[i][1].color = 0xFFFFFFFF;
		partyText[i][1].flags = DT_LEFT | DT_VCENTER;
		partyText[i][1].text = "ERROR";
	}
}

void Trail::init(bool west, Character p1, Character p2, Character p3 , Character p4) {
	if(west) {
		startDist = 400;
	} else {
		startDist = 2800;
	}
	party[0] = p1;
	party[1] = p2;
	party[2] = p3;
	party[3] = p4;
	running = true;
}

void Trail::init(bool west) {
	if(west) {
		startDist = 400;
	} else {
		startDist = 2800;
	}
	Character temp;
	temp.init("Dan","Amiibo");
	party[0] = temp;
	temp.init("Brad","Dota hats");
	party[1] = temp;
	temp.init("Rorie","Puppies");
	party[2] = temp;
	temp.init("Austin","Gunpla");
	party[3] = temp;
	running = true;
}

bool Trail::update() {
	char buffer[256];
	renInfo tempRen;
	D3DXMatrixIdentity(&tempRen.matrix);
	if(running) {
		tempRen.type = text;
		for(int i = 0; i < PARTYSIZE; ++i) {
			sprintf(buffer,"%s: %d",party[i].getResName().c_str(),party[i].getResource());
			partyText[i][0].text = buffer;
			tempRen.asset = &partyText[i][0];
			Engine::instance()->addRender(tempRen);
			//
			sprintf(buffer,"%s HP: %d",party[i].getName().c_str(),party[i].getHP());
			partyText[i][1].text = buffer;
			tempRen.asset = &partyText[i][1];
			Engine::instance()->addRender(tempRen);
		}
	}
	return running;
}
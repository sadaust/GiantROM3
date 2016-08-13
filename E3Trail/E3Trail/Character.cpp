#pragma once
#include "Character.h"
#include <regex>






void Character::init(std::string a_name, std::string resourceName) {
	maxhp = 100;
	hp = maxhp;
	strength = 10; // probably change this for balance. Used for minigames and event thresholds
	agility = 10;
	intelligence = 10;
	resource = 0;
	resrate = 0.1f;
	resclickrate = 1;
	name = a_name;
	resName = resourceName;
	for (int i = 0; i < NUM_ITEMS; ++i) {
		activeitems[i] = false;
		items[i].Clear();
	}

	for(int i = 0; i < NUM_STATUS; ++i) {
		statusPic[i].center = D3DXVECTOR3(0, 0, 0);
		statusPic[i].color = 0xFFFFFFFF;
		statusPic[i].rec.top = 0;
		statusPic[i].rec.left = 0;
	}
	victory = "They did a thing!!!";
	// loading images.

	if (name == "Brad") {
		statusPic[0].image = (imageAsset*)(Engine::instance()->getResource("brad000.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[0].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[0].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[1].image = (imageAsset*)(Engine::instance()->getResource("brad033.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[1].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[1].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[2].image = (imageAsset*)(Engine::instance()->getResource("brad066.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[2].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[2].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[3].image = (imageAsset*)(Engine::instance()->getResource("brad100.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[3].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[3].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[4].image = (imageAsset*)(Engine::instance()->getResource("brad133.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[4].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[4].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[5].image = (imageAsset*)(Engine::instance()->getResource("bradevil.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[5].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[5].rec.right = statusPic[0].image->texInfo.Width;
	}
	else if (name == "Dan") {
		statusPic[0].image = (imageAsset*)(Engine::instance()->getResource("dan000.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[0].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[0].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[1].image = (imageAsset*)(Engine::instance()->getResource("dan033.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[1].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[1].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[2].image = (imageAsset*)(Engine::instance()->getResource("dan066.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[2].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[2].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[3].image = (imageAsset*)(Engine::instance()->getResource("dan100.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[3].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[3].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[4].image = (imageAsset*)(Engine::instance()->getResource("dan133.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[4].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[4].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[5].image = (imageAsset*)(Engine::instance()->getResource("danevil.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[5].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[5].rec.right = statusPic[0].image->texInfo.Width;
	}
	else if (name == "Rorie") {
		statusPic[0].image = (imageAsset*)(Engine::instance()->getResource("rorie000.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[0].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[0].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[1].image = (imageAsset*)(Engine::instance()->getResource("rorie033.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[1].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[1].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[2].image = (imageAsset*)(Engine::instance()->getResource("rorie066.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[2].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[2].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[3].image = (imageAsset*)(Engine::instance()->getResource("rorie100.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[3].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[3].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[4].image = (imageAsset*)(Engine::instance()->getResource("rorie133.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[4].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[4].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[5].image = (imageAsset*)(Engine::instance()->getResource("rorieevil.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[5].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[5].rec.right = statusPic[0].image->texInfo.Width;
	}
	else if (name == "Austin") {
		statusPic[0].image = (imageAsset*)(Engine::instance()->getResource("austin000.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[0].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[0].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[1].image = (imageAsset*)(Engine::instance()->getResource("austin033.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[1].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[1].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[2].image = (imageAsset*)(Engine::instance()->getResource("austin066.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[2].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[2].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[3].image = (imageAsset*)(Engine::instance()->getResource("austin100.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[3].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[3].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[4].image = (imageAsset*)(Engine::instance()->getResource("austin133.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[4].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[4].rec.right = statusPic[0].image->texInfo.Width;

		statusPic[5].image = (imageAsset*)(Engine::instance()->getResource("austinevil.png", D3DXCOLOR(0, 0, 0, 255))->resource);
		statusPic[5].rec.bottom = statusPic[0].image->texInfo.Height;
		statusPic[5].rec.right = statusPic[0].image->texInfo.Width;
	}


}


void Character::Draw(int index) {
	renInfo tempRen;
	D3DXMATRIX tempMat;

	D3DXMatrixIdentity(&tempRen.matrix);
	D3DXMatrixIdentity(&tempMat);
	D3DXMatrixTranslation(&tempRen.matrix, 0, 0, 1);

	if (hp <= 0) {
		tempRen.asset = &statusPic[0];
	}
	else if (hp > 0 && hp <= 33) {
		tempRen.asset = &statusPic[1];
	}
	else if (hp > 33 && hp <= 66) {
		tempRen.asset = &statusPic[2];
	}
	else if (hp > 66 && hp <= 100) {
		tempRen.asset = &statusPic[3];
	}
	else if (hp > 100) {
		tempRen.asset = &statusPic[4];
	}
	//TO DO: EVIL TAKING PRECEDENCE OVER DAMAGE


	float x = Engine::instance()->getWidth()*0.08f + (index * Engine::instance()->getWidth()*.25f), y = Engine::instance()->getHeight()*0.83f;
	tempRen.type = screenSprite;
	D3DXMatrixScaling(&tempRen.matrix, STATUS_PIC_SCALE, STATUS_PIC_SCALE, 1);
	D3DXMatrixTranslation(&tempMat, x, y, 0);
	D3DXMatrixMultiply(&tempRen.matrix, &tempRen.matrix, &tempMat);
	Engine::instance()->addRender(tempRen);


}


int Character::getHP() { 
	return hp; 
}


int Character::getMaxHP() {
	return maxhp; 
}


int Character::getStrength() { 
	return strength; 
}


int Character::getAgility() { 
	return agility; 
}


int Character::getIntelligence() { 
	return intelligence; 
}


int Character::getResource() { 
	return resource; 
}


std::string Character::getResName() { 
	return resName; 
}


std::string Character::getName() { 
	return name; 
}


void Character::resIncer() { 
	resource += resrate; 
}


void Character::resClick() { 
	resource += resclickrate; 
}


void Character::modHp(int mod) { 
	hp += mod; 
	if (hp < 0) { 
		hp = 0; 
	} 
}


void Character::modMaxHp(int mod) { 
	maxhp += mod; 
}


void Character::modStrength(int mod) { 
	strength += mod; 
}


void Character::modAgility(int mod) { 
	agility += mod; 
}


void Character::modIntelligence(int mod) { 
	intelligence += mod; 
}


void Character::modResource(int mod) { 
	resource += mod; 
	if (resource < 0) { 
		resource = 0; 
	} 
}


void Character::operator=(Character& in) {
	hp = in.hp;
	maxhp = in.maxhp;
	strength = in.strength;
	agility = in.agility;
	intelligence = in.intelligence;
	resource = in.resource;
	resrate = in.resrate;
	resclickrate = in.resclickrate;
	name = in.name;
	resName = in.resName;
	victory = in.victory;
	for (int i = 0; i < NUM_STATUS; ++i) {
		statusPic[i] = in.statusPic[i];
	}
	for (int i = 0; i < NUM_ITEMS; ++i) {
		items[i] = in.items[i];
		activeitems[i] = in.activeitems[i];
	}
	for (int i = 0; i < NUM_STATUS; ++i) {
		statusPic[i] = in.statusPic[i];
	}
}


// iTEM STUFF
Item Character::getItem(int index) { 
	return items[index]; 
} // don't you dare ask for an item outside of NUM_ITEMS


bool Character::getActiveItem(int index) { 
	return activeitems[index]; 
}


std::string Character::getItemName(int index) { 
	return items[index].getName(); 
}


void Character::receiveItem(int index, Item &a_item) {
	Attribute tempatt;
	if (activeitems[index]) {
		for (int i = 0; i < items[index].numAtt(); ++i) { // Remove the old item if there is one active.
			tempatt = items[index].getAttribute(i);
			if (tempatt == STRENGTH) {
				strength -= items[index].getValue(i);
				if (strength < 0)
					strength = 0;
			}
			else if (tempatt == AGILITY) {
				agility -= items[index].getValue(i);
				if (agility < 0)
					agility = 0;
			}
			else if (tempatt == INTELLIGENCE) {
				intelligence -= items[index].getValue(i);
				if (intelligence < 0)
					intelligence = 0;
			}
			else if (tempatt == HP) {
				maxhp -= items[index].getValue(i);
				hp -= items[index].getValue(i);
				if (maxhp < 0)
					maxhp = 0;
				if (hp < 0)
					hp = 0;
			}
			else if (tempatt == RESRATE) {
				resrate -= items[index].getValue(i);
				if (resrate < 0)
					resrate = 0;
			}
			else if (tempatt == RESCLICK) {
				resclickrate -= items[index].getValue(i);
				if (resclickrate < 0)
					resclickrate = 0;
			}
		}

	}



	items[index] = a_item; // change the item.


	if (a_item.getName() != "Empty" && a_item.getName() != "Error") {
		for (int i = 0; i < a_item.numAtt(); ++i) { // Add the new item's stuff to your stats
			tempatt = a_item.getAttribute(i);
			if (tempatt == STRENGTH) {
				strength += a_item.getValue(i);
				if (strength < 0)
					strength = 0;
			}
			else if (tempatt == AGILITY) {
				agility += items[index].getValue(i);
				if (agility < 0)
					agility = 0;
			}
			else if (tempatt == INTELLIGENCE) {
				intelligence += items[index].getValue(i);
				if (intelligence < 0)
					intelligence = 0;
			}
			else if (tempatt == HP) {
				maxhp += a_item.getValue(i);
				hp += a_item.getValue(i);
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
			else if (tempatt == RESCLICK) {
				resclickrate += a_item.getValue(i);
				if (resclickrate < 0)
					resclickrate = 0;
			}
		}
		activeitems[index] = true;
	}
	else
		activeitems[index] = false;
}
// end of receiveItem

std::string Character::getVictory() {
	std::regex matcher;
	matcher = "%s";
	char buffer[256];
	std::string timeScale[] = {"seconds","minutes","hours","days","weeks","months","years"};
	std::string locations[] = {"a cave","a swimming pool","an abandond building","a ditch","the GiantBomb office","a dingy basement","the Lang zone"};
	std::string z;
	std::vector<std::string> temp;
	if(hp>0) {
		return victory;
	} else {
		//lose template
		z = "%s was found %s %s later in %s surrounded by %s";
		//name
		temp.push_back(name);
		//time
		sprintf(buffer,"%d",2+rand()%29);
		temp.push_back(buffer);
		//time scale
		temp.push_back(timeScale[rand()%7]);
		//location
		temp.push_back(locations[rand()%7]);
		//resource
		sprintf(buffer,"%.0f %s",resource,resName.c_str());
		temp.push_back(buffer);
		for (int i = 0; i < temp.size(); ++i) {
			z = std::regex_replace(z, matcher, temp[i], std::regex_constants::format_first_only);
		}
		return z;
	}
}


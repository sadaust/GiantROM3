#include "Game.h"

void noFunc() {
}

void startEast() {
	Engine::instance()->postMessage("East");
}

void startWest() {
	Engine::instance()->postMessage("West");
}

void startCredits() {
	Engine::instance()->postMessage("Credits");
}

void leaveCredits() {
	Engine::instance()->postMessage("LeaveCredits");
}

void quitMsg() {
	Engine::instance()->postMessage("Quit");
}

Game::Game() {
	cam.fov = 90.0f;
	cam.cam_pos = D3DXVECTOR3(0,0,2000);
	cam.cam_up_vec = D3DXVECTOR3(0,1,0);
	cam.cam_look_pos = D3DXVECTOR3(0,0,0);
	cam.drawDist = 5000;
	fps = 0;
	srand(time(0));
};

Game::~Game() {
	shutdown();
};

void Game::init() {
	mainMenu.init();
	//Init input
	Engine::instance()->bind(W,"SelectionUp");
	Engine::instance()->bind(S,"SelectionDown");
	//Engine::instance()->bind(SPACE,"Accept");
	Engine::instance()->bind(mouse_0,"Accept");
	Engine::instance()->bind(mouse_Xp,mouse_Xn,"MouseX");
	Engine::instance()->bind(mouse_Yp,mouse_Yn,"MouseY");
	Engine::instance()->bind(ESC,"Back");
	Engine::instance()->setRepeat(0.75);

	//init menu
	buildMenu(false);
};

bool Game::update() {
	if(!trail.update()) {
		mainMenu.update();
		mainMenu.render();
		if(Engine::instance()->getMessage("Quit"))
			return false;
		if (Engine::instance()->getMessage("Credits")) {
			buildMenu(true);
		}
		else if (Engine::instance()->getMessage("LeaveCredits")) {
			buildMenu(false);
		}
		else if (Engine::instance()->getMessage("East")) {
			trail.init(false);
		} else if(Engine::instance()->getMessage("West")) {
			trail.init(true);
		}
	}
	trail.render();
	Engine::instance()->render();
	Engine::instance()->clearMessages();
	//keep the game running
	return true;
};

void Game::shutdown() {
	mainMenu.clear();
};





void Game::buildMenu(bool credits) {
	frect temp;
	mainMenu.clear();
	temp.left = 0.25;
	temp.right = 0.75;

	if (credits) {
		temp.top = 0.3;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(noFunc, "Created by\nTyler Van Gastel\nand\nJosh Foley", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFFFFFFFF);

		temp.top = 0.4;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(noFunc, "For the Giant Rom 3 game jam\non 8/14/2016", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFFFFFFFF);

		temp.top = 0.5;
		temp.bottom = temp.top + 0.2;

		mainMenu.addButton(noFunc, "duder images from\nsnakesnakesnake.com\nand\ngoogle images", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFFFFFFFF);

		temp.top = 0.7;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(leaveCredits, "Back to main menu", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFF0000FF);
	}
	else {
		temp.left = 0.25;
		temp.right = 0.75;

		temp.top = 0.4;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(startWest, "Start: West", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFF0000FF);

		temp.top = 0.5;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(startEast, "Start: East", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFF0000FF);

		temp.top = 0.65;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(startCredits, "Credits", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFF0000FF);

		temp.top = 0.8;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(quitMsg, "Quit", temp, DT_CENTER | DT_VCENTER, 0xFFFFFFFF, 0xFF0000FF);
	}
}





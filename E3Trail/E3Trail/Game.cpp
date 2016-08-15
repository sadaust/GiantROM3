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
	bColor = 0xFF0000FF;
	hColor = 0xFF00FF00;
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
	Engine::instance()->setVolume(0.1f,music);
	//trail.init(true);
	logo.color = 0xFFFFFFFF;
	logo.rec.top = 0;
	logo.rec.left = 0;
	logo.image = (imageAsset*)(Engine::instance()->getResource("logo.png", D3DXCOLOR(0, 0, 0, 0))->resource);
	logo.rec.bottom = logo.image->texInfo.Height;
	logo.rec.right = logo.image->texInfo.Width;
	logo.center = D3DXVECTOR3(logo.rec.right/2, logo.rec.bottom/2, 0);
	drawLogo = true;
	menuMusic = *(musicStruct*)Engine::instance()->getResource("Maximalism-EntertheFuturion.mp3",stream)->resource;
	Engine::instance()->playMusic(menuMusic,false);
	//init menu
	buildMenu(false);
	restartMusic = false;
};

bool Game::update() {
	renInfo tempRen;
	D3DXMATRIX tempMat;
	if(!trail.update()) {
		if(restartMusic) {
			Engine::instance()->playMusic(menuMusic,false);
			restartMusic = false;
		}
		mainMenu.update();
		mainMenu.render();
		//logo
		if(drawLogo) {
			tempRen.asset = &logo;
			tempRen.type = screenSprite;
			D3DXMatrixIdentity(&tempRen.matrix);
			D3DXMatrixIdentity(&tempMat);
			D3DXMatrixScaling(&tempRen.matrix,0.5,0.5,1);
			D3DXMatrixTranslation(&tempMat,Engine::instance()->width()/2,Engine::instance()->height()/3,1);
			D3DXMatrixMultiply(&tempRen.matrix,&tempRen.matrix,&tempMat);
			Engine::instance()->addRender(tempRen);
		}
		if(Engine::instance()->getMessage("Quit"))
			return false;
		if (Engine::instance()->getMessage("Credits")) {
			drawLogo = false;
			buildMenu(true);
		}
		else if (Engine::instance()->getMessage("LeaveCredits")) {
			drawLogo = true;
			buildMenu(false);
		}
		else if (Engine::instance()->getMessage("East")) {
			Engine::instance()->playMusic(menuMusic,true);
			restartMusic = true;
			trail.init(false);
		} else if(Engine::instance()->getMessage("West")) {
			Engine::instance()->playMusic(menuMusic,true);
			restartMusic = true;
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
		temp.top = 0.2;
		temp.bottom = temp.top + 0.2;

		mainMenu.addButton(noFunc, "Created by\nTyler Van Gastel\nand\nJosh Foley", temp, DT_CENTER | DT_VCENTER | DT_WORDBREAK, 0xFFFFFFFF, 0xFFFFFFFF );

		temp.top = 0.4;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(noFunc, "For the Giant Rom 3 game jam\n8/6/2016-8/14/2016", temp, DT_CENTER | DT_VCENTER | DT_WORDBREAK, 0xFFFFFFFF, 0xFFFFFFFF );

		temp.top = 0.5;
		temp.bottom = temp.top + 0.2;

		mainMenu.addButton(noFunc, "Music by Maximalism\nDuder images from snakesnakesnake.com\nand google images", temp, DT_CENTER | DT_VCENTER | DT_WORDBREAK, 0xFFFFFFFF, 0xFFFFFFFF );

		temp.top = 0.7;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(leaveCredits, "Back to main menu", temp, DT_CENTER | DT_VCENTER, bColor, hColor );
	}
	else {
		temp.left = 0.25;
		temp.right = 0.75;

		temp.top = 0.4;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(startWest, "Start: West", temp, DT_CENTER | DT_VCENTER, bColor, hColor );

		temp.top = 0.5;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(startEast, "Start: East", temp, DT_CENTER | DT_VCENTER, bColor, hColor );

		temp.top = 0.65;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(startCredits, "Credits", temp, DT_CENTER | DT_VCENTER, bColor, hColor );

		temp.top = 0.8;
		temp.bottom = temp.top + 0.1;

		mainMenu.addButton(quitMsg, "Quit", temp, DT_CENTER | DT_VCENTER, bColor, hColor );
	}
}





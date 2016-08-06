#include "MenuSystem.h"

MenuSystem::MenuSystem() {
	hold = false;
	selection = 0;
}

void MenuSystem::init() {
	//click = *(soundStruct*)Engine::instance()->getResource("click.ogg", audio)->resource;
	//rollover = *(soundStruct*)Engine::instance()->getResource("rollover.ogg", audio)->resource;
	soundvec.x = 0;
	soundvec.y = 0;
	soundvec.z = 0;

	_mX = 0;
	_mY = 0;
	_height = Engine::instance()->getHeight();
	_width = Engine::instance()->getWidth();
	cursor.image = (imageAsset*)(Engine::instance()->getResource("default.bmp",D3DXCOLOR(0,0,0,1))->resource);
	cursor.color = D3DXCOLOR(255,255,255,255);
	cursor.center = D3DXVECTOR3(0,0,0);
	cursor.rec.top = 0;
	cursor.rec.left = 0;
	cursor.rec.right = cursor.image->texInfo.Width;
	cursor.rec.bottom = cursor.image->texInfo.Height;
}


void MenuSystem::clear() {
	while(buttons.size())
		buttons.pop_back();
}

void MenuSystem::update() {
	_mX += Engine::instance()->getAxis("MouseX");
	_mY += Engine::instance()->getAxis("MouseY");
	if(_mX < 0) {
		_mX = 0;
	} else if(_mX > _width) {
		_mX = _width;
	}
	if(_mY < 0) {
		_mY = 0;
	} else if(_mY > _height) {
		_mY = _height;
	}

	float sx = 0;
	float sy = 0;
	sx = _mX / (float)_width;
	sy = _mY / (float)_height;
	if(buttons.size() > 0) {
		if(Engine::instance()->getAxis("MouseX") != 0 || Engine::instance()->getAxis("MouseY") != 0){
			for(int i = 0; i < buttons.size(); ++i) {
				if(buttons[i].mouseHover(sx,sy)) {
					selection = i;
					break;
				}
			}
		}
		if(Engine::instance()->getButton("SelectionUp")) {
			if(!hold) {
				--selection;
				hold = true;
				//Engine::instance()->playSound(rollover, soundvec, soundvec);
			}
		} else if(Engine::instance()->getButton("SelectionDown")) {
			if(!hold) {
				++selection;
				hold = true;
				//Engine::instance()->playSound(rollover, soundvec, soundvec);
			}
		} else if(Engine::instance()->getButton("Accept")) {
			if(selection < 0) {
				selection = buttons.size()-1;
			} else if(selection >= buttons.size()) {
				selection = 0;
			}

			if(!hold) {
				buttons[selection].click();
				//Engine::instance()->playSound(click, soundvec, soundvec);
				hold = true;
			}
		} else {
			hold = false;
		}

		if(selection < 0) {
			selection = buttons.size()-1;
		} else if(selection >= buttons.size()) {
			selection = 0;
		}
	}
}

void MenuSystem::render() {
	renInfo temp;
	D3DXMATRIX mat;
	for(unsigned int i = 0; i < buttons.size(); ++i) {
		buttons[i].render(i == selection);
	}
	temp.type = screenSprite;
	temp.asset = &cursor;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&mat,_mX,_mY,0);
	temp.matrix = mat;
	Engine::instance()->addRender(temp);
}

void MenuSystem::addButton(Button in) {
	buttons.push_back(in);
}

void MenuSystem::addButton(void (*func)(),const char* label,frect rect,DWORD flags,D3DCOLOR color,D3DCOLOR hcolor) {
	Button temp;
	temp.setButton(func,label,rect,flags,color,hcolor);
	buttons.push_back(temp);
}
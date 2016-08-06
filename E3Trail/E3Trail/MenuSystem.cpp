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
}


void MenuSystem::clear() {
	while(buttons.size())
		buttons.pop_back();
}

void MenuSystem::update() {
	if(buttons.size() > 0) {
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
	for(unsigned int i = 0; i < buttons.size(); ++i) {
		buttons[i].render(i == selection);
	}
}

void MenuSystem::addButton(Button in) {
	buttons.push_back(in);
}

void MenuSystem::addButton(void (*func)(),const char* label,frect rect,DWORD flags,D3DCOLOR color,D3DCOLOR hcolor) {
	Button temp;
	temp.setButton(func,label,rect,flags,color,hcolor);
	buttons.push_back(temp);
}
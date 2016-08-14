#include "TrailEvent.h"

TrailEvent::TrailEvent() {
	eventText = "ERROR";
}

void TrailEvent::reset() {
	eventText = "ERROR";
	targs.clear();
}

void TrailEvent::setText(const char* tex) {
	eventText = tex;
}

void TrailEvent::addEventEffect(TEvent::eventTarg effect) {
	targs.push_back(effect);
}

void TrailEvent::addEventEffect(TEvent::target targ, int value) {
	TEvent::eventTarg temp;
	temp.targ = targ;
	temp.value = value;
	temp.failVal = 0;
	targs.push_back(temp);
}

void TrailEvent::addEventEffect(TEvent::target targ, int successValue, int failValue) {
	TEvent::eventTarg temp;
	temp.targ = targ;
	temp.value = successValue;
	temp.failVal = failValue;
	targs.push_back(temp);
}

int TrailEvent::numEffect() {
	return targs.size();
}

TEvent::eventTarg TrailEvent::getEffect(int id) {
	return targs[id];
}
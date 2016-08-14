#pragma once
#include "Engine.h"

namespace TEvent{
	enum target {
		ranParty,
		party0,
		party1,
		party2,
		party3,
		Hp,
		Res,
		randResource,
		credits,
		fuel,
		food,
		str,
		intel,
		agi
	};

	struct eventTarg {
		target targ;
		int value;
		int failVal;
	};
};

class TrailEvent {
private:
	std::string eventText;
	std::vector<TEvent::eventTarg> targs;
public:
	TrailEvent();
	void reset();
	void setText(const char* string);
	std::string getText() {return eventText;}
	void addEventEffect(TEvent::eventTarg effect);
	void addEventEffect(TEvent::target targ, int value);
	void addEventEffect(TEvent::target targ, int value, int failValue);
	int numEffect();
	TEvent::eventTarg getEffect(int id);
};
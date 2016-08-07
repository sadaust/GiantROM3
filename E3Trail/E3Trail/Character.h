#pragma once
#include <string>

class Character {
private:
	int hp;
	int resource;
	float resrate;
	std::string name;
	std::string resName;
public:
	void init(std::string a_name, std::string resourceName) {
		hp = 100;
		resource = 0;
		name = a_name;
		resName = resourceName;
	}
	int getHP() {return hp;}
	int getResource() {return resource;}
	std::string getResName() {return resName;}
	std::string getName() {return name;}
	void resIncer() {resource += resrate*hp;}
	void modHp(int mod) {hp+= mod;}
	void modResource(int mod) {resource+=mod;if(resource<0){resource = 0;}}
};
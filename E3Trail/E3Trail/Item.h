#pragma once
#include <string>
#include <vector>

enum Attribute {
	STRENGTH,
	HP,
	RESRATE
};


struct AttributeChange {
	int value;
	Attribute stat;
};



class Item {
private:
	std::string name;
	//std::string description; // maybe later
	std::vector <AttributeChange> attributes;
public:
	Item();
	~Item();
	Item(Item &a_item);
	int numAtt();
	std::string getName();
	AttributeChange getAttChange(int a_index);
	int getValue(int a_index);
	Attribute getAttribute(int a_index);
	void setName(std::string a_name);
	void addAttributeChange(AttributeChange a_attchange);
	void setValue(int a_index, int a_value);
	void setValue(Attribute a_att, int a_value);
	void addValue(int a_index, int a_value);
	void addValue(Attribute a_att, int a_value);




};





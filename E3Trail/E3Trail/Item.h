#pragma once
#include <string>
#include <vector>

enum Attribute {
	STRENGTH,
	AGILITY,
	INTELLIGENCE,
	HP,
	RESRATE,
	RESCLICK
};


struct AttributeChange {
	float value;
	Attribute stat;
};



class Item {
private:
	std::string name;
	//std::string description; // maybe later
	std::vector <AttributeChange> attributes;
	int cost;
public:
	Item();
	~Item();
	Item(const Item &a_item);
	void Clear();
	int numAtt() const;
	std::string getName() const;
	AttributeChange getAttChange(int a_index) const;
	float getValue(int a_index)const;
	float getValue(Attribute a_att)const;
	Attribute getAttribute(int a_index) const;
	void setName(std::string a_name);
	void addAttributeChange(AttributeChange a_attchange);
	void setValue(int a_index, float a_value);
	void setValue(Attribute a_att, float a_value);
	void addValue(int a_index, float a_value);
	void addValue(Attribute a_att, float a_value);

	int getCost() const;
	void setCost(int a_cost);



};





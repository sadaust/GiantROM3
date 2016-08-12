#pragma once
#include "Item.h"




Item::Item() {
	name = "Error";
	cost = 0;
}


Item::~Item() {
	attributes.clear();
}


Item::Item(const Item &a_item) {
	Clear();
	name = a_item.getName();
	for (int i = 0; i < a_item.numAtt(); ++i) {
		attributes.push_back(a_item.getAttChange(i));
	}
	cost = a_item.getCost();
}


int Item::numAtt() const {
	return attributes.size();
}


std::string Item::getName() const {
	return name;
}


void Item::Clear() {
	attributes.clear();
	name = "Empty";
}


AttributeChange Item::getAttChange(int a_index) const {
	return attributes[a_index];
}


float Item::getValue(int a_index) const {
	return attributes[a_index].value;
}


float Item::getValue(Attribute a_att) const {
	for (int i = 0; i < attributes.size(); ++i) {
		if (attributes[i].stat == a_att) {
			return attributes[i].value;
		}
	}

	return 0;

}


Attribute Item::getAttribute(int a_index) const {
	return attributes[a_index].stat;
}


void Item::setName(std::string a_name) {
	name = a_name;
}


void Item::addAttributeChange(AttributeChange a_attchange) {
	bool jobsdone = false;
	for (int i = 0; i < attributes.size() && !jobsdone; ++i) {
		if (attributes[i].stat == a_attchange.stat) {
			attributes[i].value += a_attchange.value;
			jobsdone = true;
		}

	}
	if (!jobsdone) {
		attributes.push_back(a_attchange);
		jobsdone = true;
	}
}


void Item::setValue(int a_index, float a_value) {
	attributes[a_index].value = a_value;
}


void Item::setValue(Attribute a_att, float a_value) {
	bool jobsdone = false;
	for (int i = 0; i < attributes.size() && !jobsdone; ++i) {
		if (attributes[i].stat == a_att) {
			attributes[i].value = a_value;
			jobsdone = true;
		}

	}
	if (!jobsdone) {
		AttributeChange temp;
		temp.stat = a_att;
		temp.value = a_value;
		attributes.push_back(temp);
		jobsdone = true;
	}
	
}


void Item::addValue(int a_index, float a_value) {
	attributes[a_index].value += a_value;
}


void Item::addValue(Attribute a_att, float a_value) {
	AttributeChange temp;
	temp.stat = a_att;
	temp.value = a_value;
	addAttributeChange(temp);
}


int Item::getCost() const {
	return cost;
}


void Item::setCost(int a_cost) {
	cost = a_cost;
}





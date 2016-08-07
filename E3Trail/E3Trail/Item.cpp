#pragma once
#include "Item.h"




Item::Item() {
	name = "ERROR";
	
}


Item::~Item() {
	attributes.clear();
}


Item::Item(Item &a_item) {
	name = a_item.getName();
	for (int i = 0; i < a_item.numAtt(); ++i) {
		attributes.push_back(a_item.getAttChange(i));
	}
}


int Item::numAtt() {
	return attributes.size();
}


std::string Item::getName() {
	return name;
}


AttributeChange Item::getAttChange(int a_index) {
	return attributes[a_index];
}


int Item::getValue(int a_index) {
	return attributes[a_index].value;
}


Attribute Item::getAttribute(int a_index) {
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


void Item::setValue(int a_index, int a_value) {
	attributes[a_index].value = a_value;
}


void Item::setValue(Attribute a_att, int a_value) {
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


void Item::addValue(int a_index, int a_value) {
	attributes[a_index].value += a_value;
}


void Item::addValue(Attribute a_att, int a_value) {
	AttributeChange temp;
	temp.stat = a_att;
	temp.value = a_value;
	addAttributeChange(temp);
}







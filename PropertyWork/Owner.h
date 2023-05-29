#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Property.h"
using namespace std;

class Owner : public Ijsonio, public Ixmlio {
public:
	string fullname;
	string inn;
	vector<Property*> properties;

	Owner(string fullname, string inn);
	Owner(string filename);
	void AddProperty(Property* p);
	void DeleteProperty(int index);
	double TaxSum();

	void fromJson(json obj) override;
	json toJson() override;
	
	void fromXML(xml_node xml) override;
	void toXML(xml_node& node) override;

	void TaxListJson(string filename);

	void ShowConsole();
};

class PropertyFactoryMethod {
public:
	static Property* getProperty(string key);
};
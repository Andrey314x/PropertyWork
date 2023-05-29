#include "Owner.h"

void Owner::fromJson(json obj) {
	this->fullname = obj["fullname"];
	this->inn = obj["inn"];

	vector<json> p = obj["properties"].get<vector<json>>();

	for (int i = 0; i < p.size(); i++) {
		string key = p[i].items().begin().key();
		Property* h = PropertyFactoryMethod::getProperty(key);
		h->fromJson(p[i][key]);
		this->properties.push_back(h);
	}
}
json Owner::toJson() {
	double sum = this->TaxSum();

	json obj;
	obj["fullname"] = this->fullname;
	obj["inn"] = this->inn;
	obj["sumtax"] = sum;

	json proptax;
	vector<json> taxs;

	for (int i = 0; i < this->properties.size(); i++) {
		taxs.push_back(properties[i]->toJson());
	}
	obj["taxs"] = taxs;

	return obj;
}



void Owner::fromXML(xml_node xml)
{
	this->fullname = xml.attribute("fullname").as_string();
	this->inn = xml.child_value("inn");

	for (auto node : xml.child("Properties").children("Property")) {
		string x = node.attribute("type").as_string();
		if (x == "Appartment") {
			Property* h = new Appartment(1, 1);
			h->fromXML(node);
			this->properties.push_back(h);
		}
		if (x == "Car") {
			Property* h = new Car(1, 1);
			h->fromXML(node);
			this->properties.push_back(h);
		}
		if (x == "CountryHouse") {
			Property* h = new CountryHouse(1, 1);
			h->fromXML(node);
			this->properties.push_back(h);
		}
	}
}
void Owner::toXML(xml_node& node)
{
	auto attr = node.append_attribute("fullname");
	attr.set_value(this->fullname.c_str());
	auto inn = node.append_child("inn");
	inn.text().set(this->inn.c_str());
	auto tax = node.append_child("Sumary_tax");
	tax.text().set(int(this->TaxSum() * 100) / 100);
	auto props = node.append_child("Properties");
	for (int i = 0; i < this->properties.size(); i++) {
		auto prop = props.append_child("Property");
		this->properties[i]->toXML(prop);
	}
}



Owner::Owner(string fullname, string inn) {
	this->fullname = fullname;
	this->inn = inn;
}
Owner::Owner(string filename) {
	ifstream fin(filename);
	json j_owner = json::parse(fin);
	fin.close();

	this->fullname = j_owner["fullname"];
	this->inn = j_owner["inn"];

	vector<json> p = j_owner["properties"].get<vector<json>>();

	for (int i = 0; i < p.size(); i++) {
		string key = p[i].items().begin().key();
		
		Property* h = PropertyFactoryMethod::getProperty(key);
		h->fromJson(p[i][key]);
		this->properties.push_back(h);
	}
}
void Owner::AddProperty(Property* p) {
	this->properties.push_back(p);
}
void Owner::DeleteProperty(int index) {
	if (index > 0 && index < properties.size())
		properties.erase(properties.begin() + index);
}
double Owner::TaxSum() {
	double sum = 0;
	for (auto i : properties) {
		sum += i->CalculateTax();
	}
	return sum;
}

void Owner::TaxListJson(string filename) {

	double sum = this->TaxSum();

	json obj;
	obj["fullname"] = this->fullname;
	obj["inn"] = this->inn;
	obj["sumtax"] = sum;

	json proptax;
	vector<json> taxs;
	
	for (int i = 0; i < this->properties.size(); i++) {
		taxs.push_back(properties[i]->toJson());
	}
	obj["taxs"] = taxs;

	ofstream os(filename);
	os << obj;
	os.close();
}

void Owner::ShowConsole() {
	cout << "Fullname: " << this->fullname << endl;
	cout << "INN: " << this->inn << endl << endl;
	cout << "properties: " << endl;
	for (int i = 0; i < this->properties.size(); i++) {
		properties[i]->ShowConsole();
		cout << endl;
	}
}


Property* PropertyFactoryMethod::getProperty(string key) {
	Property * h = new Car(1, 1);
	if(key == "Appartment") h = new Appartment(1, 1);
	if(key == "Car") h = new Car(1, 1);
	if(key == "CountryHouse") h = new CountryHouse(1, 1);

	return h;
}
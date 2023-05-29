#include "Property.h"
#include "TaxRates.h"

Property::Property(unsigned int worth)
{
	this->worth = worth;
}
Property::Property() {

}
double Property::CalculateIncomeTax() {
	return this->worth * 0.13;
}

void Appartment::ShowConsole() {
	cout << "Appartment: " << endl;
	cout << "worth: " << this->worth << endl;
	cout << "square: " << this->square << endl;
}
void Car::ShowConsole() {
	cout << "Car: " << endl;
	cout << "worth: " << this->worth << endl;
	cout << "horse power: " << this->horsepower << endl;
}
void CountryHouse::ShowConsole() {
	cout << "Country House: " << endl;
	cout << "worth:" << this->worth << endl;
	cout << "distance from city: " << this->distanceFromCity << endl;
}

void Appartment::SetFromConsole() {
	double c;
	cout << "Enter cost: ";
	cin >> c;
	this->worth = c;
	cout << "Enter square: ";
	cin >> c;
	this->square = c;
}
void Car::SetFromConsole() {
	double c;
	cout << "Enter cost: ";
	cin >> c;
	this->worth = c;
	cout << "Enter horsepower: ";
	cin >> c;
	this->horsepower = c;
}
void CountryHouse::SetFromConsole() {
	double c;
	cout << "Enter cost: ";
	cin >> c;
	this->worth = c;
	cout << "Enter distance from city: ";
	cin >> c;
	this->distanceFromCity = c;
}

void Appartment::toXML(xml_node& node) {
	auto attr = node.append_attribute("type");
	attr.set_value("Appartment");
	auto tax = node.append_child("tax");
	tax.text().set(int(this->CalculateTax() * 100) / 100);
	auto intax = node.append_child("income_tax");
	intax.text().set(int(this->CalculateIncomeTax() * 100) / 100);
}
void Appartment::fromXML(xml_node xml) {
	this->square = strtod(xml.child_value("square"), nullptr);
	this->worth = stoi(xml.child_value("worth"));
}
void Car::toXML(xml_node& node) {
	auto attr = node.append_attribute("type");
	attr.set_value("Car");
	auto tax = node.append_child("tax");
	tax.text().set(int(this->CalculateTax() * 100) / 100);
	auto intax = node.append_child("income_tax");
	intax.text().set(int(this->CalculateIncomeTax() * 100) / 100);
}
void Car::fromXML(xml_node xml) {
	this->horsepower = strtod(xml.child_value("horsepower"), nullptr);
	this->worth = stoi(xml.child_value("worth"));
}
void CountryHouse::toXML(xml_node& node) {
	auto attr = node.append_attribute("type");
	attr.set_value("CountryHouse");
	auto tax = node.append_child("tax");
	tax.text().set(int(this->CalculateTax() * 100) / 100);
	auto intax = node.append_child("income_tax");
	intax.text().set(int(this->CalculateIncomeTax() * 100) / 100);
}
void CountryHouse::fromXML(xml_node xml) {
	this->distanceFromCity = strtod(xml.child_value("distanceFromCity"), nullptr);
	this->worth = stoi(xml.child_value("worth"));
}


Appartment::Appartment(unsigned int worth, double square)
{
	
	this->worth = worth;
	this->square = square;
}
double Appartment::CalculateTax() {
	if (square <= TAX_RATES::LIMIT_APPARTMENT_SQUARE)
		return worth * TAX_RATES::APPARTMENT_TAX;
	else
		return worth * TAX_RATES::APPARTMENT_LUXURY_TAX;
}
void Appartment::fromJson(json obj){
	this->square = obj["square"];
	this->worth = obj["worth"];
}
json Appartment::toJson() {
	json obj;
	obj["tax"] = this->CalculateTax();
	json h;
	h["Appartment"] = obj;
	return h;
};

Car::Car(unsigned int worth, double horsepower)
{
	this->worth = worth;
	this->horsepower = horsepower;
}
double Car::CalculateTax() {
	if (horsepower < TAX_RATES::LOW_HORSEPOWER)
		return worth * TAX_RATES::CAR_TAX;
	else
		if (horsepower > TAX_RATES::HIGH_HORSEPOWER)
			return worth * TAX_RATES::CAR_LUXURY_TAX;
		else
			return worth * TAX_RATES::CAR_TRUCK_TAX;
}
void Car::fromJson(json obj) {
	this->horsepower = obj["horsepower"];
	this->worth = obj["worth"];
}
json Car::toJson() {
	json obj;
	obj["tax"] = this->CalculateTax();
	json h;
	h["Car"] = obj;
	return h;
};

CountryHouse::CountryHouse(unsigned int worth, unsigned int distance)
{
	this->worth = worth;
	this->distanceFromCity = distance;
}
double CountryHouse::CalculateTax() {
	if (distanceFromCity <= TAX_RATES::LIMIT_DISTANCE_FROM_CITY)
		return worth * TAX_RATES::APPARTMENT_TAX;
	else
		return worth * TAX_RATES::APPARTMENT_LUXURY_TAX;
}
void CountryHouse::fromJson(json obj) {
	this->distanceFromCity = obj["distanceFromCity"];
	this->worth = obj["worth"];
}
json CountryHouse::toJson() {
	json obj;
	obj["tax"] = this->CalculateTax();
	json h;
	h["CountryHouse"] = obj;
	return h;
};

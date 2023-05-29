#pragma once
#include "Ijsonio.h"
#include "Ixmlio.h"
#include <iostream>

using namespace std;

class Property : public Ijsonio, public Ixmlio
{
public:
	unsigned int worth;
	Property(unsigned int worth);
	Property();
	virtual double CalculateTax() = 0;
	double CalculateIncomeTax();
	virtual void ShowConsole() = 0;
	virtual void SetFromConsole() = 0;
};

class Appartment : public Property {
private:
	double square;
public:
	Appartment(unsigned int worth, double square);
	double CalculateTax() override;

	void fromJson(json obj) override;
	json toJson() override;

	void fromXML(xml_node xml) override;
	void toXML(xml_node& node) override;

	void ShowConsole() override;
	void SetFromConsole() override;
};

class Car : public Property {
private:
	double horsepower;
public:
	Car(unsigned int worth, double horsepower);
	double CalculateTax() override;

	void fromJson(json obj) override;
	json toJson() override;

	void fromXML(xml_node xml) override;
	void toXML(xml_node& node) override;

	void ShowConsole() override;
	void SetFromConsole() override;
};

class CountryHouse : public Property {
	unsigned int distanceFromCity;
public:
	CountryHouse(unsigned int worth, unsigned int distance);
	double CalculateTax() override;

	void fromJson(json obj) override;
	json toJson() override;

	void fromXML(xml_node xml) override;
	void toXML(xml_node& node) override;

	void ShowConsole() override;
	void SetFromConsole() override;
};


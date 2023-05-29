#include "TaxService.h"

TaxService::TaxService() {

}

TaxService::TaxService(string filename) {
	ifstream fin(filename);
	json j_owners = json::parse(fin);
	fin.close();

	vector<json> p = j_owners["owners"].get<vector<json>>();

	for (int i = 0; i < p.size(); i++) {
		Owner o("", "");
		o.fromJson(p[i]);
		this->owners.push_back(o);
	}
}

void TaxService::fromJson(json obj) {
	vector<json> p = obj["owners"].get<vector<json>>();
	for (int i = 0; i < p.size(); i++) {
		Owner o("", "");
		o.fromJson(p[i]);
		this->owners.push_back(o);
	}
}
json TaxService::toJson() {
	json obj;

	json ownersList;
	vector<json> own;

	for (int i = 0; i < this->owners.size(); i++) {
		own.push_back(owners[i].toJson());
	}
	obj["owners"] = own;

	return obj;
}

void TaxService::fromXML(xml_node xml)
{
	for (auto node : xml.children("Owner")) {
		Owner o("", "");
		o.fromXML(node);
		this->owners.push_back(o);
	}
}
void TaxService::toXML(xml_node& node)
{
	auto sumTax = node.append_child("summary_taxes");
	sumTax.text().set(int(this->SumTaxs() * 100) / 100);
	for (int i = 0; i < this->owners.size(); i++) {
		auto own = node.append_child("Owner");
		this->owners[i].toXML(own);
	}
}

void TaxService::JsonTaxList(string filename) {
	json obj;
	
	json ownersList;
	vector<json> own;

	for (int i = 0; i < this->owners.size(); i++) {
		own.push_back(owners[i].toJson());
	}
	obj["owners"] = own;

	ofstream os(filename);
	os << obj;
	os.close();
}

double TaxService::AverageTaxs() {
	double sum = 0;
	for (Owner i : this->owners) {
		sum += i.TaxSum();
	}
	return sum / this->owners.size();
}
double TaxService::SumTaxs() {
	double sum = 0;
	for (Owner i : this->owners) {
		sum += i.TaxSum();
	}
	return sum;
}
Owner TaxService::MinTaxs() {
	double min = 100000;
	Owner o("", "");
	for (Owner i : this->owners) {
		if (i.TaxSum() < min) {
			min = i.TaxSum();
			o = i;
		}
	}
	return o;
}
Owner TaxService::MaxTaxs() {
	double max = 0;
	Owner o("", "");
	for (Owner i : this->owners) {
		if (i.TaxSum() > max) {
			max = i.TaxSum();
			o = i;
		}
	}
	return o;
}
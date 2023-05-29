#pragma once
#include "Ijsonio.h"
#include "Owner.h"

class TaxService : public Ijsonio, public Ixmlio {
public:
	vector<Owner> owners;
	TaxService(string filename);
	TaxService();

	void fromJson(json json) override;
	json toJson() override;

	void fromXML(xml_node xml) override;
	void toXML(xml_node& node) override;

	void JsonTaxList(string filename);
	double AverageTaxs();
	double SumTaxs();
	Owner MinTaxs();
	Owner MaxTaxs();
};
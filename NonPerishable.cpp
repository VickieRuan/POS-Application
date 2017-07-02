#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "NonPerishable.h" 
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;
namespace ict {
	bool NonPerishable::ok() const {
		return m_err.isClear();

	}
	void NonPerishable::error(const char* message) {
		m_err.message(message);
	}
	char NonPerishable::signature()const {
		char ch = 'N';
		return ch;
	}
	std::fstream& NonPerishable::save(std::fstream& file)const {
		file << endl;
		file << signature() << ',' << sku() << ',' << name() << ',' << price() << ',' << taxed() << ',' << quantity();
		return file;
	}
	std::fstream& NonPerishable::load(std::fstream& file) {
		bool taxedTemp = 0;
		char skuTemp[50];
		char nameTemp[50];
		int qtyTemp = 0;
		double priceTemp;
		file.ignore(1);
		file.getline(skuTemp, 50, ',');
		sku(skuTemp);
		file.getline(nameTemp, 50, ',');
		name(nameTemp);
		file >> priceTemp;
		price(priceTemp);
		file.ignore(1);
		file >> taxedTemp;
		taxed(taxedTemp);
		file.ignore(1);
		file >> qtyTemp;
		quantity(qtyTemp);
		file.ignore();

		return file;
	}
	std::ostream& NonPerishable::write(std::ostream& ostr, bool linear)const {
		if (!ok()) {
			ostr << (const char*)m_err;
		}
		else {
			if (linear) {
				ostr << left << setw(MAX_SKU_LEN) << sku() << '|';
				ostr << left << setw(20) << name() << '|';
				ostr << right << setw(7) << fixed << setprecision(2) << price() << '|';
				if (taxed()) {
					ostr << " T" << signature() << '|';
				}
				else {
					ostr << "  " << signature() << '|';
				}
				ostr << right << setw(4) << quantity() << '|';
				ostr << right << setw(9) << cost() * quantity() << '|';
			}
			else {

				ostr << "Name:" << endl;
				ostr << name() << endl;
				ostr << "Sku: " << sku() << endl;
				ostr << "Price: " << price() << endl;
				if (taxed()) {
					ostr << "Price after tax: " << cost() << endl;
				}
				else {
					ostr << "Price after tax: N/A" << endl;
				}
				ostr << "Quantity: " << quantity() << endl;
				ostr << "Total Cost: " << cost() * quantity() << endl;
			}
		}
		return ostr;
	}
	std::istream& NonPerishable::read(std::istream& is) {
		double dTemp;
		int iTemp;
		char stringTemp[100];
		char charTemp;

		if (!is.fail()) {
			m_err.clear();
			cout << "Item Entry:" << endl;
			cout << "Sku: ";
			is >> stringTemp;
			sku(stringTemp);

			cout << "Name:" << endl;
			is >> stringTemp;
			name(stringTemp);

			cout << "Price: ";
			is >> dTemp;
			if (is.fail()) {
				error("Invalid Price Entry");
			}
			else {
				price(dTemp);
			}

			if (m_err.isClear()) {
				cout << "Taxed: ";
				is >> charTemp;
				if (charTemp == 'y'){
					taxed(true);
				}else if(charTemp == 'n'){
					taxed(false);
				}
				else {
					error("Invalid Taxed Entry, (y)es or (n)o");
					is.setstate(ios::failbit);
				}
			}

			if (m_err.isClear()) {
				cout << "Quantity: ";
				is >> iTemp;
				if (is.fail()) {
					error("Invalid Quantity Entry");
				}
				else {
					quantity(iTemp);
				}
			}
		}
		return is;
	}

}
#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include "Perishable.h"

using namespace std;

namespace ict {

	char Perishable::signature()const {
		char ch = 'P';
		return ch;
	}
	Perishable::Perishable() {
		m_expiry.dateOnly(true);
	}
	std::fstream& Perishable::save(std::fstream& file)const {
		NonPerishable::save(file);
		file << ",";
		m_expiry.write(file);
		return file;
	}
	std::fstream& Perishable::load(std::fstream& file) {

		NonPerishable::load(file);
		//  file.ignore();
		m_expiry.read(file);

		return file;
	}
	std::ostream& Perishable::write(std::ostream& ostr, bool linear)const {
		NonPerishable::write(ostr, linear);
		if (ok() && !linear) {
			ostr << "Expiry date: " << m_expiry << endl;
		}
		return ostr;
	}
	std::istream& Perishable::read(std::istream& is) {

		cout << "Perishable ";
		NonPerishable::read(is);
		if (NonPerishable::ok()) {
			cout << "Expiry date (YYYY/MM/DD): ";
			is >> m_expiry;
			if (m_expiry.errCode() != NO_ERROR) {
				if (m_expiry.errCode() == CIN_FAILED) {
					error("Invalid Date Entry");
				}
				else if (m_expiry.errCode() == YEAR_ERROR) {
					error("Invalid Year in Date Entry");
				}
				else if (m_expiry.errCode() == MON_ERROR) {
					error("Invalid Month in Date Entry");
				}
				else if (m_expiry.errCode() == DAY_ERROR) {
					error("Invalid Day in Date Entry");
				}
				is.setstate(ios::failbit);
			}

		}

		return is;
	}

}
#include "Perishable.h"

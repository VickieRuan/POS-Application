#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"

namespace ict {
	void Date::set() {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		m_day = lt.tm_mday;
		m_mon = lt.tm_mon + 1;
		m_year = lt.tm_year + 1900;
		if (dateOnly()) {
			m_hour = m_min = 0;
		}
		else {
			m_hour = lt.tm_hour;
			m_min = lt.tm_min;
		}
	}

	int Date::value()const {
		return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
	}

	int Date::mdays()const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
		mon--;
		return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
	}

	void Date::errCode(int errorCode) {
		m_readErrorCode = errorCode;
	}
	void Date::set(int year, int mon, int day, int hour, int min) {
		m_year = year;
		m_mon = mon;
		m_day = day;
		m_hour = hour;
		m_min = min;
		m_readErrorCode = NO_ERROR;
	}
	Date::Date() {
		m_dateOnly = false;
		set();
	}
	Date::Date(int yr, int mon, int day) {
		m_dateOnly = true;
		m_year = yr;
		m_mon = mon;
		m_day = day;
		m_hour = 0;
		m_min = 0;
		m_readErrorCode = NO_ERROR;
	}
	Date::Date(int yr, int mon, int day, int hr, int min) {
		m_dateOnly = false;
		m_year = yr;
		m_mon = mon;
		m_day = day;
		m_hour = hr;
		m_min = min;
		m_readErrorCode = NO_ERROR;

	}
	//These operators return the result of comparing the left operand to the right operand
	bool Date::operator==(const Date& D)const {
		return this->value() == D.value();
	}
	bool Date::operator!=(const Date& D)const {
		return this->value() != D.value();
	}
	bool Date::operator<(const Date& D)const {
		return this->value() < D.value();
	}
	bool Date::operator>(const Date& D)const {
		return this->value() > D.value();
	}
	bool Date::operator<=(const Date& D)const {
		return this->value() <= D.value();
	}
	bool Date::operator>=(const Date& D)const {
		return this->value() >= D.value();
	}
	int Date::errCode()const {
		return m_readErrorCode;
	}
	bool Date::bad()const {
		return m_readErrorCode != 0;
	}
	bool Date::dateOnly()const {
		return m_dateOnly;
	}
	void Date::dateOnly(bool value) {
		m_dateOnly = value;
		if (value == 1) {
			m_hour = 0;
			m_min = 0;
		}
	}

	std::istream& Date::read(std::istream& is) {
		errCode(NO_ERROR);
		is >> m_year;
		if (is.get() != '/') {
			errCode(CIN_FAILED);
		}
		is >> m_mon;
		if (is.get() != '/') {
			errCode(CIN_FAILED);
		}
		is >> m_day;
		if (!m_dateOnly) {
			if (is.get() != ',') {
				errCode(CIN_FAILED);
			}
			if (is.get() != ' ') {
				errCode(CIN_FAILED);
			}
			is >> m_hour;
			if (is.get() != ':') {
				errCode(CIN_FAILED);
			}
			is >> m_min;
		}
		if (is.fail() || m_readErrorCode) {
			errCode(CIN_FAILED);
		}
		else {
			if (m_year < MIN_YEAR || m_year > MAX_YEAR) {
				m_readErrorCode = YEAR_ERROR;
			}
			else if (m_mon < 1 || m_mon > 12) {
				m_readErrorCode = MON_ERROR;
			}
			else if (m_day < 1 || m_day > mdays()) {
				m_readErrorCode = DAY_ERROR;
			}
			else if (m_hour < 0 || m_hour > 23) {
				m_readErrorCode = HOUR_ERROR;
			}
			else if (m_min < 0 || m_min > 59) {
				m_readErrorCode = MIN_ERROR;
			}
			else {
				m_readErrorCode = NO_ERROR;
			}
		}
		return is;
	}

	std::ostream& Date::write(std::ostream& ostr)const {
		ostr << m_year << "/";
		if (m_mon < 10) {
			ostr << "0";
		}
		ostr << m_mon << "/";
		if (m_day < 10) {
			ostr << "0";
		}
		ostr << m_day;
		if (!m_dateOnly) {
			ostr << ", ";
			if (m_hour < 10) {
				ostr << "0";
			}
			ostr << m_hour << ":";
			if (m_min < 10) {
				ostr << "0";
			}
			ostr << m_min;
		}
		return ostr;
	}
	//operator<< and >> overload for cout and cin
	std::istream& operator>>(std::istream& is, Date& A) {
		return A.read(is);
	}
	std::ostream& operator<< (std::ostream& ostr, const Date& A) {
		return A.write(ostr);
	}
}
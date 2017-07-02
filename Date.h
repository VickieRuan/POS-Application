#ifndef ICT_DATE_H_
#define ICT_DATE_H_

#include <iostream>
// ict namespace
namespace ict {
	// Date defined Error values
	const int NO_ERROR = 0;
	const int CIN_FAILED = 1;
	const int YEAR_ERROR = 2;
	const int MON_ERROR = 3;
	const int DAY_ERROR = 4;
	const int HOUR_ERROR = 5;
	const int MIN_ERROR = 6;

	class Date {
	private:
		// member variables
		int m_year;
		int m_mon;
		int m_day;
		int m_hour;
		int m_min;
		int m_readErrorCode;
		bool m_dateOnly;

		// private methods
		int value()const;
		void errCode(int errorCode);

	public:
		// constructors
		Date();
		Date(int yr, int mon, int day);
		Date(int yr, int mon, int day, int hr, int min = 0);

		void set();
		void set(int year, int mon, int day, int hour, int min);
		// operator ovrloads
		bool operator==(const Date& D)const;
		bool operator!=(const Date& D)const;
		bool operator<(const Date& D)const;
		bool operator>(const Date& D)const;
		bool operator<=(const Date& D)const;
		bool operator>=(const Date& D)const;

		// methods
		int mdays()const;
		//getter
		int errCode()const;
		bool bad()const;
		bool dateOnly()const;
		void dateOnly(bool value);

		// istream  and ostream read and write methods
		std::istream& read(std::istream& is = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;

	};
	// operator<< and >> overload prototypes for cout and cin
	std::istream& operator >> (std::istream& is, Date& A);
	std::ostream& operator<<(std::ostream& ostr, const Date& A);

}

#endif
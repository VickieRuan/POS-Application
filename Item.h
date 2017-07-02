#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include "PosIO.h"
#include "POS.h"

namespace ict {
	// class Item
	class Item : public PosIO {
		char m_sku[MAX_SKU_LEN + 1]; //null-terminated character array
		char* m_name; //character pointer points to a dynamically allocated string 
		double m_price;
		bool m_taxed;
		int m_quantity;
	public:
		Item();
		Item(const char* s, const char* n, double p, bool t = true);
		virtual ~Item();
		//copy constructor and operator =
		Item(const Item& src);
		Item& operator=(const Item& src);
		void sku(const char* sku);
		void price(double price);
		void name(const char* name);
		void taxed(bool tax);
		void quantity(int qty);
		const char* sku()const;
		double price()const;
		const char* name()const;
		bool taxed()const;
		int quantity()const;
		double cost()const;
		bool isEmpty()const;
		bool operator==(const char* str);
		int operator+=(int num);
		int operator-=(int num);


		virtual std::fstream& save(std::fstream& file)const = 0;
		virtual std::fstream& load(std::fstream& file) = 0;
		virtual std::ostream& write(std::ostream& ostr, bool linear)const = 0;
		virtual std::istream& read(std::istream& is) = 0;
	};
	// end class Item

	// Non-member operator overload, operator += 
	double operator+=(double& d, const Item& I);
	// Non-member IO operator overloads, operator << and operator >>
	std::ostream& operator<<(std::ostream& os, const Item& I);
	std::istream& operator >> (std::istream& is, Item& I);
}

#endif
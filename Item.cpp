#define _CRT_SECURE_NO_WARNINGS  
// Lib includes
#include <iostream>
#include <cstring>

// inlcude Item and POS header files
#include "Item.h"
#include "POS.h"

using namespace std;

namespace ict {
	// class Item implementaion
	Item::Item() {
		m_sku[0] = '\0';
		m_name = nullptr;
		m_price = 0;
		m_taxed = false;
		m_quantity = 0;
	}
	Item::Item(const char* s, const char* n, double p, bool t) {
		sku(s);
		name(n);
		price(p);
		taxed(t);
		quantity(0);
	}

	Item::~Item() {
		delete[] m_name;
	}
	Item::Item(const Item& src) {
		//shallow copies
		sku(src.sku());
		name(src.name());
		price(src.price());
		taxed(src.taxed());
		quantity(src.quantity());
	}

	Item& Item::operator=(const Item& src) {
		if (this != &src) {
			sku(src.sku());
			price(src.price());
			taxed(src.taxed());
			quantity(src.quantity());
			//deallocate previously allocated dynamic memory         
			delete[] m_name;
			name(src.name());
		}
		return *this;
	}
	//setter
	void Item::sku(const char* sku) {
		strncpy(m_sku, sku, MAX_SKU_LEN);
		m_sku[MAX_SKU_LEN] = '\0';
	}
	void Item::price(double price) {
		m_price = price;
	}
	void Item::name(const char* name) {
		m_name = new char[strlen(name) + 1];
		if (name != nullptr) {
			strncpy(m_name, name, strlen(name) + 1);
			m_name[strlen(name) + 1] = '\0';
		}
		else {
			m_name = nullptr;
		}
	}

	void Item::taxed(bool tax) {
		m_taxed = tax;
	}
	void Item::quantity(int qty) {
		m_quantity = qty;
	}
	//getter
	const char* Item::sku()const {
		return m_sku;
	}
	double Item::price()const {
		return m_price;
	}
	const char* Item::name()const {
		return m_name;
	}
	bool Item::taxed()const {
		return m_taxed;
	}
	int Item::quantity()const {
		return m_quantity;
	}
	double Item::cost()const {
		double cost;
		if (taxed()) {
			cost = price() * (1 + TAX);
		}
		else {
			cost = price();
		}
		return cost;
	}

	bool Item::isEmpty()const {
		return m_name == nullptr;
	}
	bool Item::operator==(const char* sku) {
		return !strcmp(m_sku, sku);
	}
	int Item::operator+=(int num) {
		return m_quantity += num;
	}
	int Item::operator-=(int num) {
		return m_quantity -= num;
	}
	double operator+=(double& d, const Item& I) {
		d = d + I.cost() * I.quantity();
		return d;
	}
	std::ostream& operator<<(std::ostream& os, const Item& I) {
		return I.write(os, true);
	}
	std::istream& operator >> (std::istream& is, Item& I) {
		return I.read(is);
	}

}


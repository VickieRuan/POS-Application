#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__

#include "NonPerishable.h"
#include "Date.h"


namespace ict {

	class Perishable : public NonPerishable {
	private:
		Date m_expiry;
	protected:
		char signature()const;

	public:
		Perishable();
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& ostr, bool linear)const;
		std::istream& read(std::istream& is);

	};
}

#endif
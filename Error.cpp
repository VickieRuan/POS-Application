#define _CRT_SECURE_NO_WARNINGS 
#include <cstring>
#include "Error.h"

namespace ict {
	Error::Error() {
		m_message = nullptr;
	}
	Error::Error(const char* errorMessage) {
		m_message = nullptr;
		message(errorMessage);
	}
	Error::~Error() {
		delete[] m_message;
	}
	void Error::operator=(const char* errorMessage) {
		delete[] m_message;
		m_message = new char[strlen(errorMessage) + 1];
		clear();
		message(errorMessage);
	}

	void Error::clear() {
		delete[] m_message;
		m_message = nullptr;
	}
	bool Error::isClear()const {
		return m_message == nullptr;
	}
	void Error::message(const char* value) {
		delete[] m_message;
		m_message = new char[strlen(value) + 1];
		strcpy(m_message, value);
	}
	Error::operator const char*() const {
		return m_message;
	}
	Error::operator bool()const {
		return m_message == nullptr;
	}
	std::ostream& operator<<(std::ostream& ostr, const Error& A) {
		return (A.isClear()) ? ostr : ostr << (const char*)A;
	}

}
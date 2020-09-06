// Name:
// Seneca Student ID:
// Seneca email:
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include<iostream>
#include<string>

namespace std {
	class Utilities {
		size_t m_widthField = 1;
		static char m_delimiter;
	public:
		void setFieldWidth(size_t width) { m_widthField = width; }
		size_t getFieldWidth() const { return m_widthField; }
		const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(const char del) { m_delimiter = del; }
		const char getDelimiter() const { return m_delimiter; }
		void trim(std::string& str);
	};
}

#endif // !UTILITIES_H

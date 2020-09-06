// Name: 
// Seneca Student ID:
// Seneca email:
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include"Utilities.h"

namespace std {
	char Utilities::m_delimiter = ' ';
	void Utilities::trim(std::string& str)
	{
		size_t i;

		for (i = 0; i < str.length() && str[i] == ' '; i++) {
			str = str.substr(i + 1);
		}

		for (i = str.length(); i > 0 && str[i] == ' '; i--) {
			str = str.substr(0, i);
		}
	}

	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		size_t index = 0;
		std::string s_tmp = "";

		if (next_pos != 0)
			next_pos++;

		// from the next_pos
		s_tmp = str.substr(next_pos);

		// find the next del, then extracts the token *the last token doesn't have delimiter
		try {
			index = s_tmp.find(m_delimiter);
			s_tmp = s_tmp.substr(0, index);
		}
		catch (...) {
			;
		}

		// If successful, it returns the extracted token found and sets more to true; false otherwise.
		// This function reports an exception if there are two delimiters with no token between them.
		if (s_tmp == "") {
			more = false;
			throw "no token between\n";
		}
		else {
			more = true;
			trim(s_tmp);
			// updates the current object's m_widthField data member 
			// if its current value is less than the size of the token extracted. 
			if (s_tmp.length() > m_widthField) {
				m_widthField = s_tmp.length();
			}
			return s_tmp;
		}
	}
}
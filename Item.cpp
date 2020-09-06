// Name:
// Seneca Student ID:
// Seneca email:
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include"Item.h"
#include"Utilities.h"
#include<iomanip>

namespace std {

	size_t Item::m_widthField = 0;

	Item::Item(const std::string& record)
	{
		std::string tmp_record = record;
		size_t pos = 0;
		size_t m_pos = 0;
		bool success = true;
		Utilities tmp_util;

		// extract name
		m_name = tmp_util.extractToken(record, pos, success);

		// find the next position, then make a substring to find the next position
		pos = tmp_record.find(tmp_util.getDelimiter());
		tmp_record = tmp_record.substr(pos + 1);

		// extract serial num
		m_serialNumber = std::stoi(tmp_util.extractToken(record, pos, success));


		// find the next position, then make a substring to find the next position
		m_pos = tmp_record.find(tmp_util.getDelimiter());
		pos += m_pos;
		tmp_record = tmp_record.substr(m_pos + 1);

		// extract QTY
		m_quantity = std::stoi(tmp_util.extractToken(record, pos, success));


		// find the next position, then make a substring to find the next position
		m_pos = tmp_record.find(tmp_util.getDelimiter());
		pos += m_pos;
		tmp_record = tmp_record.substr(m_pos + 1);

		// extract description

		m_description = tmp_util.extractToken(record, pos, success);


		if (m_widthField < tmp_util.getFieldWidth())
			m_widthField = tmp_util.getFieldWidth();
	}

	void Item::display(std::ostream& os, bool full) const
	{
		if (full) {
			os << std::left << std::setw(m_widthField) << m_name;
			os << '[' << std::setw(6) << std::setfill('0') << m_serialNumber << "] ";
			os << std::setfill(' ') << "Quantity: " << std::left << std::setw(m_widthField) << m_quantity;
			os << "Description: " << m_description;
		}
		else {
			os << std::setw(m_widthField) << std::left << m_name;
			os << '[' << m_serialNumber << ']';
		}

		os << std::endl;
	}
}
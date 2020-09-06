// Name:
// Seneca Student ID:
// Seneca email:
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include<iostream>
#include<string>

namespace std {
	class Item {
		std::string m_name = "";
		std::string m_description = "";
		size_t m_serialNumber = 0;
		size_t m_quantity = 0;
		static size_t m_widthField;
	public:
		Item(const std::string& record);
		const std::string& getName() const { return m_name; }
		const unsigned int getSerialNumber() { return m_serialNumber++; }
		const unsigned int getQuantity() { return m_quantity; }
		void updateQuantity() { if (m_quantity > 0) m_quantity--; }
		void display(std::ostream& os, bool full) const;
		// for Task moudle
		Item& getItem() { return *this; }
	};
}
#endif // !ITEM_H

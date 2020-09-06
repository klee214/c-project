#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include<iostream>
#include<string>
#include"Utilities.h"
#include"Item.h"

namespace std {
	struct ItemInfo
	{
		std::string m_itemName;
		unsigned int m_serialNumber = 0;
		bool m_fillState = false;

		ItemInfo(std::string src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		unsigned int m_cntItem = 0;
		ItemInfo** m_lstItem = nullptr;
		static size_t m_widthField;
	public:
		CustomerOrder() {};
		~CustomerOrder() { delete[] m_lstItem; }
		CustomerOrder(std::string& record);
		CustomerOrder(const CustomerOrder& c) { }
		CustomerOrder& operator=(const CustomerOrder& c) = delete;
		CustomerOrder(CustomerOrder&& c) noexcept { *this = std::move(c); }
		CustomerOrder& operator=(CustomerOrder&& c)noexcept
		{
			m_name = c.m_name;
			m_product = c.m_product;
			m_cntItem = c.m_cntItem;
			m_lstItem = c.m_lstItem;
			c.m_lstItem = nullptr;

			return *this;
		}
		bool getItemFillState(std::string) const;
		bool getOrderFillState() const;
		void fillItem(Item& item, std::ostream&);
		void display(std::ostream&) const;
	};
}
#endif // !SDDS_CUSTOMERORDER_H

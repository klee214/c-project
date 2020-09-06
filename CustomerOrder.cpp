#include<iomanip>
#include"CustomerOrder.h"


namespace std {
	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder(std::string& record)
	{
		std::string tmp_record = record;
		std::string tmp_string;
		Utilities tmp_util;
		size_t pos = 0;
		size_t m_pos = 1;
		size_t listCnt = 0;
		bool success = true;

		// extract name
		m_name = tmp_util.extractToken(record, pos, success);

		// find the next position, then make a substring to find the next position
		pos = tmp_record.find(tmp_util.getDelimiter());
		tmp_record = tmp_record.substr(pos + 1);

		// extract serial num
		m_product = tmp_util.extractToken(record, pos, success);

		m_pos = tmp_record.find(tmp_util.getDelimiter());

		while (m_pos > 0) {
			ItemInfo* tmp_item;

			m_pos = tmp_record.find(tmp_util.getDelimiter()) + 1;

			if (!m_pos > 0)
				break;

			tmp_record = tmp_record.substr(m_pos);

			pos += m_pos - 1;
			try {
				tmp_string = tmp_util.extractToken(record, pos, success);
			}
			catch (...) {
				;
			}

			tmp_item = new ItemInfo(tmp_string);
			++listCnt;

			if (listCnt == 1) {
				m_lstItem = new ItemInfo*;
				m_lstItem[0] = tmp_item;
			}
			else {
				ItemInfo** tmpItem = m_lstItem;

				m_lstItem = nullptr;
				delete m_lstItem;

				m_lstItem = new ItemInfo * [listCnt];
				for (size_t i = 0; i < listCnt - 1; ++i) {
					m_lstItem[i] = tmpItem[i];
				}
				m_lstItem[listCnt - 1] = tmp_item;
			}
		}

		if (m_widthField < tmp_util.getFieldWidth())
			m_widthField = tmp_util.getFieldWidth();

		m_cntItem = listCnt;
	}

	bool CustomerOrder::getItemFillState(std::string cmp) const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == cmp) {
				return m_lstItem[i]->m_fillState;
			}
		}
		return true;
	}

	bool CustomerOrder::getOrderFillState() const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_fillState)
				return false;
		}
		return true;
	}

	void CustomerOrder::fillItem(Item& item, std::ostream&)
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == item.getName()) {
				if (item.getQuantity() > 0) {
					std::cout << "Filled " << m_name << ", " << m_product << '[' << item.getName() << ']' << std::endl;
					m_lstItem[i]->m_itemName = item.getName();
					m_lstItem[i]->m_serialNumber = item.getSerialNumber();
					m_lstItem[i]->m_fillState = true;
					item.updateQuantity();

				}
				else {
					std::cout << "Unable to fill " << m_name << std::endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			os << '[' << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ');
			os << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName << " - ";
			if (m_lstItem[i]->m_fillState) {
				os << "FILLED" << std::endl;
			}
			else {
				os << "MISSING" << std::endl;
			}
		}
	}
}
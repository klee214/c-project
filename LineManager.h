#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include"Task.h"
#include"CustomerOrder.h"


namespace std {
	class LineManager {
		std::vector<Task*> AssemblyLine;
		std::deque<CustomerOrder> ToBeFilled;
		std::deque<CustomerOrder> Completed;
		unsigned int m_cntCustomerOrder = 0;
		size_t m_first = 0;
		size_t m_last = 0;
	public:
		LineManager(const std::string& filename, std::vector<Task*> task, std::vector<CustomerOrder>& order);
		bool run(std::ostream&);
		void displayCompleted(std::ostream& os) const;
		void validateTasks() const;
	};
}

#endif // !SDDS_LINEMANAGER_H

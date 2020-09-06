#ifndef SDDS_TASK_H
#define SDDS_TASK_H

#include<iostream>
#include<string>
#include<deque>
#include"Item.h"
#include"CustomerOrder.h"

namespace std {
	class Task : public Item{
		std::deque<CustomerOrder> m_orders;
		Task* m_pNextTask = nullptr; // a pointer to the next task on the assembly line

	public:
		Task(const std::string& record) : Item(record) { m_pNextTask = nullptr; }
		Task(const Task& task) = delete;
		Task& operator=(const Task& task) = delete;
		Task(Task&& task) = delete;
		Task& operator=(Task&& task) = delete;
		void runProcess(std::ostream&);
		bool moveTask();
		void setNextTask(Task& task) { m_pNextTask = &task; }
		bool getCompleted(CustomerOrder&);
		void validate(std::ostream&);
		Task& operator+=(CustomerOrder&& order) { m_orders.push_front(std::move(order)); return *this; }
	};
}
#endif // !SDDS_TASK_H

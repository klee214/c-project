#include"Task.h"

namespace std {


	//verify the fill status of the last CustomerOrder 
	//and fill it if the order contains the Item specified by the current Task
	void Task::runProcess(std::ostream& os)
	{
		if (m_orders.size() > 0)
		{
			m_orders.back().fillItem(Item::getItem(), os);
		}
	}

	//moves the last CustomerOrder in the queue to the next task on the assembly line 
	//if the orders fill state for the current Item is true.
	bool Task::moveTask()
	{
		if (m_orders.size() != 0) {

			if (m_orders.back().getItemFillState(Item::getName()))
			{
				//move to the next task on the assembly line
				//assume pNextTask is not nullptr
				if (m_pNextTask != nullptr)
				{
					*m_pNextTask += std::move(m_orders.back());
					m_orders.pop_back();
				}
					return true;
			}
		}

		return false;
	}

	//Removes the last CustomerOrder from the queue, places it in the parameter and returns true
	bool Task::getCompleted(CustomerOrder& order)
	{
		if (!m_orders.size() > 0 || !m_orders.back().getOrderFillState())
			return false;

		order = std::move(m_orders.back());
		m_orders.pop_back();

		return true;
	}

	void Task::validate(std::ostream& os)
	{
		os << Item::getName() << " --> ";

		if (m_pNextTask == nullptr)
			os << "END OF LINE" << std::endl;
		else
			os << m_pNextTask->Item::getName() << std::endl;
	}
}
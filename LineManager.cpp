#include<fstream>
#include"LineManager.h"

namespace std {

	LineManager::LineManager(const std::string& filename, std::vector<Task*> task, std::vector<CustomerOrder>& order)
	{
		std::fstream fin(filename, std::ios::in);
		std::string record;
		size_t count = 0;

		//read the records from file and setup all the m_pNextTask references in the Task objects, 
		//Linking each Task object together to form the assembly line
		std::vector<std::string> linkingItem;
		while (std::getline(fin, record))
		{
			size_t pos = 0;
			Utilities tmp_util;
			std::string tmp_item;
			bool test = true;

			tmp_item = tmp_util.extractToken(record, pos, test);
			linkingItem.push_back(tmp_item);
		}

		for (size_t i = 0; i < linkingItem.size(); ++i)
		{
			for (size_t j = 0; j < task.size(); ++j)
			{
				if (task[j]->getName() == linkingItem[i])
				{
					if (i == linkingItem.size() - 1)
					{
						m_last = j;
						break;
					}

					for (size_t k = 0; k < task.size(); ++k)
					{
						if (task[k]->getName() == linkingItem[i + 1])
						{
							task[j]->setNextTask(*task[k]);

							if (i == 0)
								m_first = j;
						}
					}
				}
			}
		}

		// Move all the CustomerOrder objects onto the front of the ToBeFilled queue
		for (int i = 0; i < order.size(); i++)
		{
			ToBeFilled.push_front(std::move(order[i]));
			m_cntCustomerOrder++;
		}
		// Copy all the Task objects into the AssemblyLine container
		AssemblyLine = task;
	}

	bool LineManager::run(std::ostream& os)
	{
		CustomerOrder complete;

		if(!ToBeFilled.empty()) 
		{
			*AssemblyLine[m_first] += std::move(ToBeFilled.back());
			ToBeFilled.pop_back();
		}

		for (size_t i = 0; i < AssemblyLine.size(); i++)
		{
			AssemblyLine[i]->runProcess(os);
		}

		for (int x = (int)AssemblyLine.size() - 1; x >= 0; x--) 
		{
			bool result = AssemblyLine[x]->moveTask();

			if (result)
			{
				CustomerOrder completedOrder;
				bool result = AssemblyLine[x]->getCompleted(completedOrder);
				if (result)
					Completed.push_back(std::move(completedOrder));
			}
		}

		if (Completed.size() == m_cntCustomerOrder)
			return true;
		else
			return false;
	}

	void LineManager::displayCompleted(std::ostream& os) const
	{
		if (!Completed.empty())
			for (size_t i = 0; i < Completed.size(); ++i)
				Completed[i].display(os);
	}

	void LineManager::validateTasks() const
	{
		if (!AssemblyLine.empty())
			for (size_t i = 0; i < AssemblyLine.size(); ++i)
				AssemblyLine[i]->validate(std::cout);
	}
}
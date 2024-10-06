#include "pch.h"
#include "OM_Engine/Core/Thread_Pool.hpp"

namespace Core
{
	bool Thread_Pool::Initialisation(unsigned int nb_thread_created)
	{
		for (unsigned int i = 0; i < nb_thread_created; i++)
		{
			m_workers.emplace_back([this] {
				while (true)
				{
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(m_mutex_tasks);
						m_condition_variable.wait(lock, [this] { return m_stop_flag || !m_tasks.empty(); });
						if (m_stop_flag && m_tasks.empty())
							return;

						task = std::move(m_tasks.front());
						m_tasks.pop();
					}
					task();
				}
			});
		}
		return true;
	}

	void Thread_Pool::Add_Task(std::function<void()> task)
	{
		std::lock_guard<std::mutex> lock(m_mutex_tasks);
		m_tasks.emplace(task);
		m_condition_variable.notify_one();
	}

	void Thread_Pool::Destroy()
	{
		std::lock_guard<std::mutex> lock(m_mutex_tasks);
		m_stop_flag = true;

		m_condition_variable.notify_all();
		for (std::thread& worker : m_workers)
		{
			if (worker.joinable())
				worker.join();
		}
	}

	Thread_Pool* Thread_Pool::Get_Instance()
	{
		if (!s_instance)
			s_instance = new Thread_Pool();
		return s_instance;
	}
}
#pragma once

#include "OM_Engine/Base.hpp"
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>

namespace Core
{
	class OM_ENGINE_API Thread_Pool
	{
		// Behavior
	public:
		bool Initialisation(unsigned int nb_thread_created = 5);
		void Add_Task(std::function<void()> task);
		void Destroy();

	private:
		std::vector<std::thread> m_workers;
		std::queue<std::function<void()>> m_tasks;
		std::mutex m_mutex_tasks;
		std::condition_variable m_condition_variable;
		std::atomic<bool> m_stop_flag;

		// Instance
	public:
		static Thread_Pool* Get_Instance();
	private:
		static inline Thread_Pool* s_instance = nullptr;
	};
}
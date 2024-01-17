#pragma once
#include <queue>
#include <mutex>
#include "common.h"

class msgQueue
{
public:
	static msgQueue& getInstance();
	msgQueue(const msgQueue& queue) = delete;
	msgQueue& operator=(const msgQueue& queue) = delete;
	void push(TickStruct& tick);
	void pop();
	TickStruct& front();

private:
	msgQueue() {};
	std::queue<TickStruct> m_queue;
	std::mutex mtx;
};


#include "msgQueue.h"

msgQueue& msgQueue::getInstance()
{
	static msgQueue singleton;
	return singleton;
}

void msgQueue::push(TickStruct& tick)
{
	mtx.lock();
	m_queue.push(tick);
	mtx.unlock();
}

void msgQueue::pop()
{
	mtx.lock();
	m_queue.pop();
	mtx.unlock();
}

TickStruct& msgQueue::front()
{
	return m_queue.front();
}

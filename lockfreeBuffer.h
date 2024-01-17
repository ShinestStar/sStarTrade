#pragma once


template<typename object>
class lockfreeBuffer
{
public:
	//template<typename object>
	lockfreeBuffer(const char* name, unsigned int count, unsigned int flags)
		: m_prodHead(0)
		, m_prodTail(0)
		, m_consHead(0)
		, m_consTail(0)
	{
		if (!powerOf2(count))//
		{

		}
		else
		{
			m_size = count;
			m_mask = m_size - 1;
			m_capacity = m_mask;
			m_ringBuffer = new object[count];
		}

	}

	//template<typename object>
	void enQueue(object obj)
	{
		unsigned int prod_head, prod_next;
		const unsigned int capacity = m_capacity;
		unsigned int free_entries;

		prod_head = m_prodHead;
		prod_next = m_prodHead;
		free_entries = capacity + m_consTail - prod_head;
		if (free_entries < 1)
		{
			//空间不足
		}
		else
		{
			prod_next = prod_head + 1;
			if (1)//单进程
			{
				m_prodHead = prod_next;
			}
		}
		m_ringBuffer[m_prodHead] = obj;

		m_prodTail = prod_next;
		//return n;
	}

	//template<typename object>
	object deQueue()
	{
		unsigned int cons_head, cons_next;
		const unsigned int capacity;
		unsigned int free_entries;

		cons_head = m_consHead;
		cons_next = m_consTail;

		free_entries = m_prodTail - cons_head;

		if (1 > free_entries)
		{
			return;
		}
		cons_next = cons_head + 1;
		if (1)//单消费者
		{
			m_consHead = cons_next;
		}
		if (1)//成功占位
		{
			object tempObj = m_ringBuffer[m_consTail];
			m_consTail = m_consHead;
		}
	}

private:
	template<typename T>
	static bool powerOf2(T number) { return (((number-1) & number) == 0); }
private:
	//char m_name;
	int m_flags;
	object*			 m_ringBuffer;
	unsigned int	 m_size;
	unsigned int	 m_mask;
	unsigned int	 m_capacity;


	volatile int m_prodHead;
	volatile int m_prodTail;
	

	volatile int m_consHead;
	volatile int m_consTail;
	

};

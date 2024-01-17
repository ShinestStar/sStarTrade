#pragma once
#include <cstring>
//�ⲿ���Ժ�Ҫ��װ����������
#define MAX_EXCHANGE_LENGTH 16
#define MAX_INSTRUMENT_LENGTH 32
struct TickStruct
{
	char		exchg[MAX_EXCHANGE_LENGTH];
	char		code[MAX_INSTRUMENT_LENGTH];

	double		price;				//���¼�
	double		open;				//���̼�
	double		high;				//��߼�
	double		low;				//��ͼ�
	double		settle_price;		//�����

	double		upper_limit;		//��ͣ��
	double		lower_limit;		//��ͣ��

	double		total_volume;		//�ܳɽ���
	double		volume;				//�ɽ���
	double		total_turnover;		//�ܳɽ���
	double		turn_over;			//�ɽ���
	double		open_interest;		//�ܳ�
	double		diff_interest;		//����

	unsigned int	trading_date;		//������,��20140327
	unsigned int	action_date;		//��Ȼ����,��20140327
	unsigned int	action_time;		//����ʱ��,��ȷ������,��105932000
	unsigned int	reserve_;			//ռλ��

	double		pre_close;			//���ռ�
	double		pre_settle;			//�����
	double		pre_interest;		//�����ܳ�

	double		bid_prices[10];		//ί��۸�
	double		ask_prices[10];		//ί���۸�
	double		bid_qty[10];		//ί����
	double		ask_qty[10];		//ί����
	TickStruct()
	{
		memset(this, 0, sizeof(TickStruct));
	}

	//TickStruct& operator = (const TickStructOld& tick)
	//{
	//	strncpy(exchg, tick.exchg, MAX_EXCHANGE_LENGTH);
	//	strncpy(code, tick.code, MAX_INSTRUMENT_LENGTH);

	//	price = tick.price;
	//	open = tick.open;
	//	high = tick.high;
	//	low = tick.low;
	//	settle_price = tick.settle_price;

	//	upper_limit = tick.upper_limit;
	//	lower_limit = tick.lower_limit;

	//	total_volume = tick.total_volume;
	//	total_turnover = tick.total_turnover;
	//	open_interest = tick.open_interest;
	//	volume = tick.volume;
	//	turn_over = tick.turn_over;
	//	diff_interest = tick.diff_interest;

	//	trading_date = tick.trading_date;
	//	action_date = tick.action_date;
	//	action_time = tick.action_time;

	//	pre_close = tick.pre_close;
	//	pre_interest = tick.pre_interest;
	//	pre_settle = tick.pre_settle;

	//	for (int i = 0; i < 10; i++)
	//	{
	//		bid_prices[i] = tick.bid_prices[i];
	//		bid_qty[i] = tick.bid_qty[i];
	//		ask_prices[i] = tick.ask_prices[i];
	//		ask_qty[i] = tick.ask_qty[i];
	//	}

	//	return *this;
	//}
};

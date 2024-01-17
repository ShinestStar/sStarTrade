#pragma once
#include <cstring>
//这部分以后要封装到数据类中
#define MAX_EXCHANGE_LENGTH 16
#define MAX_INSTRUMENT_LENGTH 32
struct TickStruct
{
	char		exchg[MAX_EXCHANGE_LENGTH];
	char		code[MAX_INSTRUMENT_LENGTH];

	double		price;				//最新价
	double		open;				//开盘价
	double		high;				//最高价
	double		low;				//最低价
	double		settle_price;		//结算价

	double		upper_limit;		//涨停价
	double		lower_limit;		//跌停价

	double		total_volume;		//总成交量
	double		volume;				//成交量
	double		total_turnover;		//总成交额
	double		turn_over;			//成交额
	double		open_interest;		//总持
	double		diff_interest;		//增仓

	unsigned int	trading_date;		//交易日,如20140327
	unsigned int	action_date;		//自然日期,如20140327
	unsigned int	action_time;		//发生时间,精确到毫秒,如105932000
	unsigned int	reserve_;			//占位符

	double		pre_close;			//昨收价
	double		pre_settle;			//昨结算
	double		pre_interest;		//上日总持

	double		bid_prices[10];		//委买价格
	double		ask_prices[10];		//委卖价格
	double		bid_qty[10];		//委买量
	double		ask_qty[10];		//委卖量
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

#include "parserXTP.h"

parserXTP::parserXTP()
: m_quoteQueue("zz", 65536,1)
, m_userApi(nullptr)
{
	//�Ҳ��м򵥵�� ֻ����dll�ķ���
	
	//m_userApi = XTP::API::QuoteApi::CreateQuoteApi(m_uClientID, path.c_str(), XTP_LOG_LEVEL_DEBUG);
	
	//XTP::API::TraderApi* pUserApi;
	//bool is_connected_ = false;
	std::string trade_server_ip;
	int trade_server_port;
	//std::map<uint64_t, uint64_t> map_session;
	//uint64_t* session_arrary = NULL;
	
	//XTPOrderInsertInfo* orderList = NULL;
	std::string quote_server_ip;
	int quote_server_port;
	std::string quote_username;
	std::string quote_password;
	XTP_PROTOCOL_TYPE quote_protocol = XTP_PROTOCOL_UDP;

	FileUtils* fileUtils = new FileUtils();
		
		if (!fileUtils->init())
		{
			//std::cout << "The config.json file parse error." << std::endl;


			return ;
		}

		//��ȡ��������
		trade_server_ip = fileUtils->stdStringForKey("trade_ip");
		trade_server_port = fileUtils->intForKey("trade_port");
		bool auto_save = fileUtils->boolForKey("auto_save");//�Ƿ񽫻ر��������̣��˲������ڴ�demo��ʹ�ã����漰demo�ص��������߼������Ǳ����
		int client_id = fileUtils->intForKey("client_id");
		int account_count = fileUtils->countForKey("account");
		int resume_type = fileUtils->intForKey("resume_type");
		std::string account_key = fileUtils->stdStringForKey("account_key");

		std::string filepath = fileUtils->stdStringForKey("path");

		bool ping_pong_test = fileUtils->boolForKey("ping_pong_test");//demo�Ƿ���ƹ�Ҳ��ԣ�Ĭ���ǲ������ģ������Ҫ���������������ļ����޸ģ��˲������ڴ�demo��ʹ�ã����漰demo�ص��������߼������Ǳ����

		//��ȡ��������
		quote_server_ip = fileUtils->stdStringForKey("quote_ip");
		quote_server_port = fileUtils->intForKey("quote_port");
		quote_username = fileUtils->stdStringForKey("quote_user");
		quote_password = fileUtils->stdStringForKey("quote_password");
		quote_protocol = (XTP_PROTOCOL_TYPE)(fileUtils->intForKey("quote_protocol"));
		int32_t quote_buffer_size = fileUtils->intForKey("quote_buffer_size");

		//��ȡ������ʱ����
		int32_t heat_beat_interval = fileUtils->intForKey("hb_interval");
		//��ʼ������api
		m_userApi = XTP::API::QuoteApi::CreateQuoteApi(client_id, filepath.c_str(), XTP_LOG_LEVEL_DEBUG);//log��־������Ե���
		m_userApi->RegisterSpi(this);

		m_userApi->SetHeartBeatInterval(heat_beat_interval); //��Ϊ1.1.16�����ӿ�
	//�趨���鱾�ػ����С����λΪMB
		m_userApi->SetUDPBufferSize(quote_buffer_size);//��Ϊ1.1.16�����ӿ�

		int loginResult_quote = -1;
		//��¼���������,��1.1.16��ʼ�����������֧��UDP���ӣ��Ƽ�ʹ��UDP
		loginResult_quote = m_userApi->Login(quote_server_ip.c_str(), quote_server_port, quote_username.c_str(), quote_password.c_str(), quote_protocol);
}

void parserXTP::connect()
{
	unsigned int m_uHBInterval = 1;

	m_userApi->SetHeartBeatInterval(m_uHBInterval);
	//m_userApi->SetUDPBufferSize(m_uBuffSize);//Ĭ��64mb
	int iResult = 0;// = m_userApi->Login(m_strHost.c_str(), m_iPort, m_strUser.c_str(), m_strPass.c_str(), m_iProtocol, m_strLocalIP.c_str());
	if (iResult != 0)
	{
		//if (m_sink)
		//{
		//	if (iResult == -1)
		//	{
		//		m_sink->handleEvent(WPE_Connect, iResult);

		//		write_log(m_sink, LL_ERROR, "[ParserXTP] Connecting server failed: {}", iResult);
		//	}
		//	else
		//	{
		//		m_sink->handleEvent(WPE_Connect, 0);

		//		write_log(m_sink, LL_ERROR, "[ParserXTP] Sending login request failed: {}", iResult);
		//	}

		//}
	}
	else
	{
		//m_uTradingDate = strToTime(m_pUserAPI->GetTradingDay());
		
		//if (m_sink)
		//{
		//	m_sink->handleEvent(WPE_Connect, 0);
		//	m_sink->handleEvent(WPE_Login, 0);
		//}

		//write_log(m_sink, LL_INFO, "[ParserXTP] Connecting server successed: {}, begin to subscibe data ...", iResult);

		subScribe();
	}
}

void parserXTP::subScribe()
{
	char** subscribe = new char* [1];
	const char* jtdj{ "002176" };
	subscribe[0] = (char*)jtdj;
	int iResult = m_userApi->SubscribeMarketData(subscribe, 1, XTP_EXCHANGE_SZ);
	if (iResult != 0)
	{

	}
	else
	{
		//�ɹ�
	}
}

void parserXTP::disconnect()
{

}

void parserXTP::OnDepthMarketData(XTPMD* market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count)
{
	//д��queue
	TickStruct quote;
	//strcpy(quote.exchg, commInfo->getExchg());

	//quote.action_date = actDate;
	//quote.action_time = actTime;

	quote.price = market_data->last_price;
	quote.open = market_data->open_price;
	quote.high = market_data->high_price;
	quote.low = market_data->low_price;
	quote.total_volume = (uint32_t)market_data->qty;
	//quote.trading_date = m_uTradingDate;
	quote.total_turnover = market_data->turnover;

	//if (commInfo->getCategoty() == CC_Future)
	//{
	//	quote.settle_price = market_data->settl_price;
	//	quote.open_interest = (uint32_t)market_data->total_long_positon;

	//	quote.pre_settle = checkValid(market_data->pre_settl_price);
	//	quote.pre_interest = (uint32_t)market_data->pre_total_long_positon;
	//}

	quote.upper_limit = market_data->upper_limit_price;
	quote.lower_limit = market_data->lower_limit_price;

	quote.pre_close = market_data->pre_close_price;

	//ί���۸�
	for (int i = 0; i < 10; i++)
	{
		quote.ask_prices[i] = market_data->ask[i];
		quote.ask_qty[i] = (uint32_t)market_data->ask_qty[i];

		quote.bid_prices[i] = market_data->bid[i];
		quote.bid_qty[i] = (uint32_t)market_data->bid_qty[i];
	}
	m_quoteQueue.enQueue(quote);
}


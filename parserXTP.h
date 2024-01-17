#pragma once
#include "IParser.h"
#include "XTP2.2.37.4/include/xtp_quote_api.h"
#include <string>
#include "lockfreeBuffer.h"
#include "common.h"
#include "FileUtils.h"

class parserXTP : public IParser, public  XTP::API::QuoteSpi
{
public:
	parserXTP();

	void connect();
	void subScribe();
	void disconnect();

private:
	
	virtual void OnDepthMarketData(XTPMD* market_data, int64_t bid1_qty[], int32_t bid1_count, int32_t max_bid1_count, int64_t ask1_qty[], int32_t ask1_count, int32_t max_ask1_count);
	
	
	XTP::API::QuoteApi* m_userApi;//XTPµÄ½Ó¿Ú
	lockfreeBuffer<TickStruct> m_quoteQueue;
};


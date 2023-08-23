#include "W3bstreamClient.h"
#include "DefaultCommunicationFunctions.h"

bool W3bstreamClient::begin(W3bstreamProtocol protocol, void* ctx,
							const W3bstreamCommunicationFunctions& functions)
{
	this->ctx = ctx;
	currentProtocol = protocol;
	commFunctions = functions;
	psa_crypto_init();
	return commFunctions.connectFn(ctx);
}

bool W3bstreamClient::connected()
{
	if(commFunctions.isConnectedFn)
	{
		return commFunctions.isConnectedFn(ctx);
	}
	return false;
}

bool W3bstreamClient::connect()
{
	if(commFunctions.connectFn)
	{
		return commFunctions.connectFn(ctx);
	}
	return false;
}

size_t W3bstreamClient::send(const String data)
{
	if(commFunctions.sendDataFn)
	{
		return commFunctions.sendDataFn((uint8_t*)data.c_str(), data.length(), ctx);
	}
	return false;
}

String W3bstreamClient::read()
{
	// TODO String W3bstreamClient::read()
	return "";
}

void W3bstreamClient::disconnect()
{
	if(commFunctions.disconnectFn)
	{
		commFunctions.disconnectFn(ctx);
	}
}

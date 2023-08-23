#ifndef __DEFAULT_COMMUNICATION_FUNCTIONS_H__
#define __DEFAULT_COMMUNICATION_FUNCTIONS_H__

#include "W3bstreamClient.h"
#include <Arduino.h>

/**
 * Default communication functions
 * Serves as an automagically provided default implementation of the communication functions
 * An implementation is provided for some of the popular boards in the
 * <board>CommunicationFunctions.cpp files The implementation is conditionally compiled based on a
 * macro defined by arduino that indicates the board type
 */
namespace DefaultCommunicationFunctions
{
struct DefaultCtx
{
	W3bstreamProtocol protocol;
	void* settings;
};

bool defaultConnectFn(void* ctx);

bool defaultDisconnectFn(void* ctx);

bool defaultIsConnectedFn(void* ctx);

bool defaultSendDataFn(uint8_t* data, size_t size, void* ctx);

bool defaultReadDataFn(uint8_t* buffer, size_t bufferSize, void* ctx);

} // namespace DefaultCommunicationFunctions

class DefaultW3bstreamHttpSettings
{
  public:
	// Client-less constructor, implemented in device specific class
	DefaultW3bstreamHttpSettings(const char* endpoint, const char* token);

	DefaultW3bstreamHttpSettings(void* client, const char* endpoint, const char* token) :
		client(client), endpoint(endpoint), token(token){};

	~DefaultW3bstreamHttpSettings();

  public:
	const char* endpoint;
	const char* token;
	void* client;
};

struct DefaultW3bstreamMqttSettings
{
	char* host;
	uint16_t port;
	char* topic;
	char* name;
	void* client;
};

#endif // __DEFAULT_COMMUNICATION_FUNCTIONS_H__
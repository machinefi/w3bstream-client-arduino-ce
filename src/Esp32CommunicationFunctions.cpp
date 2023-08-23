/**
 * \file Esp32CommunicationFunctions.cpp
 * \brief Implementation of the communication functions for the ESP32 board
 */

#if defined(ESP32) // Conditionally compile this file only for ESP32

	#include "DefaultCommunicationFunctions.h"
	#include "W3bstreamClient.h"

	#include <HTTPClient.h>
	#include <PubSubClient.h>
	#include <WiFi.h>

using namespace DefaultCommunicationFunctions;

bool DefaultCommunicationFunctions::defaultConnectFn(void* ctx)
{
	Serial.printf("DefaultCommunicationFunctions::defaultConnectFn\n");
	DefaultCtx* defaultCtx = static_cast<DefaultCtx*>(ctx);
	Serial.printf("DefaultCommunicationFunctions::defaultConnectFn - casting protocol\n");
	W3bstreamProtocol protocol = defaultCtx->protocol;
	Serial.printf("DefaultCommunicationFunctions::defaultConnectFn - casting settings\n");
	void* settings = defaultCtx->settings;
	if(protocol == W3bstreamProtocol::HTTP)
	{
		Serial.printf(
			"DefaultCommunicationFunctions::defaultConnectFn - is HTTP, returning success\n");
		return true;
	}
	else if(protocol == W3bstreamProtocol::MQTT)
	{
		const DefaultW3bstreamMqttSettings* mqttSettings =
			static_cast<const DefaultW3bstreamMqttSettings*>(settings);
		PubSubClient* mqttClient = static_cast<PubSubClient*>(mqttSettings->client);
		// Implement MQTT connection
		mqttClient->setServer(mqttSettings->host, mqttSettings->port);
		if(mqttClient->connect(mqttSettings->name))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool DefaultCommunicationFunctions::defaultDisconnectFn(void* ctx)
{
	DefaultCtx* defaultCtx = static_cast<DefaultCtx*>(ctx);
	W3bstreamProtocol protocol = defaultCtx->protocol;
	void* settings = defaultCtx->settings;
	if(protocol == W3bstreamProtocol::HTTP)
	{
		return true;
	}
	else if(protocol == W3bstreamProtocol::MQTT)
	{
		const DefaultW3bstreamMqttSettings* mqttSettings =
			static_cast<const DefaultW3bstreamMqttSettings*>(settings);
		PubSubClient* mqttClient = static_cast<PubSubClient*>(mqttSettings->client);
		mqttClient->disconnect();
		return true;
	}
	return false;
}

bool DefaultCommunicationFunctions::defaultIsConnectedFn(void* ctx)
{
	DefaultCtx* defaultCtx = static_cast<DefaultCtx*>(ctx);
	W3bstreamProtocol protocol = defaultCtx->protocol;
	void* settings = defaultCtx->settings;
	if(protocol == W3bstreamProtocol::HTTP)
	{
		return true;
	}
	else if(protocol == W3bstreamProtocol::MQTT)
	{
		const DefaultW3bstreamMqttSettings* mqttSettings =
			static_cast<const DefaultW3bstreamMqttSettings*>(settings);
		PubSubClient* mqttClient = static_cast<PubSubClient*>(mqttSettings->client);
		return mqttClient->connected();
	}
}

bool DefaultCommunicationFunctions::defaultSendDataFn(uint8_t* data, size_t size, void* ctx)
{
	DefaultCtx* defaultCtx = static_cast<DefaultCtx*>(ctx);
	W3bstreamProtocol protocol = defaultCtx->protocol;
	void* settings = defaultCtx->settings;
	if(protocol == W3bstreamProtocol::HTTP)
	{
		const DefaultW3bstreamHttpSettings* httpSettings =
			static_cast<const DefaultW3bstreamHttpSettings*>(settings);
		HTTPClient* httpClient = static_cast<HTTPClient*>(httpSettings->client);
		httpClient->begin(httpSettings->endpoint);
		httpClient->addHeader("Content-Type", "application/json");
		httpClient->addHeader("Authorization", "Bearer " + String(httpSettings->token));
		int responseCode = httpClient->POST(data, size);
		httpClient->end();
		if(responseCode == 201)
		{
			// Serial.printf("Data sent successfully\n");
			return true;
		}
		else
		{
			// Serial.printf("Error sending data: %d\n", responseCode);
			return false;
		}
	}
	else if(protocol == W3bstreamProtocol::MQTT)
	{
		const DefaultW3bstreamMqttSettings* mqttSettings =
			static_cast<const DefaultW3bstreamMqttSettings*>(settings);
		PubSubClient* mqttClient = static_cast<PubSubClient*>(mqttSettings->client);
		// TODO protobuf encode data
		return mqttClient->publish(mqttSettings->topic, data, size);
	}
	return false;
}

bool DefaultCommunicationFunctions::defaultReadDataFn(uint8_t* buffer, size_t bufferSize, void* ctx)
{
	// TODO DefaultCommunicationFunctions::defaultReadDataFn - not supported by w3bstream
}

W3bstreamCommunicationFunctions::W3bstreamCommunicationFunctions()
{
	connectFn = DefaultCommunicationFunctions::defaultConnectFn;
	disconnectFn = DefaultCommunicationFunctions::defaultDisconnectFn;
	isConnectedFn = DefaultCommunicationFunctions::defaultIsConnectedFn;
	sendDataFn = DefaultCommunicationFunctions::defaultSendDataFn;
	readDataFn = DefaultCommunicationFunctions::defaultReadDataFn;
}

DefaultW3bstreamHttpSettings::DefaultW3bstreamHttpSettings(const char* endpoint,
														   const char* token) :
	endpoint(endpoint),
	token(token)
{
	client = new HTTPClient();
}

DefaultW3bstreamHttpSettings::~DefaultW3bstreamHttpSettings()
{
	HTTPClient* httpClient = static_cast<HTTPClient*>(client);
	delete httpClient;
}

#endif // ESP32
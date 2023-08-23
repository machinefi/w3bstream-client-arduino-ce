#ifndef __W3BSTREAMCLIENT_H__
#define __W3BSTREAMCLIENT_H__

#include "PSACrypto.h"
#include <Arduino.h>

/**
 * \brief Enum to hold the supported communication protocols
 */
enum class W3bstreamProtocol
{
	HTTP,
	MQTT,
	UNINITIALIZED
};

/**
 * \class W3bstreamCommunicationFunctions
 * \brief A class that holds the communication functions
 * \note The default constructor is implemented in the device specific
 * <board>CommunicationFunctions.cpp file The default constructor populates the functions with the
 * default implementation for the current board
 */
class W3bstreamCommunicationFunctions
{
  public:
	W3bstreamCommunicationFunctions(bool (*connectFn)(void* ctx), bool (*disconnectFn)(void* ctx),
									bool (*isConnectedFn)(void* ctx),
									bool (*sendDataFn)(uint8_t* data, size_t size, void* ctx),
									bool (*readDataFn)(uint8_t* buffer, size_t bufferSize,
													   void* ctx)) :
		connectFn(connectFn),
		disconnectFn(disconnectFn), isConnectedFn(isConnectedFn), sendDataFn(sendDataFn),
		readDataFn(readDataFn){};

	W3bstreamCommunicationFunctions();

  public:
	bool (*connectFn)(void* ctx);
	bool (*disconnectFn)(void* ctx);
	bool (*isConnectedFn)(void* ctx);
	bool (*sendDataFn)(uint8_t* data, size_t size, void* ctx);
	bool (*readDataFn)(uint8_t* buffer, size_t bufferSize, void* ctx);
};

/**
 * \class W3bstreamClient
 * \brief A class that represents a W3bstream client
 */
class W3bstreamClient
{
  public:
	W3bstreamClient() :
		currentProtocol(W3bstreamProtocol::UNINITIALIZED),
		commFunctions(W3bstreamCommunicationFunctions()), ctx(nullptr){};

	/**
	 * \brief Starts the client
	 * \param protocol The protocol to use
	 * \param ctx The user context to pass to the communication functions
	 * \param functions The communication functions to use
	 * \return True if the client was started successfully, false otherwise
	 */
	bool
		begin(W3bstreamProtocol protocol, void* ctx,
			  const W3bstreamCommunicationFunctions& functions = W3bstreamCommunicationFunctions());

	/**
	 * \brief Checks if the client is connected
	 * \return True if the client is connected, false otherwise
	 */
	bool connected();

	/**
	 * \brief Connects to the W3bstream server
	 * \return True if the connection was successful, false otherwise
	 */
	bool connect();

	/**
	 * \brief Sends a String to the W3bstream server
	 * \param data The data to send
	 * \return The number of bytes sent
	 */
	size_t send(const String data);

	/**
	 * \brief Reads all data from the W3bstream server
	 */
	String read();

	/**
	 * \brief Disconnects from the W3bstream server
	 */
	void disconnect();

  private:
	// Communication callbacks and user context
	W3bstreamCommunicationFunctions commFunctions;
	void* ctx;

	// The client needs to store protocol for protocol specific logic eg. protobuf encoding
	W3bstreamProtocol currentProtocol;
};

#endif // __W3BSTREAMCLIENT_H__

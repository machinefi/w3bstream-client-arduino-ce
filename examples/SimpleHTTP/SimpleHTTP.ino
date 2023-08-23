#include "Arduino.h"
#include "secrets.h"

#include "DefaultCommunicationFunctions.h"
#include "Signer.h"
#include "W3bstreamClient.h"
#include <HTTPClient.h>

#include <iomanip>
#include <sstream>

// Configuration
const char* endpoint = ENDPOINT;
const char* token = DEVICE_TOKEN;
const char* ssid = SSID;
const char* password = PASSWORD;

// Create an instance of the W3bstreamClient
W3bstreamClient w3bstreamClient;

// Define the HTTP settings
DefaultW3bstreamHttpSettings httpSettings(endpoint, token);

// Define the communication context
using namespace DefaultCommunicationFunctions;
DefaultCtx ctx = {.protocol = W3bstreamProtocol::HTTP, .settings = &httpSettings};

Signer signer;

void setup()
{
	Serial.begin(115200);
	delay(1000);
	Serial.println();

	Serial.println("W3bstream Client example: Simple HTTP");
	Serial.println(
		"This example shows how to use the W3bstreamClient to send data to W3bstream using HTTP.");
	Serial.println("--------------------------------------------------------------------\n");

	// Connect to WiFi
	Serial.println("Connecting to WiFi...");
	WiFi.begin(ssid, password);
	while(WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
	Serial.println("\nWiFi connected");

	// Start the client
	// The communication functions are not passed, so the default ones will be used
	w3bstreamClient.begin(W3bstreamProtocol::HTTP, &ctx);

	W3bstreamKeyDetails keyDetails;
	// Begin the signer. Key is not passed so a new key will be generated
	signer.begin(keyDetails);
}

// Build the payload to send to W3bstream
// The payload message format and content is up to the user and application
// In this example, we have decided to send the string "Hello from SimpleHTTP example!"
// Additionally, the signature is calculated and added to the payload, along with the public key
// There is no requirement to sign the message unless your application requires it, this is just an example
String buildPayload()
{
	uint8_t buf[64] = {0};
	size_t signatureLength = 0;
	String data = "Hello from SimpleHTTP example!";
	Serial.printf("Signing data: %s\n", data.c_str());
	signer.sign(data, buf, sizeof(buf), &signatureLength);

	// Convert the signature to a hex string
	String signature = "";
	std::stringstream ss;
	for(int i = 0; i < signatureLength; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)buf[i];
	}
	signature = String(ss.str().c_str());

	String payload = "{";
	payload += "\"data\":" + data + ",";
	payload += "\"signature\": \"" + signature + "\",";
	payload += "\"public_key\":\"" + signer.exportPublicKey() + "\"";
	payload += "}";
	Serial.printf("Payload: %s\n", payload.c_str());

	return payload;
}

void loop()
{
	// Send a message to W3bstream
	Serial.println("Sending message to W3bstream...");
	String payload = buildPayload();
	Serial.printf("Payload: %s\n", payload.c_str());
	w3bstreamClient.send(payload);
	delay(5000);
}

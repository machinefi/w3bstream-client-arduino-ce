#ifndef __SIGNER_H__
#define __SIGNER_H__

#include "PSACrypto.h"
#include <Arduino.h>

/**
 * \brief Size in bytes of the private key for W3bstream using the default signing algorithm.
 */
#define WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BYTES 32

/**
 * \brief Size in bits of the private key for W3bstream using the default signing algorithm.
 */
#define WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BITS (WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BYTES * 8)

/**
 * \brief A struct that holds the details of a key.
 */
class W3bstreamKeyDetails
{
  public:
	W3bstreamKeyDetails()
	{
		memset(bytes, 0, sizeof(bytes));
		attributes = PSA_KEY_ATTRIBUTES_INIT;
	}
	uint8_t bytes[WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BYTES];
	psa_key_attributes_t attributes;
};

/**
 * \class Signer
 * \brief A class that handles key management and signature generation.
 */
class Signer
{
  public:
	/**
	 * \brief Initializes the signer with the given key, or generates a new key.
	 * \param keyDetails The key details to use. If the key is not set (bytes are all 0), a new key
	 * will be generated. \param algorithm The algorithm to use for signing. Defaults to ECDSA with
	 * SHA256.
	 */
	bool begin(W3bstreamKeyDetails& keyDetails,
			   psa_algorithm_t algorithm = PSA_ALG_ECDSA(PSA_ALG_SHA_256));

	/**
	 * \brief Gets the default key attributes for W3bstream.
	 */
	static void getDefaultAttributes(psa_key_attributes_t* attributes);

	/**
	 * \brief Exports the private key as an array of bytes.
	 * \param buffer The buffer to export the key to.
	 * \param bufferSize The size of the buffer. Should be big enough to hold the key.
	 * \param keySize The number of bytes that have been exported.
	 * \return True if the key was exported successfully, false otherwise.
	 */
	bool exportPrivateKey(uint8_t* buffer, size_t bufferSize, size_t* keySize);

	/**
	 * \brief Exports the private key as a hex String.
	 */
	String exportPrivateKey();

	/**
	 * \brief Exports the public key as a hex String.
	 */
	String exportPublicKey();

	/**
	 * \brief Signs the given data using the algorithm specified in begin().
	 * \param data The data to sign.
	 * \param buffer The buffer to write the signature to.
	 * \param bufferSize The size of the buffer. Should be big enough to hold the signature.
	 * \param signatureLength The number of bytes that have been written to the buffer.
	 * \return True if the data was signed successfully, false otherwise.
	 */
	bool sign(String data, uint8_t* buffer, size_t bufferSize, size_t* signatureLength);

  private:
	String publicKey;
	psa_key_id_t keyHandle;
	psa_algorithm_t algorithm;

	bool generateKey(psa_key_attributes_t* attributes);
};

#endif // __SIGNER_H__
#include "Signer.h"

#include <iomanip>
#include <sstream>

void Signer::getDefaultAttributes(psa_key_attributes_t* attributes)
{
	*attributes = PSA_KEY_ATTRIBUTES_INIT;
	psa_set_key_usage_flags(attributes, PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH);
	psa_set_key_algorithm(attributes, PSA_ALG_ECDSA(PSA_ALG_SHA_256));
	psa_set_key_type(attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_K1));
	psa_set_key_bits(attributes, WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BITS);
}

bool Signer::generateKey(psa_key_attributes_t* attributes)
{
	if(!attributes)
	{
		getDefaultAttributes(attributes);
	}
	psa_status_t status = psa_generate_key(attributes, &keyHandle);
	if(status != PSA_SUCCESS)
	{
		// Serial.printf("Error generating key: %d\n", (int)status);
		return false;
	}
	// Serial.printf("Key generated. Key handle: %d\n", keyHandle);
	return true;
}

bool Signer::exportPrivateKey(uint8_t* buffer, size_t bufferSize, size_t* keySize)
{
	psa_status_t status = psa_export_key(keyHandle, buffer, bufferSize, keySize);
	if(status != PSA_SUCCESS)
	{
		return false;
	}
	return true;
}

String Signer::exportPrivateKey()
{
	uint8_t buf[WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BYTES] = {0};
	size_t keySize = 0;
	exportPrivateKey(buf, sizeof(buf), &keySize);
	std::stringstream ss;
	for(int i = 0; i < keySize; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)buf[i];
	}
	// Serial.printf("Private key: %s\n", ss.str().c_str());
	return String(ss.str().c_str());
}

String Signer::exportPublicKey()
{
	return publicKey;
}

bool Signer::begin(W3bstreamKeyDetails& keyDetails, psa_algorithm_t algorithm)
{
	this->algorithm = algorithm;
	bool keyPassed = false;
	uint8_t emptyKey[WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BYTES] = {0};

	if(memcmp(keyDetails.bytes, &emptyKey, WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BYTES))
	{
		keyPassed = true;
	}
	psa_key_attributes_t uninitialisedAttributes = PSA_KEY_ATTRIBUTES_INIT;
	if(!memcmp(&(keyDetails.attributes), &uninitialisedAttributes, sizeof(psa_key_attributes_t)))
	{
		getDefaultAttributes(&keyDetails.attributes);
	}
	if(!keyPassed)
	{
		generateKey(&keyDetails.attributes);
	}
	else
	{
		psa_status_t status = psa_import_key(&keyDetails.attributes, keyDetails.bytes,
											 WEBSTREAM_DEFAULT_PRIVATE_KEY_SIZE_BYTES, &keyHandle);
		if(status != PSA_SUCCESS)
		{
			return false;
		}
	}

	// Store the public key into publicKey so we don't have to recalculate it every time the user
	// exports it.
	uint8_t publicKey[65] = {0};
	size_t publicKeyLength = 0;
	psa_status_t status =
		psa_export_public_key(keyHandle, publicKey, sizeof(publicKey), &publicKeyLength);
	if(status != PSA_SUCCESS)
	{
		// Serial.printf("Error exporting public key: %d\n", status);
		return false;
	}
	std::stringstream ss;
	for(int i = 0; i < publicKeyLength; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)publicKey[i];
	}
	this->publicKey = String(ss.str().c_str());
	return true;
}

bool Signer::sign(String data, uint8_t* buffer, size_t bufferSize, size_t* signatureLength)
{
	psa_status_t status = psa_sign_message(keyHandle, algorithm, (const uint8_t*)data.c_str(),
										   data.length(), buffer, bufferSize, signatureLength);
	if(status != PSA_SUCCESS)
	{
		// Serial.printf("Error signing data: %d\n", status);
		return false;
	}
	// Serial.printf("Signature length: %d\n", *signatureLength);
	return true;
}
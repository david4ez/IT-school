#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <openssl/pem.h>
#include <openssl/x509.h>

class Fingerprint {
public:
	Fingerprint(const char* name);

	std::string sha256() const;

private:
	const char* m_fileName = "certificate.pem";

	std::unique_ptr<BIO, decltype(&BIO_free)> m_bio{ BIO_new_file(m_fileName, "rb"), &BIO_free };
	std::unique_ptr<X509, decltype(&X509_free)> m_x{ PEM_read_bio_X509(m_bio.get(), NULL, NULL, NULL), &X509_free };
};
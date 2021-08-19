#include "fingerprint.h"

Fingerprint::Fingerprint(const char* name)
	: m_fileName(name) {
    try {
        if (BIO_new_file(m_fileName, "rb") == NULL)
            throw std::runtime_error("Unable to open the certificate");
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what();

        exit(0);
    }
}

std::string Fingerprint::sha256() const {
    static const char hexbytes[] = "0123456789ABCDEF";
    unsigned int n;
    unsigned char md[EVP_MAX_MD_SIZE];
    std::stringstream ss;
    std::string result;

    X509_digest(m_x.get(), EVP_sha256(), md, &n);

    for (int i = 0; i < n; i++) {
        ss << hexbytes[(md[i] & 0xf0) >> 4] << hexbytes[(md[i] & 0x0f) >> 0];
        if (i != n - 1)
            ss << ":";
    }

    ss >> result;

    return result;
}
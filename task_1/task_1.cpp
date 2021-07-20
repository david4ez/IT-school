#include <iostream>
#include <memory>
#include <sstream>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <exception>

using namespace std;

class Data {
public:
    Data() = delete;
    Data(const char* name) 
    : fileName(name) {
        try {
            if (BIO_new_file(fileName, "rb") == NULL)
                throw runtime_error("Unable to open the certificate");
        }
        catch (const runtime_error& e) {
            cout << e.what();

            exit(0);
        }
    }

    string sha256() const {
        static const char hexbytes[] = "0123456789ABCDEF";
        unsigned int n;
        unsigned char md[EVP_MAX_MD_SIZE];
        stringstream ss;
        string result;

        X509_digest(x.get(), EVP_sha256(), md, &n);

        for (int i = 0; i < n; i++) {
            ss << hexbytes[(md[i] & 0xf0) >> 4] << hexbytes[(md[i] & 0x0f) >> 0];
            if (i != n - 1)
                ss << ":";
        }

        ss >> result;

        return result;
    }
private:
    const char* fileName;

    unique_ptr<BIO, decltype(&BIO_free)> bio{ BIO_new_file(fileName, "rb"), &BIO_free };
    unique_ptr<X509, decltype(&X509_free)> x{ PEM_read_bio_X509(bio.get(), NULL, NULL, NULL), &X509_free };
};

int main() {
    char fileName[80];
    cin >> fileName;

    Data info(fileName);

    cout << "SHA256 Fingerprint=" << info.sha256() << endl;

    return EXIT_SUCCESS;
}

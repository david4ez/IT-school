#include <iostream>
#include <openssl/pem.h>
#include <openssl/x509.h>

using namespace std;

struct Data {
    BIO* bio;
    X509* x;
};

int main() {
    Data info;

    info.bio = BIO_new_file("certificate.pem", "rb");
    info.x = PEM_read_bio_X509(info.bio, NULL, NULL, NULL);

    static const char hexbytes[] = "0123456789ABCDEF";
    unsigned int n;
    unsigned char md[EVP_MAX_MD_SIZE];

    X509_digest(info.x, EVP_sha256(), md, &n);

    cout << "SHA256 Fingerprint=";

    for (int i = 0; i < n; i++) {
        cout << hexbytes[(md[i] & 0xf0) >> 4] << hexbytes[(md[i] & 0x0f) >> 0];
        if (i != n - 1)
            cout << ":";
    }

    cout << endl;

    return EXIT_SUCCESS;
}
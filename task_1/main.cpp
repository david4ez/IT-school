#include <iostream>
#include "fingerprint.h"

int main() {
    std::string fileName;
    std::cin >> fileName;

    Fingerprint info(fileName.c_str());

    std::cout << "SHA256 Fingerprint=" << info.sha256() << std::endl;

    return EXIT_SUCCESS;
}
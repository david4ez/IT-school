#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

int main() {
    std::string message;
    getline(std::cin, message);

    shared_memory_object shm_obj(create_only,
                                 "shared_memory",
                                 read_write);
    shm_obj.truncate(1000);

    mapped_region region(shm_obj, read_write);

    memcpy(region.get_address(), message.c_str(), message.length());

    while (true) {
        std::string stop;
        std::cin >> stop;

        if (stop == "stop")
            break;
    }

    shared_memory_object::remove("shared_memory");

    std::cout << "Success!" << std::endl;

    return 0;
}

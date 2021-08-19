#include <iostream>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

int main() {
    try {
        shared_memory_object shm_obj(open_only,
                                     "shared_memory",
                                     read_only);

        mapped_region region(shm_obj, read_only);

        char *mem = static_cast<char*>(region.get_address());
        std::cout << mem << std::endl;
    }
    catch (interprocess_exception &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    std::cout << "Success!" << std::endl;

    return 0;
}

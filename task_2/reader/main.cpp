#include <iostream>
#include <cstring>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

using namespace std;

int main() {
    try {
        shared_memory_object shm_obj(open_only,
                                     "shared_memory",
                                     read_only);

        mapped_region region(shm_obj, read_only);

        char *mem = static_cast<char*>(region.get_address());
        cout << mem;
    }
    catch (interprocess_exception &ex) {
        cout << ex.what() << endl;
        return 1;
    }

    cout << endl << "Success!" << endl;

    return 0;
}

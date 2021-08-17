#include <iostream>
#include <cstring>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

using namespace boost::interprocess;

using namespace std;

int main() {
    string msg;
    char message[80];

    getline(cin, msg);

    for (size_t i = 0; i != msg.length(); i++)
        message[i] = msg[i];

    cout << message << endl;

    shared_memory_object shm_obj(create_only,
                                 "shared_memory",
                                 read_write);
    shm_obj.truncate(1000);

    mapped_region region(shm_obj, read_write);

    memcpy(region.get_address(), message, strlen(message));

    while (true) {
        string stop;
        cin >> stop;

        if (stop == "stop")
            break;
    }

    shared_memory_object::remove("shared_memory");

    cout << "Success!" << endl;

    return 0;
}

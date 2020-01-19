#include <iostream>
#include <fstream>

int main(const int argc, const char **argv) {
    std::ofstream file("in.txt", std::ios::binary);
    for (size_t i = 0; i < 2 * 1024 * 1024; ++i) {
        uint64_t n = rand()%100;
        file.write(reinterpret_cast<const char*>(&n), sizeof(uint64_t));
    }
    file.close();
    return 0;
}
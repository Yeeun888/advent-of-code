#include <string>

int main(int argc, char** argv) {
    std::string test_string("garbageHEREgarbageHERE");

    printf("%d\n", test_string.find("HERE", 8));

    return 0;
}
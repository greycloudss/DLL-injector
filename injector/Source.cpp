#include "header.h"

int main(int argc, const char* argv[]) {
    if (argc != 3) return 10;
    injector(argv[1], argv[2]);
    return 0;
}

#include "crconv.h"

int main(int argc, char **argv) {
    if (argc > 0) {
        return cr_read(argv[1]);
    }
    return 0;
}

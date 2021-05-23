#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "taful.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s license_string\n", argv[0]);
        return -EINVAL;
    }

    printf("Validation result: %d\n", validate(argv[1]));
    return EXIT_SUCCESS;
}

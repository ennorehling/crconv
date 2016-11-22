#include <platform.h>
#include <autoconf.h>
#include "crconv.h"

#include <stdio.h>

int main(int argc, char **argv) {
    if (argc > 0) {
        cJSON *report;
        report = cr_read(argv[1]);
        if (report) {
            fputs(cJSON_Print(report), stdout);
            cJSON_Delete(report);
        }
    }
    return 0;
}

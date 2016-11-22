#include <platform.h>
#include <autoconf.h>
#include "crconv.h"

#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

cJSON *cr_read(const char *filename) {
    FILE *F = fopen(filename, "r");
    char line[8192];
    cJSON *root, *regions, *units, *region, *child = NULL;
    int lineno = 0;

    if (!F) {
        return NULL;
    }
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "regions", regions = cJSON_CreateObject());
    cJSON_AddItemToObject(root, "units", units = cJSON_CreateObject());
    while (!feof(F)) {
        fgets(line, sizeof(line), F);
        ++lineno;
        char *key = strrchr(line, ';');
        if (key == NULL) {
            if (line[0] != '"') {
                int x, y, p = 0;
                char id[16];
                if (sscanf(line, "REGION %d %d %d", &x, &y, &p) >= 2) {
                    snprintf(id, sizeof(id), "%d,%d,%d", x, y, p);
                    cJSON_AddItemToObject(regions, id, child = cJSON_CreateObject());
                    region = child;
                }
                else if (sscanf(line, "EINHEIT %d", &x) >= 1) {
                    snprintf(id, sizeof(id), "%d", x);
                    cJSON_AddItemToObject(units, id, child = cJSON_CreateObject());
                }
                else {
                    child = NULL;
                }
            }
        }
        else if (child) {
            size_t len = strlen(key);
            while (len > 0 && isspace(key[len - 1])) {
                key[--len] = '\0';
            }
            key++;
            if (line[0] == '"') {
                char * value = line + 1;
                if (key > line + 2 && key[-2] == '"') {
                    key[-2] = '\0';
                }
                else {
                    fprintf(stderr, "invalid input in line %d: %s", lineno, line);
                }
                cJSON_AddItemToObject(child, key, cJSON_CreateString(value));
            }
            else {
                double value = atof(line);
                cJSON_AddItemToObject(child, key, cJSON_CreateNumber(value));
            }
        }
    }
    fclose(F);
    return root;
}

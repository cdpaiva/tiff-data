#include "constants.h"

int get_type_byte_count(int type)
{
    int tag_types[5][2] = {{1, 1}, {2, 1}, {3, 2}, {4, 4}, {5, 8}};

    for (int i = 0; i < 5; i++) {\
        if (tag_types[i][0] == type) {
            return tag_types[i][1];
        }
    }
    return -1;
}

char* get_type_name(int type)
{
    if (type < 1 || type > 11) {
        return "";
    }
    char *type_names[11] = {"BYTE", "ASCII", "SHORT", "LONG", "RATIONAL", "SBYTE", "UNDEFINED", "SSHORT", "SRATIONAL", "FLOAT", "DOUBLE"};

    return type_names[type-1];
}

#ifndef ENUM_DEF_H
#define ENUM_DEF_H

enum Endianess {
    LE,
    BE,
    INVALID
};

#endif

int get_type_byte_count(int type);
char* get_type_name(int type);

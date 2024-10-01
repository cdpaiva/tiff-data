#ifndef ENUM_DEF_H
#define ENUM_DEF_H

enum Endianess {
    LE,
    BE,
    INVALID
};

#endif

#ifndef TAG_NUMBER_H
#define TAG_NUMBER_H

typedef struct {
    int tag_number;
    char *name;
} IFD_Tag;

#endif

int get_type_byte_count(int type);
char* get_tag_name(int tag);
char* get_type_name(int type);

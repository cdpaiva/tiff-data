#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


enum Endianess {
    LE,
    BE,
    INVALID
};

FILE* open_file(char* path);
void close_file(FILE* fptr);

void print_raw_header(FILE* fptr);
enum Endianess get_endianess(FILE* fptr);
int is_valid_magic_number(FILE* fptr, enum Endianess endianess);
int get_IFD_offset(FILE* fptr, enum Endianess endianess);



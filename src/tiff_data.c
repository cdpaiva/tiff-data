#include <stdint.h>
#include <stdio.h>
#include "tiff_data.h"
#include "utils.h"

FILE* open_file(char* path)
{
    FILE* fptr = fopen(path, "r");
    if (fptr == NULL) {
        perror("Error opening the file\n");
        exit(EXIT_FAILURE);
    }
    return fptr;
}

void close_file(FILE *fptr)
{
    fclose(fptr);
}

void read_chunk(uint8_t *buffer, FILE *fptr, size_t n, int offset)
{
    long int curr_pos = ftell(fptr);

    int seek_res = fseek(fptr, offset, SEEK_SET);
    if (seek_res != 0) {
        perror("Failed to read chunk.\n");
        exit(1);
    }

    size_t bytes_read = fread(buffer, sizeof(uint8_t), n, fptr);

    fseek(fptr, curr_pos, SEEK_SET);

    if (bytes_read != n) {
        if (feof(fptr)) {
            printf("Reached end of file, could not parse endianess\n");
        } else {
            perror("Error reading file endianess.\n");
        }
        exit(1);
    }
}

enum Endianess get_endianess(FILE *fptr)
{
    int endianess_offset = 0;
    size_t endianess_length = 2;
    uint8_t buffer[endianess_length];

    read_chunk(buffer, fptr, endianess_length, endianess_offset);


    if (buffer[0] == 'I' && buffer[1] == 'I') {
        return LE;
    } else if (buffer[0] == 'M' && buffer[1] == 'M') {
        return BE;
    } else {
        return INVALID;
    }
}

int is_valid_magic_number(FILE *fptr, enum Endianess endianess)
{
    int magic_number_offset = 2;
    size_t magic_number_length = 2;

    uint8_t buffer[magic_number_length];

    read_chunk(buffer, fptr, magic_number_length, magic_number_offset);

    if (endianess == BE) {
        return buffer[1] == 42;
    }

    return buffer[0] == 42;
}

int get_IFD_offset(FILE *fptr, enum Endianess endianess)
{
    int ifd_offset_offset = 4;
    size_t ifd_offset_length = 4;

    uint8_t buffer[ifd_offset_length];

    read_chunk(buffer, fptr, ifd_offset_length, ifd_offset_offset);

    uint32_t IFD_offset = 0;

    for (size_t i = 0; i < ifd_offset_length; i++) {
        IFD_offset += (uint32_t)(buffer[i]) << (i)*8;
    }

    if (endianess == BE) {
        IFD_offset = flip_endianess32(IFD_offset);
    }

    return IFD_offset;
}

int get_number_IFDs(FILE *fptr, enum Endianess endianess)
{
    int IFD_offset = get_IFD_offset(fptr, endianess);
    size_t IFD_number_length = 2;

    uint8_t buffer[IFD_number_length];

    read_chunk(buffer, fptr, IFD_number_length, IFD_offset);

    uint16_t IFD_number = 0;
    for (size_t i = 0; i < IFD_number_length; i++) {
        IFD_number += (uint16_t)(buffer[i]) << (i)*8;
    }

    if (endianess == BE) {
        IFD_number = flip_endianess16(IFD_number);
    }

    return IFD_number;
}

void print_raw_header(FILE *fptr)
{
    int header_offset = 0;
    int header_size = 8;

    uint8_t buffer[header_size];
    read_chunk(buffer, fptr, header_size, header_offset);

    printf("========= IMAGE HEADER =========\n");

    for(int i = 0; i < header_size; i++) {
        printf("%3d ", buffer[i]);
    }
    printf("\n");
}

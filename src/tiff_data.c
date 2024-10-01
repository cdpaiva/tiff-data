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

void print_IFDs(FILE *fptr, enum Endianess endianess)
{
    int IFD_offset = get_IFD_offset(fptr, endianess);
    size_t IFD_number_length = 2;

    printf("IFD offset: %x.\n", IFD_offset);
    uint8_t buffer[IFD_number_length];

    read_chunk(buffer, fptr, IFD_number_length, IFD_offset);

    uint16_t IFD_number = to_uint16(buffer, IFD_number_length ,endianess);

    printf("File has %hu IFDs.\n", IFD_number);

    uint8_t IFD_buffer[IFD_number*12];

    read_chunk(IFD_buffer, fptr, IFD_number*12, IFD_offset + IFD_number_length);

    for (size_t i = 0; i < IFD_number*12; i += 12) {
        uint16_t tag_number = to_uint16(IFD_buffer + i, 12, endianess);
        int field_type_offset = i + 2;

        uint16_t field_type = to_uint16(IFD_buffer + field_type_offset, 10, endianess);
        char* type_name = get_type_name(field_type);
        if (type_name[0] == '\0') {
            perror("Type value must be between 1 and 12");
            exit(1);
        }
        int count_offset = i + 4;

        uint32_t count = to_uint32(IFD_buffer + count_offset, 8, endianess);
        uint32_t value_offset = 0;

        int num_bytes = get_type_byte_count(field_type);
        if (num_bytes * count > 32) {
            value_offset = 0;
        }
        int value_offset_offset = i + 8;
        if (num_bytes == 1) {
            value_offset = IFD_buffer[value_offset_offset];
        } else if (num_bytes == 2) {
            value_offset = to_uint16(IFD_buffer + value_offset_offset, 2, endianess);
        } else if (num_bytes == 4) {
            value_offset = to_uint32(IFD_buffer + value_offset_offset, 4, endianess);
        } else {
            value_offset = 0;
        }

        printf("%hu %s %d %d\n", tag_number, type_name, count, value_offset);
    }
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

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

enum Endianess get_endianess(FILE* fptr)
{
    long int curr_pos = ftell(fptr);
    int ENDIANESS_OFFSET = 0;

    int seek_res = fseek(fptr, ENDIANESS_OFFSET, SEEK_SET);
    if (seek_res != 0) {
        perror("Failed to read image header\n");
        exit(1);
    }

    size_t should_read = 2;
    uint8_t buffer[should_read];
    size_t bytes_read = fread(buffer, sizeof(uint8_t), should_read, fptr);

    fseek(fptr, curr_pos, SEEK_SET);

    if (bytes_read != should_read) {
        if (feof(fptr)) {
            printf("Reached end of file, could not parse endianess\n");
        } else {
            perror("Error reading file endianess.\n");
        }
        exit(1);
    }

    if (buffer[0] == 'I' && buffer[1] == 'I') {
        return LE;
    } else if (buffer[0] == 'M' && buffer[1] == 'M') {
        return BE;
    } else {
        return INVALID;
    }
}

int is_valid_magic_number(FILE* fptr, enum Endianess endianess)
{
    long int curr_pos = ftell(fptr);
    int MAGIC_NUMBER_OFFSET = 2;

    int seek_res = fseek(fptr, MAGIC_NUMBER_OFFSET, SEEK_SET);
    if (seek_res != 0) {
        perror("Failed to read image header\n");
        exit(1);
    }

    size_t should_read = 1;
    uint16_t magic_number;
    size_t bytes_read = fread(&magic_number, sizeof(uint16_t), should_read, fptr);

    fseek(fptr, curr_pos, SEEK_SET);

    if (bytes_read != should_read) {
        if (feof(fptr)) {
            printf("Reached end of file, could not parse endianess\n");
        } else {
            perror("Error reading file endianess.\n");
        }
        exit(1);
    }

    if (endianess == BE) {
        magic_number = flip_endianess16(magic_number);
    }

    return magic_number == 42;
}

int get_IFD_offset(FILE* fptr, enum Endianess endianess)
{
    long int curr_pos = ftell(fptr);
    int IFD_OFFSET_OFFSET = 4;

    int seek_res = fseek(fptr, IFD_OFFSET_OFFSET, SEEK_SET);
    if (seek_res != 0) {
        perror("Failed to read image header\n");
        exit(1);
    }

    size_t should_read = 1;
    u_int32_t IFD_offset;
    size_t bytes_read = fread(&IFD_offset, sizeof(uint32_t), should_read, fptr);

    fseek(fptr, curr_pos, SEEK_SET);

    if (bytes_read != should_read) {
        if (feof(fptr)) {
            printf("Reached end of file, could not parse IFD offset\n");
        } else {
            perror("Error reading file endianess.\n");
        }
        exit(1);
    }

    if (endianess == BE) {
        IFD_offset = flip_endianess32(IFD_offset);
    }

    return IFD_offset;
}

int get_number_IFDs(FILE *fptr, enum Endianess endianess)
{
    long int curr_pos = ftell(fptr);
    int IFD_offset = get_IFD_offset(fptr, endianess);
    printf("IFD offset is %d bytes\n", IFD_offset);
    printf("%02hhX\n", IFD_offset);

    int seek_res = fseek(fptr, IFD_offset, SEEK_SET);
    if (seek_res != 0) {
        perror("Failed to read image header\n");
        exit(1);
    }

    size_t should_read = 1;
    uint16_t IFD_number;
    size_t bytes_read = fread(&IFD_number, sizeof(uint16_t), should_read, fptr);

    if (bytes_read != should_read) {
        if (feof(fptr)) {
            printf("Read %ld bytes\n", bytes_read);
            printf("Reached end of file, could not parse number of IFDs\n"); 
        } else {
            perror("Failed to read number of IFDs\n");
            exit(1);
        }
    }

    fseek(fptr, curr_pos, SEEK_SET);

    if (endianess == BE) {
        IFD_number = flip_endianess16(IFD_number);
    }

    return IFD_number;
}

void print_raw_header(FILE* fptr)
{
    long int curr_pos = ftell(fptr);
    int HEADER_OFFSET = 0;
    int HEADER_SIZE = 8;

    int seek_res = fseek(fptr, HEADER_OFFSET, SEEK_SET);
    if (seek_res != 0) {
        perror("Failed to read image header\n");
        exit(1);
    }

    size_t should_read = 8;
    uint8_t buffer[HEADER_SIZE];
    size_t bytes_read = fread(buffer, sizeof(uint8_t), should_read, fptr);

    if (bytes_read != should_read) {
        if (feof(fptr)) {
            printf("Reached end of file, could not parse IFD offset\n");
        } else {
            perror("Error reading file endianess.\n");
        }
        exit(1);
    }

    fseek(fptr, curr_pos, SEEK_SET);

    printf("========= IMAGE HEADER =========\n");

    for(int i = 0; i < HEADER_SIZE; i++) {
        printf("%3d ", buffer[i]);
    }
    printf("\n");
}

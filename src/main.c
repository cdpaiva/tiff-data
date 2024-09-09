#include "tiff_data.h"
#include "string.h"

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("usage: tiffdata [options] path\n\n");
        printf("options:\n-d : dump all header information\n");
        return 1;
    }

    if (strcmp(argv[1], "-d") == 0) {
        printf("%s\n", argv[1]);
        FILE *fptr = open_file(argv[2]);
        print_raw_header(fptr);
        close_file(fptr);
        return 0;
    }

    if (argc == 2) {
        FILE *fptr = open_file(argv[1]);

        printf("Image byte order: ");
        enum Endianess endianess = get_endianess(fptr);
        if (endianess == LE) {
            printf("Little Endian\n");
        } else if (endianess == BE) {
            printf("Big Endian\n");
        } else {
            printf("Could not parse file endianess.\n");
        }

        if (is_valid_magic_number(fptr, endianess)) {
            printf("File has valid magic number (42)\n");
        } else {
            printf("Invalid magic number\n");
        }

        printf("IFD offset: %u\n", get_IFD_offset(fptr, endianess));
        close_file(fptr);
        return 0;
    }

    return 0;
}

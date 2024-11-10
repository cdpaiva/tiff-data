#include "utils.h"

uint16_t flip_endianess16(uint16_t value)
{
    return (value >> 8) | (value << 8);
}

uint32_t flip_endianess32(uint32_t value)
{
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8)  & 0x0000FF00) |
           ((value << 8)  & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}

uint16_t to_uint16(uint8_t *arr, size_t length, enum Endianess end) 
{
    if (length < 2) {
        perror("Not enough bytes to convert to uint16.");
        exit(1);
    }
    if (end == LE) {
        return (uint16_t)arr[0] | ((uint16_t)arr[1] << 8);
    } 
    if (end == BE) {
        return (uint16_t)arr[1] | ((uint16_t)arr[0] << 8);
    }
    return -1;
}

uint32_t to_uint32(uint8_t *arr, size_t length, enum Endianess end)
{
    if (length < 4) {
        perror("Not enough bytes to convert to uint32.");
        exit(1);
    }
    if (end == LE) {
        return (uint32_t)arr[0] | ((uint32_t)arr[1] << 8) | ((uint32_t)arr[2] << 16) | ((uint32_t)arr[3] << 24);
    } 
    if (end == BE) {
        return (uint32_t)arr[3] | ((uint32_t)arr[2] << 8) | ((uint32_t)arr[1] << 16) | ((uint32_t)arr[0] << 24);
    }
    return -1;
}

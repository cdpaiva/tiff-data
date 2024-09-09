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

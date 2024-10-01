#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

uint16_t flip_endianess16(uint16_t value);
uint32_t flip_endianess32(uint32_t value);
uint16_t to_uint16(uint8_t *arr, size_t length, enum Endianess end);
uint32_t to_uint32(uint8_t *arr, size_t length, enum Endianess end);

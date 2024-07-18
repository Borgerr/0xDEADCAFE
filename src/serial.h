#pragma once
#include <stdint.h>

// -------------------------------------------------------------------
// PORT ADDRESSES
// wiki reference: https://osdev.wiki/wiki/Serial_Ports#Port_Addresses
// -------------------------------------------------------------------

#define COM1_IOPORT 0x3F8
#define COM2_IOPORT 0x2F8
#define COM3_IOPORT 0x3E8
#define COM4_IOPORT 0x2E8
#define COM5_IOPORT 0x5F8
#define COM6_IOPORT 0x4F8
#define COM7_IOPORT 0x5E8
#define COM8_IOPORT 0x4E8

// ------------------------------------------------------------------
// PROTOCOL IMPLEMENTATION
// wiki reference: https://osdev.wiki/wiki/Serial_Ports#Line_Protocol
// ------------------------------------------------------------------

int init_serial(uint16_t port);
char read_serial(uint16_t port);
void write_serials(uint16_t port, const char* str);


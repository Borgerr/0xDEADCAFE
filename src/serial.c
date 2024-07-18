#include "serial.h"

static uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("in %0, %1" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

static void outb(uint16_t port, uint8_t byte) {
    asm volatile ("out %1, %0" : : "a"(byte), "Nd"(port) : "memory");
}

int init_serial(uint16_t port) {
    outb(port + 1, 0x00);   // disable interrupts
    outb(port + 3, 0x80);   // enable DLAB
    outb(port + 0, 0x03);   // set devisor to 3 (lo byte) 38400 baud
    outb(port + 1, 0x00);   //                  (hi byte)
    outb(port + 3, 0x03);   // 8 bits, no parity, one stop bit
    outb(port + 2, 0xC7);   // enable FIFO, clear, with 14-byte threshold
    outb(port + 4, 0x0B);   // IRQ enabled, RTS/DSR set
    outb(port + 4, 0x1E);   // set in loopback mode, test the serial chip
    outb(port + 0, 0xAE);   // test serial chip by sending 0xae over loopback

    // check loopback sent as received
    if(inb(port + 0) != 0xAE)
        return -1;

    // serial isn't faulty, set normal operation
    // (not-loopback with IRQ enabled, OUT#1 and OUT#2 bits enabled)
    outb(port + 4, 0x0F);
    return 0;
}

static int is_transmit_empty(uint16_t port) {
    return inb(port + 5) & 0x20;
}

static void write_serialc(uint16_t port, char a) {
    while (is_transmit_empty(port) == 0);   // busy loop until transmit empty
    outb(port, a);
}

void write_serials(uint16_t port, const char* str) {
    char* i = str;
    while (*i) {
        write_serialc(port, *i);
        i++;
    }
}


#include "kio.h"

void printk(uint16_t port, const char* str) {
    write_serials(port, str);
    vgaprint(str);
}


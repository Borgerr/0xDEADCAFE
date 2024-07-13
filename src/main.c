#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "limine.h"

// base revision set to 2, recommended since it's the latest base revision
// described by the limine boot protocol
__attribute__((used, section(".requests")))
volatile LIMINE_BASE_REVISION(2);

extern volatile struct limine_framebuffer_request framebuffer_request;

// mandatory functions that GCC and Clang reserve the right to generate calls to
// NO TOUCHIE but you can move them
void* memcpy(void* dest, const void* src, size_t n) {
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t* psrc = (const uint8_t*)src;

    for (size_t i = 0; i < n; i++)
        pdest[i] = psrc[i];

    return dest;
}

void* memset(void* s, int c, size_t n) {
    uint8_t* p = (uint8_t*)s;

    for (size_t i = 0; i < n; i++)
        p[i] = (uint8_t)c;

    return s;
}

void* memmove(void* dest, const void* src, size_t n) {
    uint8_t* pdest = (uint8_t*)dest;
    const uint8_t* psrc = (const uint8_t*)src;

    if (src > dest) {
        for (size_t i = 0; i < n; i++)
            pdest[i] = psrc[i];
    } else if (src < dest) {
        for (size_t i = n; i > 0; i--)
            pdest[i-1] = psrc[i-1];
    }

    return dest;
}

int memcmp(const void* s1, const void* s2, size_t n) {
    const uint8_t* p1 = (const uint8_t*)s1;
    const uint8_t* p2 = (const uint8_t*)s2;

    for (size_t i = 0; i < n; i++) {
        if (p1[i] != p2[i])
            return p1[i] < p2[i] ? -1 : 1;
    }

    return 0;
}

// halt and catch fire
static void hcf(void) {
    asm ("cli");
    for (;;)
        asm ("hlt");
}

// UNIMPORTANT TESTING THINGS
// can remove someday but for now this is just to do some Q&D "tests"
// IAFM.
void takesInt(int x) {}

// kernel's entry point
// linker refers to this function's name
void _start(void) {
    // ensure bootloader actually understands base revision
    if (LIMINE_BASE_REVISION_SUPPORTED == false)
        hcf();

    // ensure we have a framebuffer
    if (framebuffer_request.response == NULL
            || framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // fetch first framebuffer
    struct limine_framebuffer* framebuffer = framebuffer_request.response->framebuffers[0];
    for (size_t i = 0; i < 100; i++) {
        volatile uint64_t* fb_ptr = framebuffer->address;
        fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
    }

    uint8_t sum = 0;
    for (uint8_t* i = 0; i < 0x200000000; i += 4096) {
        sum += *i;
    }
    takesInt(sum);

    hcf();
}


// file serves, for now, as a means for kernel printing
// until I figure out how to roll my own printing after limine boot.
// This will likely require a working filesystem, as I want to keep the kernel
// as small as possible.
// So, I suppose this serves as motivation for getting a working filesystem module asap

#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "limine.h"

#include "vgaprint.h"

extern volatile struct limine_framebuffer_request framebuffer_request;
static struct flanterm_context* flanterm_ctxt;

int vgaprint_init() {
    // ensure we have a framebuffer
    if (framebuffer_request.response == NULL
            || framebuffer_request.response->framebuffer_count < 1) {
        return -1;
    }
    // fetch 0th framebuffer
    struct limine_framebuffer* fbp = framebuffer_request.response->framebuffers[0];

    flanterm_ctxt = flanterm_fb_init(   // args meanings can be found in flanterm/backends/fb.h
            NULL,
            NULL,
            fbp->address, fbp->width, fbp->height, fbp->pitch,
            fbp->red_mask_size, fbp->red_mask_shift,
            fbp->green_mask_size, fbp->green_mask_shift,
            fbp->blue_mask_size, fbp->blue_mask_shift,
            NULL,
            NULL, NULL,
            NULL, NULL,
            NULL, NULL,
            NULL, 0, 0, 1,
            0, 0,
            0
            );

    return 0;
}

void vgaprint(const char* str) {
    // TODO: revisit and lower cost. Maybe add a parameter for length.
    char* str_i = (char*)str;
    size_t char_count = 0;
    while (*str_i) {
        str_i++;
        char_count++;
    }
    flanterm_write(flanterm_ctxt, str, char_count);
}


# 0xDEADCAFE
An operating system providing simple access to a modular kernel, shipped with just enough to get started.

## Work in Progress

You can see the current progress on a blog on [my website](<https://borgerr.github.io/blog/index.html>).
Although this README has big goals, for now it's really just a toy OS.
Only time will tell whether or not this has any potential-
but for me, it's easier to work on something when there's a goal.

## Goals

The OS aims to be as minimal as possible for the sake of extreme modularity.
This means adding things at runtime like:

- device drivers
- system calls
- protocol implementaitons

Although the mechanisms are not yet implemented,
I aim to have a simple suite of utilities
like linux's `insmod`, `modprobe`, `rmmod`, `dmesg`, etc.

### Other Considerations

Since this project is currently WIP, considerations and ideas relevant to the project
may come and go out of my mind at a moment's notice.
I try to capture them all here, or in other notes I have (again, see my blog).

- Do we want static modules, or strictly dynamic modules?

## Building

- `make` builds the kernel binary
- `make iso` builds the kernel binary and creates a bootable iso
- `make run` builds the kernel binary and runs it in QEMU


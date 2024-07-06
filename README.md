# 0xDEADCAFE
An operating system providing simple access to a modular kernel, shipped with just enough to get started.

## Work in Progress

You can see the current progress on a blog on [my website](<https://borgerr.github.io).

## Goals

The OS aims to be as minimal as possible for the sake of extreme modularity.
This means adding things at runtime like:

- device drivers
- system calls
-

Although the mechanisms are not yet implemented,
I aim to have a simple suite of utilities
like linux's `insmod`, `modprobe`, `rmmod`, `dmesg`, etc.

### Other Considerations

Since this project is currently WIP, considerations and ideas relevant to the project
may come and go out of my mind at a moment's notice.
I try to capture them all here, or in other notes I have (again, see my blog).

- Do we want static modules, or strictly dynamic modules?

## Building

- building kernel binary: `make` from repo's root directory
- after building kernel binary, create iso: `create_iso.sh`


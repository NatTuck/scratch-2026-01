
# Building a Filesystem with FUSE

## FUSE: File system in UserSpaceE

- A library, libfuse, so that you can
  - Write a program
  - Which implements the library interface
  - And get it work as a filesystem that you can mount
    on a Linux (maybe Mac, FreeBSD) system.
- A kernel module, fuse, which hooks up kernel mounting
and system calls so this works.

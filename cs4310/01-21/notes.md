You are a CS major, you know how to write computer programs.

In this class, we're going to explore the details of
how specific computers work.

Specificially: We'll look at how operating sytems work.

Examining computer systems / operating systems is to some
extent archeology over engineering.

History of operating systems:

- Before ~1980, at least for small computers, computers
  ran one program at a time.
- Basic problem of multi-tasking: Sharing hardware
  - If you run two programs and type on the keyboard,
    which one gets the keystrokes?
  - On a modern system, one program has "keyboard focus"
    and it gets the keystrokes.
  - There's some hardware interface (e.g. USB) that actually
    connects the computer to the keyboard.
  - Solution: Add abstraction, specifically a third program
    that connects to the hardware and then forwards keystokes
    to the program that currently has focus.
- Solution: One program talks to the hardware and manages sharing.
  - This is the OS Kernel
  - This also gives us reliability and security properties
    - Makes multi-user systems possible with a permission systme
    - Allows for app permissions
    - Lets some bugs not be full system crashes
- The OS kernel exposes an API that lets user programs access
  shared resources.
- That API is a set of "system calls", which look a lot like
  function calls to programmers.
- This class covers:
  - Using system calls
    - Including building OS components that are mostly userspace
      code.
  - Implementing system calls in the kernel

Details:

- Different operating systems have different system calls.
- Different processor archtectures have different machine instructions,
  which means different system call mechanisms.
  - Example archetectures
  - CPU:
    - x86, amd64
    - Apple M-series (ARM), mobile ARM
    - RISC-V
  - GPU: (Don't typically have operating systems in our sense)
    - CUDA (or specific Nvidia families)
    - Whatever AMD's doing
    - Intel stuff
    - etc
- We're going to pick one (two?, six?)
  - Inkfish runs Debian 13 on amd64
    - This is 99% compatible with Ubuntu 24.04 or Linux Mint 22
  - We're also going to look at RISC-V
    - This will run Debian 13; we can do that in a VM or on real
        hardware.
    - We'll also be looking at the xv6 teaching OS

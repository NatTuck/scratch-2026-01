
# AMD64 Archetecture

AMD64 was developed by AMD in the early 2000's as a 64-bit
extension to Intel's ia32 (i386) 32-bit processor archetecture.

A 64 bit archetecture means:

- registers
- memory addresses

Development sequence of Intel x86 type architectures from the start.

~ 1975: Intel develops an 8 bit graphics chip.

Registers: a, b, c, d

~ 1978: Intel developed a 16-bit CPU called the 8088 (varinat 8086).

- We have 16 bit registers: ax, bx, cx, dx, si, di, sp, bp
- How much RAM in a simple 16 bit machine?
  - 65,535 bytes, or 64 K
- This CPU was used for the IBM PC.
- 640 K of RAM should be enough for anyone.
  - Idea: Segments. Have an extra register that gives you just
    a couple more bits.

~ 1985: Intel developed a 32-bit extension to the 16 bit ISA.

- We have 32-bit registers: eax, ebx, ecx, edx, esi, edi, esp, ebp
  - You can still use ax, and it's the bottom half of eax.
- Now we have 2^32 as our maxium memory address.
  - Max addressable RAM is 4 GB.

~ 2003: AMD64

- 64 bit registers: rax, rbx, rcx, rdx, rsi, rdi, rsp, rbp, +r8..r15
  - You can still use eax, ax, al, ah

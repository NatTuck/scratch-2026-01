
# RISC-V (64 bit)

Three surviving processor architectures:

- AMD64 (Intel / AMD Exclusive)
  - Intel was the winner with CISC
- ARM (Licensed by ARM, Inc)
  - ARM was the winner with RISC
- RISC-V (Open source)

RISC vs CISC

Reduced vs Complex Instruction Set Computing

Is it better to have a few simple instrutions which the CPU can mostly execute
in one clock cycle but you need to execute a bunch of them to do things, or is
it better to have complex instructions tha are individually more efficient.

Example: Dedicated divide instruction vs. subtract loop.

It turns out that instruction set doesn't matter that much, because whatever
strategy is good for one instruction set can be used for any through cheap
hardware translation.

AMD64: Upgrades from 8 general purpose registers to 16.

Traditional RISC has usually had 32.

On RISCV, those are x0 - x31.

There are aliases for the ABI:

- zero: (x0) is always zero.
- ra: is the return address register
- sp: stack pointer
- a0-a7: argument registers (a0, a1 are return registers)
- t0-t6: temporaries
- s0-s11: safe / saved registers
- fp: frame pointer


# Operating System Kernel

What is a kernel?

- The component that lets hardware talk to software.
- The only program that runs on the computer that isn't restricted as a
  "user program".
  - It can access memory by physical address.
  - It can execute privileged CPU instructions (e.g. disable interrupts,
    set page tables, etc)
  - Directly talk to hardware without needing to make system calls.

We should look at two things:

- How the kernel can talk to hardware (slides).
- How user programs can talk to the kernel (syscalls).

## Syscalls

On AMD64:

- Put stuff in registers.
- syscall

On RISC-V:

- Put stuff in registers.
- ecall

On x86 (32-bit)

- Put stuff in regisers and on the stack.
- int 0x80

Any of these causes the kernel to look up the syscall handler
in the system call table.

This runs some code (kind of like a function, but in kernel mode).
Then we return to user code when we're done.

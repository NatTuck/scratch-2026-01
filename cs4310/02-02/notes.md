
```
1038

         jj  ii 
buf = [1, 0, 3, 8, '\0']
```

## Registers

- Argument registers: rdi, rsi, rdx, rcx, r8, r9, (stack)
- Return registers: rax, rdx
- Safe registers: rbx, r12-r15
  - Functions shouldn't appear to change these registers.
  - This means that if you use these registers, you have to
     save the old value and then restore it before returning.
- Non-safe, or temporary registers, are presumptively overwritten
   by any function call.

## Three ways for a register/variable to survive a function call

- Use a safe register.
  - That means we need to save and restore those regisers so
    we aren't clobbering them for functoins that call us.
- Allocate directly on the stack.
- Explicitly save and restore the temporary regs around the
  function call.

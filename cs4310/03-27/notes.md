
# More GC Notes

- Mark and Sweep

- Roots
  - This is where we have references to dynamically allocated
    objects from outside the heap.
  - Stack and Globals
  - Registers - Really just safe registers, temporary registers
    will have been saved somewhere due to function calling conventions
- Managed Heap
  - This is what we're scanning.

```C
void
count_goats(goat* goat1)
{
  goat* goat2 = gc_malloc(sizeof(goat));
  // goat1 may still be in %rdi restored from the stack,
  // but it may also be in a safe register
  printf("%p\n", goat1);
}
```

Scanning steps:

- Push all safe registers to stack
  - Probably needs assembly code.
- Figure out where the stack is
- Then we can scan for pointers

Even more accurate stack locations:

**Inline assembly**

```
void *sp;
__asm__ volatile ("movq %%rsp, %0" : "=r" (sp) : :  );
```

Finding the various parts of our address space: /proc/self/maps

**Can we do a copying collector?**

What does a copying collector do that a simple mark / sweep collector
does not?

- Copies Stuff
- Modifies pointers

Modifying pointers is an issue if we misidentify pointers due to numeric
value collisions.

48 bit address space, base rate of collisons is going be (# of objects)/2^48 *
(# of potential pointers)

Complication: Interior pointers

- If we have an array `xs[1000]`
- User takes address `&(xs[753])` and stores it in register.

This means lots of things could be pointers, we have to update all of them,
and if they weren't pointers we've corrupted our data.

How do languages like Java / JavaScrpit manage to do copying collectors?

- `struct goat  { ... } // in C`
  - The C compiler completely throws away this data definition.
- `class Goat { ... } // in Java`
  - In Java, we can't create interior pointers because we don't
    have pointer arithmetic.
  - Java keeps all its class definitions at runtime.

```
struct goat {
  char* name;
  long age;
}

function {
  goat gg;    // 16(%rsp)
  gg.name;    // 16(%rsp)
  gg.age;     // 24(%rsp)
}

function { // in Java methods
  goat gg;    // 16(%rsp) (object base)
  gg.name;    // 16(%rsp) (pointer)
  gg.age;     // 24(%rsp) (non-pointer)
}
```

```

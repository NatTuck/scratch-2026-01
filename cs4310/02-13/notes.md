
# Virtual Address Space

- When we run a program, it gets a virtual address space.
- The OS and CPU conspire to make the program think it has
  access to all the RAM that could be installed in a computer
  of the current architecture.

On AMD64 Linux:

```
+------------------+   <- top of our address space, 2^47
|                  
| The stack, grows down
|  - may need more than one
|
+----------------------
| Unallocated space
|   Other stuff?
+-----------------------
|
| The heap, grows up.
|  - may need more than one
|
+------------------------
| Sections from binary:
| - Text
| - rodata
| - Data
| - others?
+------------------------
```

## Modern virtual address management

On a modern POSIX system (Linux, Mac, Mobile devices, etc)
we control the virtual address mappings with `mmap`.

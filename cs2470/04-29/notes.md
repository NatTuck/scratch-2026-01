
# Today: Semester Review

## Administrivia

**Grades**

- Check all your stuff on Inkfish.
- Find the stuff that's wrong, and email me with links to the
  sub (e.g. <https://inkfish.homework.quest/subs/357>), what's
  wrong, and what it should show instead.

**Course Survey Things**

- Bring a device on Friday. We'll be doing these in class.

## Semester Review

### New Programming Language: C

- Compiled language
  - It compiles to assembly, and that's essential to understanding
    how your code runs.
- It has a simple static type system.
  - Every variable has a declared type.
  - No generics
- It has pointers and manual memory allocation
  - You can manipulate the pointers directly
- It is a procedural language. There are no classes, methods, lambda
expressions, or anything else that languages from after ~1990 have.

Only two ways to do complex types:

- Structs
- Arrays

This is enough to build any data structure, but not usually conveniently.

### Concrete Platform: Linux on AMD64

### Standard Library Functions are Implemented with syscalls

`int printf(const char* format_string, ...);`

`int write(int fd, char* buffer, int len);` // int is probably really size_t

Remember: stdin is 0, stdout is 1, stderr is 2, first return from open is 3

## Abstract syntax tree

```
struct tree_cell {
  int type;
}
```

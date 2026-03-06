
# Today: We'll Build a Calculator

Examples:

```
$ ./calc
expr: 1 + 2
3
expr: 4 + 2 * 9
22
```

Pseudocode:

```
while True:
  expr_text = read_line()
  answer = eval(expr_text)
  print(answer)

def eval(text):
  parse:
    - first, find the last thing to do, split at '+' or '-'
    - then at '*' or '/'
  eval:
    - that gives us a tree, which we evaluate to a number
```

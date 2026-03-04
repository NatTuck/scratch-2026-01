#ifndef EXPR_H
#define EXPR_H

typedef enum expr_type {
    TYPE_LEAF,
    TYPE_BRANCH,
} expr_type;

typedef struct leaf {
    expr_type type;
    int value;
} leaf;

typedef struct branch {
    expr_type type;
    char op;
    struct expr* left;
    struct expr* right;
} branch;

typedef struct expr {
    expr_type type;
} expr;

expr* new_leaf(int vv);
expr* new_branch(char op, expr* left, expr* right);
void free_expr(expr* ex);
expr* parse(char* text);
void print_expr(expr* ee);
int eval(expr* ex);

#endif

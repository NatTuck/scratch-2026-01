
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expr.h"

expr*
new_leaf(int vv)
{
    leaf* ll = malloc(sizeof(leaf));
    ll->type = TYPE_LEAF;
    ll->value = vv;
    // No pointers stored in structure.
    return (expr*)ll;
}

expr*
new_branch(char op, expr* left, expr* right)
{
    branch* bb = malloc(sizeof(branch));
    bb->type = TYPE_BRANCH;
    bb->op = op;
    // two pointer inputs get stored in struct
    // What are the ownership rules for these pointers?
    //  - Here, the branch owns its descendants and
    //    whoever frees the branch must also free
    //    descendents in the tree
    bb->left = left;
    bb->right = right;
    return (expr*)bb;
}

void
free_expr(expr* ex)
{
    if (ex->type == TYPE_BRANCH) {
        branch* bb = (branch*)ex;
        free_expr(bb->left);
        free_expr(bb->right);
    }
    free(ex);
}

//    mm = 5    v
// left = "abcd + ghi\n"

void
split_at(const char* text, int mm, char** left, char** right)
{
    char* tmp = malloc(mm * sizeof(char));

    int ii;
    for (ii = 0; ii < mm; ++ii) {
        tmp[ii] = text[ii];
    }
    tmp[ii] = 0;

    *left = tmp;

    int len = strlen(text);
    tmp = malloc(len - mm);

    for (ii = mm + 1; ii < len; ++ii) {
        tmp[ii - mm - 1] = text[ii];
    }
    tmp[ii] = 0;

    *right = tmp;
}

expr*
build_branch(const char* text, int ii)
{
    char* lt = 0;
    char* rt = 0;
    split_at(text, ii, &lt, &rt);

    expr* le = parse(lt);
    expr* re = parse(rt);

    expr* ex = new_branch(text[ii], le, re);
    free(lt);
    free(rt);

    return ex;
}

expr*
parse(char* text)
{
    // Scan for + or -.
    for (int ii = 0; text[ii]; ++ii) {
        if (text[ii] == '+' || text[ii] == '-') {
            return build_branch(text, ii);
        }
    }

    // Scan for * or /.
    for (int ii = 0; text[ii]; ++ii) {
        if (text[ii] == '*' || text[ii] == '/') {
            return build_branch(text, ii);
        }
    }

    return new_leaf(atoi(text));
}

void
indent(int lvl)
{
    for (int ii = 0; ii < lvl; ++ii) {
        printf("  ");
    }
}

void
print_expr(expr* ee, int lvl)
{
    switch (ee->type) {
    case TYPE_LEAF:
        leaf* ll = (leaf*)ee;
        indent(lvl);
        printf("(leaf %d)\n", ll->value);
        break;
    case TYPE_BRANCH:
        branch* bb = (branch*)ee;
        indent(lvl);
        printf("branch %c:\n", bb->op);
        print_expr(bb->left, lvl + 1);
        print_expr(bb->right, lvl + 1);
    }
}

int
eval_leaf(leaf* ll)
{
    return ll->value;
}

int
eval_branch(branch* bb)
{
    int lv = eval(bb->left);
    int rv = eval(bb->right);
    switch (bb->op) {
    case '+':
        return lv + rv;
    case '-':
        return lv - rv;
    case '*':
        return lv * rv;
    case '/':
        return lv / rv;
    default:
        printf("Bad op\n");
        exit(1);
    }
}

int
eval(expr* ex)
{
    leaf* ll;
    branch* bb;

    switch (ex->type) {
    case TYPE_LEAF:
        ll = (leaf*)ex;
        return eval_leaf(ll);
    case TYPE_BRANCH:
        bb = (branch*)ex;
        return eval_branch(bb);
    default:
        printf("Bad type\n");
        exit(1);
    }
}
